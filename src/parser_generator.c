/*
parser_generator.c
Generates parsers from a PEG
Written by by hacatu (Gabriel Eiseman)

Grammar specification:
start= rule*
rule= name whitespace? assign whitespace? pattern newline
name= [a-zA-Z0-9_]+
assign= [:=<]
pattern= group (whitespace? group)*
group= option (whitespace? bar whitespace? option)*
option= atom whitespace? quantifier?
atom= parens | name | string | invset | charset
quantifier= [+*?]
parens= lparen whitespace? pattern whitespace? rparen
invset= lbracket caret (setrange | setchar)* rbracket
charset= lbracket (setrange | setchar)* rbracket
setrange= setchar dash setchar
setchar= [^\\\-\]] | "\\-" | "\\]" | esc_seq 
string= quote ([^\\"\n] | "\\\"" | esc_seq)* quote
esc_seq< backslash [nt\\] | ("x" hex hex) | ("u" hex hex hex hex)//needs to be specially defined
whitespace: [ \t]+
lparen: "("
rparen: ")"
lbracket: "["
rbracket: "]"
caret: "^"
quote: "\""
bar: "|"
dash: "-"
backslash: "\\"
newline: "\n"//needs to be specially defined
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parser_generator.h"

//TODO: When I rewrite the generator in Umbrella, specify parse rules and output rules more separately and use CYK so that there is no merge_ast and stuff can happen faster.  The first ast should have all input output in some node or another.  Not deferring the next stage of processing is a good idea, but it might not be feasable.

const char *start_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, start_tag);
	while(!is_end(p)){
		ast *c = alloc_ast();
		if((err = rule_parser(c, p))){
			delete_ast(c);
			return err;
		}
		append_ast(t, c);
	}
	return NULL;
}

const char *rule_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, rule_tag);
	ast *c = alloc_ast();
	if((err = name_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	whitespace_parser(NULL, p);
	c = alloc_ast();
	if((err = assign_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	whitespace_parser(NULL, p);
	c = alloc_ast();
	if((err = pattern_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	if((err = newline_parser(NULL, p))){
		return err;
	}
	return NULL;
}

const char *name_parser(ast *t, position *p){
	set_tag(t, name_tag);
	ast *c = alloc_ast();
	int found = 0;
	while(1){
		if(read_setrange('a', 'z', c, p) ||
		   read_setrange('A', 'Z', c, p) ||
		   read_setrange('0', '9', c, p) ||
		   read_string("_", c, p)){
			found = 1;
		}else{
			break;
		}
	}
	if(!found){
		delete_ast(c);
	}else{
		append_ast(t, c);
	}
	return found ? NULL : name_tag;
}

const char *assign_parser(ast *t, position *p){
	set_tag(t, assign_tag);
	ast *c = alloc_ast();
	if(!(read_string(":", c, p) || read_string("=", c, p) || read_string("<", c, p))){
		delete_ast(c);
		return assign_tag;
	}
	append_ast(t, c);
	return NULL;
}

const char *pattern_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, pattern_tag);
	ast *c = alloc_ast();
	if((err = group_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	while(1){
		position s = *p;
		c = alloc_ast();
		whitespace_parser(NULL, p);
		if(group_parser(c, p)){
			*p = s;
			delete_ast(c);
			break;
		}
		append_ast(t, c);
	}
	return NULL;
}

const char *group_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, group_tag);
	ast *c = alloc_ast();
	if((err = option_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	while(1){
		position s = *p;
		c = alloc_ast();
		whitespace_parser(NULL, p);
		if(bar_parser(NULL, p)){
			*p = s;
			break;
		}
		whitespace_parser(NULL, p);
		if(option_parser(c, p)){
			*p = s;
			delete_ast(c);
			break;
		}
		append_ast(t, c);
	}
	return NULL;
}

const char *option_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, option_tag);
	ast *c = alloc_ast();
	if((err = atom_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	whitespace_parser(NULL, p);
	c = alloc_ast();
	if(quantifier_parser(c, p)){
		delete_ast(c);
	}else{
		append_ast(t, c);
	}
	return NULL;
}

const char *atom_parser(ast *t, position *p){
	const char *err = NULL, *terr = NULL;
	set_tag(t, atom_tag);
	ast *c = alloc_ast();
	position s = *p, e = s;
	do{
		if(!(terr = parens_parser(c, p))){
			break;
		}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(!(terr = name_parser(c, p))){
			break;
		}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(!(terr = string_parser(c, p))){
			break;
		}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(!(terr = invset_parser(c, p))){
			break;
		}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(!(terr = charset_parser(c, p))){
			break;
		}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
		}
		delete_ast(c);
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return atom_tag;
	}while(0);
	append_ast(t, c);
	return NULL;
}

const char *quantifier_parser(ast *t, position *p){
	set_tag(t, quantifier_tag);
	ast *c = alloc_ast();
	if(!(read_string("?", c, p) || read_string("+", c, p) || read_string("*", c, p))){
		delete_ast(c);
		return quantifier_tag;
	}
	append_ast(t, c);
	return NULL;
}

const char *parens_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, parens_tag);
	if((err = lparen_parser(NULL, p))){
		return err;
	}
	whitespace_parser(NULL, p);
	ast *c = alloc_ast();
	if((err = pattern_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	whitespace_parser(NULL, p);
	if((err = rparen_parser(NULL, p))){
		return err;
	}
	return NULL;
}

const char *invset_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, invset_tag);
	if((err = lbracket_parser(NULL, p))){
		return err;
	}
	if((err = caret_parser(NULL, p))){
		return err;
	}
	ast *c;
	position s;
	while(1){
		c = alloc_ast();
		s = *p;
		if(setrange_parser(c, p)){
			*p = s;
			if(setchar_parser(c, p)){
				delete_ast(c);
				break;
			}
		}
		append_ast(t, c);
	}
	if((err = rbracket_parser(c, p))){
		delete_ast(c);
		return err;
	}
	return NULL;
}

const char *charset_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, charset_tag);
	if((err = lbracket_parser(NULL, p))){
		return err;
	}
	ast *c;
	position s;
	while(1){
		c = alloc_ast();
		s = *p;
		if(setrange_parser(c, p)){
			*p = s;
			if(setchar_parser(c, p)){
				delete_ast(c);
				break;
			}
		}
		append_ast(t, c);
	}
	if((err = rbracket_parser(NULL, p))){
		return err;
	}
	return NULL;
}

const char *setrange_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, setrange_tag);
	ast *c = alloc_ast();
	if((err = setchar_parser(c, p))){
		delete_ast(c);
		return err;
	}
	if((err = dash_parser(NULL, p))){
		return err;
	}
	append_ast(t, c);
	c = alloc_ast();
	if((err = setchar_parser(c, p))){
		delete_ast(c);
		return err;
	}
	append_ast(t, c);
	return NULL;
}

const char *setchar_parser(ast *t, position *p){
	set_tag(t, setchar_tag);
	ast *c = alloc_ast();
	if(read_noneOf("\\-]", c, p) || read_string("\\-", c, p) || read_string("\\]", c, p) || !esc_seq_parser(c, p)){
		append_ast(t, c);
		return NULL;
	}
	delete_ast(c);
	return setchar_tag;
}

const char *string_parser(ast *t, position *p){
	const char *err = NULL;
	set_tag(t, string_tag);
	if((err = quote_parser(NULL, p))){
		return err;
	}
	ast *c;
	while(1){
		c = alloc_ast();
		if(!(read_noneOf("\\\"\n", c, p) || read_string("\\\\", c, p) || read_string("\\\"", c, p) || read_string("\\n", c, p) || !esc_seq_parser(c, p))){
			delete_ast(c);
			break;
		}
		append_ast(t, c);
	}
	if((err = quote_parser(NULL, p))){
		return err;
	}
	return NULL;
}

const char *esc_seq_parser(ast *t, position *p){
	const char *err = NULL;
	position s = *p;
	if((err = backslash_parser(NULL, p))){
		return err;
	}
	if(!(read_oneOf("\\nt", t, p) || parse_hex2(t, p) || parse_hex4(t, p))){
		*p = s;
		return "esc_seq";
	}
	return NULL;
}

const char *whitespace_parser(ast *t, position *p){
	return read_oneOf(" \t", NULL, p) ? NULL : "whitespace";
}

const char *lparen_parser(ast *t, position *p){
	return read_string("(", NULL, p) ? NULL : "\"(\"";
}

const char *rparen_parser(ast *t, position *p){
	return read_string(")", NULL, p) ? NULL : "\")\"";
}

const char *lbracket_parser(ast *t, position *p){
	return read_string("[", NULL, p) ? NULL : "\"[\"";
}

const char *rbracket_parser(ast *t, position *p){
	return read_string("]", NULL, p) ? NULL : "\"]\"";
}

const char *caret_parser(ast *t, position *p){
	return read_string("^", NULL, p) ? NULL : "\"^\"";
}

const char *quote_parser(ast *t, position *p){
	return read_string("\"", NULL, p) ? NULL : "\"\\\"\"";
}

const char *bar_parser(ast *t, position *p){
	return read_string("|", NULL, p) ? NULL : "\"|\"";
}

const char *dash_parser(ast *t, position *p){
	return read_string("-", NULL, p) ? NULL : "\"?\"";
}

const char *backslash_parser(ast *t, position *p){
	return read_string("\\", NULL, p) ? NULL : "\"\\\\\"";
}

const char *newline_parser(ast *t, position *p){
	return read_newline(p) ? NULL : "newline";
}

int main(void){
	ast *t = alloc_ast();
	/*
	position p = {
		"start= additive\n"
		"additive= multiplicative (whitespace? addition whitespace? multiplicative)*\n"
		"multiplicative= atom (whitespace? multiplication whitespace? atom)*\n"
		"atom= number | parens\n"
		"addition= [+\\-]\n"
		"multiplication= [/*]\n"
		"parens= lparen whitespace? additive whitespace? rparen\n"
		"number= [0-9]+\n"
		"lparen: \"(\"\n"
		"rparen: \")\"\n"
		"whitespace: [ \t]+\n"
	};
	*/
	position p = {
		"start= rule*\n"
		"rule= name whitespace? assign whitespace? pattern newline\n"
		"name= [a-zA-Z0-9_]+\n"
		"assign= [:=<]\n"
		"pattern= group (whitespace? group)*\n"
		"group= option (whitespace? bar whitespace? option)*\n"
		"option= atom whitespace? quantifier?\n"
		"atom= parens | name | string | invset | charset\n"
		"quantifier= [+*?]\n"
		"parens= lparen whitespace? pattern whitespace? rparen\n"
		"invset= lbracket caret (setrange | setchar)* rbracket\n"
		"charset= lbracket (setrange | setchar)* rbracket\n"
		"setrange= setchar dash setchar\n"
		"setchar= [^\\\\\\-\\]] | \"\\\\-\" | \"\\\\]\" | esc_seq\n"
		"string= quote ([^\\\\\"\\n] | \"\\\\\\\"\" | esc_seq)* quote\n"
		"whitespace: [ \\t]+\n"
		"lparen: \"(\"\n"
		"rparen: \")\"\n"
		"lbracket: \"[\"\n"
		"rbracket: \"]\"\n"
		"caret: \"^\"\n"
		"quote: \"\\\"\"\n"
		"bar: \"|\"\n"
		"dash: \"-\"\n"
		"backslash: \"\\\\\"\n"
	};
	p.curr = p.start;
	p.end = p.start + strlen(p.start);
	const char *err = NULL;
	if((err = start_parser(t, &p))){
		log_err(err, p);
	}else{
		//t = flatten_ast(t);
		prune_ast(t);
		print_ast(t);
	}
	delete_ast(t);
}

