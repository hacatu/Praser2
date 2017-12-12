#define _GNU_SOURCE //asprintf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#include "parser.h"
#include "ast_compiler.h"

/*
pattern = group+
group = option+
option = atom quantifier?
atom = state | string | charset | invset

======pattern======
const char *parse_<rule_name>(ast *t, position *p){
	[if not a generated rule] set_tag(t, <rule_name>_tag);
	[group]...
	return NULL;
}

======group[>1]======
do{
	const char *err = NULL, *terr = NULL;
	position s = *p, e = s;
	[option (err=terr)]...
	if(e.curr > s.curr){
		*p = e;
		return err;
	}
	return "[options_spec]";
}while(0);

======group[1]======
{
	const char *err;
	position s = *p;
	[atom_quantified (err=err)]
	if(err){
		return err;
	}
}

======option======
[atom_quantified]
if(!terr){
	break;
}
if(p->curr > s.curr){
	err = terr;
	e = *p;
	*p = s;
}

======atom_quantified======
[if not quantified: atom_once]
[if quantifier is "?": atom_optional]
[if quantifier is "*": atom_multiple]
[if quantifier is "+": atom_repeated]

======atom_once======
[atom (t=t)]

======atom_optional======
{
	position l = *p;
	[atom (t=t)]
	if(<err>){
		*p = l;
		<err> = NULL;
	}
}

======atom_multiple======
{
	position l;
	ast *c;
	while(1){
		l = *p;
		c = alloc_ast();
		[atom (t=c)]
		if(<err>)break;
		merge_ast(t, c);
	}
	delete_ast(c);
	*p = l;
	<err> = NULL;
}

======atom_repeated======
{
	position l;
	ast *c;
	char matched = 0;
	while(1){
		l = *p;
		c = alloc_ast();
		[atom (t=c)]
		if(<err>)break;
		matched = 1;
		merge_ast(t, c);
	}
	delete_ast(c);
	*p = l;
	if(matched){
		<err> = NULL;
	}
}

======atom======
[if state: atom_state]
[if string: atom_string]
[if charset: atom_charset]
[if invset: atom_invset]

======atom_string======
<err> = read_string(<atom->text>, <t>, p) ? NULL : "<atom->text>";

======atom_charset======
<err> = read_charset([charset_spec], <t>, p) ? NULL : "[[charset_spec]]";

======atom_invset======
<err> = read_invset([invset_spec], <t>, p) ? NULL : "[[invset_spec]]";

======atom_state======
[if assigner is "=": atom_append]
[if assigner is "<": atom_merge]
[if assigner is ":": atom_skip]

======atom_append======
ast *r = alloc_ast();
<err> = [name](s, r, p);
if(<err>){
	delete_ast(r);
}else{
	append_ast(<t>, r);
}

======atom_merge======
<err> = [name](s, <t>, p);

======atom_skip======
ast *r = &(ast){0};
<err> = [name](s, r, p);
clear_ast(r);
*/

const char
src_pre_fmt[] =
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"#include \"parser.h\"\n"
"\n",
src_mid_fmt[] =
"\n",
pattern_decl_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast*, position*);\n"
"static const char %1$s_tag[] = \"%1$s\";\n",
pattern_pre_generated_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast *t, position *p){\n",
pattern_pre_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast *t, position *p){\n"
	"\tset_tag(t, %1$s_tag);\n",
	//[group]...
pattern_post_fmt[] =
	"\treturn NULL;\n"
"}\n\n",
group_pre_fmt[] =
	"\tdo{\n"
		"\t\tconst char *err = NULL, *terr = NULL;\n"
		"\t\tposition s = *p, e = s;\n",
		//[option]...
group_post1_fmt[] =
		"\t\tif(e.curr > s.curr){\n"
			"\t\t\t*p = e;\n"
			"\t\t\treturn err;\n"
		"\t\t}\n"
		"\t\treturn ",//[option_spec]
group_post2_fmt[] =
";\n"
	"\t}while(0);\n",
group_singular_pre_fmt[] =
	"\t{\n"
		"\t\tconst char *err = NULL;\n",
		//[atom_quantified (err=err)]
group_singular_post_fmt[] =
		"\t\tif(err){\n"
			"\t\t\treturn err;\n"
		"\t\t}\n"
	"\t}\n",
option_fmt[] =
		//[atom_quantified (err=terr)]
		"\t\tif(!terr){break;}\n"
		"\t\tif(p->curr > s.curr){\n"
			"\t\t\terr = terr;\n"
			"\t\t\te = *p;\n"
			"\t\t\t*p = s;\n"
		"\t\t}\n",
atom_once_pre_fmt[] =
		"\t\t{\n",
			//[atom (t=t)]
atom_once_post_fmt[] =
		"\t\t}\n",
atom_optional_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l = *p;\n",
			//[atom (t=t)]
atom_optional_post_fmt[] =//1$<err>
			"\t\t\tif(%1$s){\n"
				"\t\t\t\t*p = l;\n"
				"\t\t\t\t%1$s = NULL;\n"
			"\t\t\t}\n"
		"\t\t}\n",
atom_multiple_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l;\n"
			"\t\t\tast *c;\n"
			"\t\t\twhile(1){\n"
				"\t\t\t\tl = *p;\n"
				"\t\t\t\tc = alloc_ast();\n",
				//[atom (t=c)]
atom_multiple_post_fmt[] =//1$<err>
				"\t\t\t\tif(%1$s)break;\n"
				"\t\t\t\tmerge_ast(t, c);\n"
			"\t\t\t}\n"
			"\t\t\tdelete_ast(c);\n"
			"\t\t\t*p = l;\n"
			"\t\t\t%1$s = NULL;\n"
		"\t\t}\n",
atom_repeated_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l;\n"
			"\t\t\tast *c;\n"
			"\t\t\tchar matched = 0;\n"
			"\t\t\twhile(1){\n"
				"\t\t\t\tl = *p;\n"
				"\t\t\t\tc = alloc_ast();\n",
				//[atom (t=c)]
atom_repeated_post_fmt[] =//1$<err>
				"\t\t\t\tif(%1$s)break;\n"
				"\t\t\t\tmatched = 1;\n"
				"\t\t\t\tmerge_ast(t, c);\n"
			"\t\t\t}\n"
			"\t\t\tdelete_ast(c);\n"
			"\t\t\t*p = l;\n"
			"\t\t\tif(matched){\n"
				"\t\t\t\t%1$s = NULL;\n"
			"\t\t\t}\n"
		"\t\t}\n",
atom_string_fmt[] =//1$<err>, 2$<t>, 3$<atom->text>
				"\t\t\t\t%1$s = read_string(\"%3$s\", %2$s, p) ? NULL : \"%3$s\";\n",
atom_charset_fmt[] =//1$<err>, 2$<t>, 3$[charset_spec]
				"\t\t\t\t%1$s = read_charset_prefix(\"%3$s\", %2$s, p) ? NULL : \"%3$s\";\n",
atom_append_fmt[] =//1$<err>, 2$<t>, 3$[name]
				"\t\t\t\tast *r = alloc_ast();\n"
				"\t\t\t\t%1$s = %3$s_parser(r, p);\n"
				"\t\t\t\tif(%1$s){\n"
					"\t\t\t\t\tdelete_ast(r);\n"
				"\t\t\t\t}else{\n"
					"\t\t\t\t\tappend_ast(%2$s, r);\n"
				"\t\t\t\t}\n",
atom_merge_fmt[] =//1$<err>, 2$<t>, 3$[name]
				"\t\t\t\t%1$s = %3$s_parser(%2$s, p);\n",
atom_skip_fmt[] =//1$<err>, 2$[name]
				"\t\t\t\tast *r = &(ast){0};\n"
				"\t\t\t\t%1$s = %2$s_parser(r, p);\n"
				"\t\t\t\tclear_ast(r);\n",
state_name_fmt[] =//1$[name]
"%1$s",
state_name_fmt_trunc[] =//1$[name], 2$[len]
"%1$.*2$s",
state_name_generated_fmt[] =//1$[offset]
"gen%1$#"PRIXPTR;

char *get_parser_name(const ast *atom);
char *get_state_name(const state *s);
char *get_charset_spec(const ast *atom);
void write_option_spec(FILE *f, const ast *group);

void write_rule_decl(FILE *f, const ast *pattern, const char *name);

void write_rule(FILE *f, const ast *pattern, const char *name);
void write_generated_rule(FILE *f, const ast *pattern, const char *name);
void write_group(FILE *f, const ast *group);
void write_group_nonsingular(FILE *f, const ast *group);
void write_group_singular(FILE *f, const ast *group);
void write_option(FILE *f, const ast *option);
void write_atom_quantified(FILE *f, const ast *atom, char quantifier, const char *err);
void write_atom_once(FILE *f, const ast *atom, const char *err);
void write_atom_optional(FILE *f, const ast *atom, const char *err);
void write_atom_multiple(FILE *f, const ast *atom, const char *err);
void write_atom_repeated(FILE *f, const ast *atom, const char *err);
void write_atom(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_string(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_charset(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_state(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_special(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_append(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_merge(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_skip(FILE *f, const ast *atom, const char *err);

void write_rule_decl(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_decl_fmt, name);
}

void write_all(FILE *f, const state *fsm, size_t num_states){
	fprintf(f, src_pre_fmt);
	for(const state *s = fsm; s < fsm + num_states; ++s){
		if(s->parse != state_parse_rule){
			continue;
		}
		ast *pattern;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
		}else{
			pattern = s->rule->children[0];
		}
		char *name = get_state_name(s);
		write_rule_decl(f, pattern, name);
		free(name);
	}
	fprintf(f, src_mid_fmt);
	for(const state *s = fsm; s < fsm + num_states; ++s){
		if(s->parse != state_parse_rule){//s is a special rule that should be defined somewhere else
			continue;
		}
		ast *pattern;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
		}else{
			pattern = s->rule->children[0];
		}
		char *name = get_state_name(s);
		write_rule(f, pattern, name);
		free(name);
	}
}

char *get_parser_name(const ast *atom){
	if(!strcmp("special", atom->name)){
		return strdup(atom->text);
	}//otherwise atom->name is "state"
	const state *s = (const state*)atom->text;
	return get_state_name(s);
}

char *get_state_name(const state *s){
	char *ret;
	if(!strcmp("rule", s->rule->name)){//explicit rule, use the name
		asprintf(&ret, state_name_fmt_trunc, s->rule->children[0]->text, (int)s->rule->children[0]->length);
	}else{
		asprintf(&ret, state_name_generated_fmt, (uintptr_t)((void*)s - (void*)get_state_name));
	}
	return ret;
}

void write_rule(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_pre_fmt, name);
	for(size_t i = 0; i < pattern->size; ++i){
		write_group(f, pattern->children[i]);
	}
	fprintf(f, pattern_post_fmt);
}

void write_generated_rule(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_pre_generated_fmt, name);
	for(size_t i = 0; i < pattern->size; ++i){
		write_group(f, pattern->children[i]);
	}
	fprintf(f, pattern_post_fmt);
}

void write_group(FILE *f, const ast *group){
	if(group->size == 1){
		write_group_singular(f, group);
	}else{
		write_group_nonsingular(f, group);
	}
}

void write_group_nonsingular(FILE *f, const ast *group){
	fprintf(f, group_pre_fmt);
	for(size_t i = 0; i < group->size; ++i){
		write_option(f, group->children[i]);
	}
	fprintf(f, group_post1_fmt);
	write_option_spec(f, group);
	fprintf(f, group_post2_fmt);
}

void write_group_singular(FILE *f, const ast *group){
	fprintf(f, group_singular_pre_fmt);
	char quantifier = group->children[0]->size == 2 ? *group->children[0]->children[1]->text : ' ';
	write_atom_quantified(f, group->children[0]->children[0], quantifier, "err");
	fprintf(f, group_singular_post_fmt);
}

void write_option(FILE *f, const ast *option){
	char quantifier = option->size == 2 ? *option->children[1]->text : ' ';
	write_atom_quantified(f, option->children[0], quantifier, "terr");
	fprintf(f, option_fmt);
}

void write_atom_quantified(FILE *f, const ast *atom, char quantifier, const char *err){
	switch(quantifier){
	case ' ':
		write_atom_once(f, atom->children[0], err);
		break;
	case '?':
		write_atom_optional(f, atom->children[0], err);
		break;
	case '*':
		write_atom_multiple(f, atom->children[0], err);
		break;
	default:// quantifier == '+'
		write_atom_repeated(f, atom->children[0], err);
	}
}

void write_atom_once(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_once_pre_fmt);
	write_atom(f, atom, err, "t");
	fprintf(f, atom_once_post_fmt);
}

void write_atom_optional(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_optional_pre_fmt);
	write_atom(f, atom, err, "t");
	fprintf(f, atom_optional_post_fmt, err);
}

void write_atom_multiple(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_multiple_pre_fmt);
	write_atom(f, atom, err, "c");
	fprintf(f, atom_multiple_post_fmt, err);
}

void write_atom_repeated(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_repeated_pre_fmt);
	write_atom(f, atom, err, "c");
	fprintf(f, atom_repeated_post_fmt, err);
}

void write_atom(FILE *f, const ast *atom, const char *err, const char *t){
	if(!strcmp("state", atom->name)){
		write_atom_state(f, atom, err, t);
	}else if(!strcmp("special", atom->name)){
		write_atom_special(f, atom, err, t);
	}else if(!strcmp("string", atom->name)){
		write_atom_string(f, atom, err, t);
	}else{
		write_atom_charset(f, atom, err, t);
	}
}

static char *charset_spec_add(char *s, char c){
	if(isprint(c)){
		if(c == '\\' || c == '"'){
			*s++ = '\\';
		}
		*s++ = c;
	}else{
		*s++ = '\\';
		switch(c){
		case '\a':
			*s++ = 'a';
			break;
		case '\b':
			*s++ = 'b';
			break;
		case '\f':
			*s++ = 'f';
			break;
		case '\n':
			*s++ = 'n';
			break;
		case '\r':
			*s++ = 'r';
			break;
		case '\t':
			*s++ = 't';
			break;
		case '\v':
			*s++ = 'v';
			break;
		default:
			*s++ = 'x';
			*s++ = "0123456789ABCDEF"[c >> 4];
			*s++ = "0123456789ABCDEF"[c & 0xF];
		}
	}
	return s;
}

void write_atom_string(FILE *f, const ast *atom, const char *err, const char *t){
	char *buf = calloc(1 + 4*strlen(atom->text), sizeof(char));
	for(char *c = (char*)atom->text, *out = buf; *c; ++c){
		out = charset_spec_add(out, *c);
	}
	fprintf(f, atom_string_fmt, err, t, buf);//WARNING: text might not be null terminated.  It isn't normally but I think I fix the strings in ast_interpreter
	free(buf);
}

char *get_charset_spec(const ast *atom){
	char *ret = calloc(2 + 9*atom->size, sizeof(char)), *c = ret;
	if(!strcmp("invset", atom->name)){
		*c++ = '-';
	}else{
		*c++ = '+';
	}
	for(ast **elem = atom->children; elem < atom->children + atom->size; ++elem){
		if(!strcmp("setchar", (*elem)->name)){
			c = charset_spec_add(c, '.');
			c = charset_spec_add(c, *(*elem)->text);
		}else{//(*elem)->name == "setrange"
			c = charset_spec_add(c, '-');
			c = charset_spec_add(c, *(*elem)->children[0]->text);
			c = charset_spec_add(c, *(*elem)->children[1]->text);
		}
	}
	return ret;
}

void write_atom_charset(FILE *f, const ast *atom, const char *err, const char *t){
	char *charset_spec = get_charset_spec(atom);
	fprintf(f, atom_charset_fmt, err, t, charset_spec);
	free(charset_spec);
}

void write_atom_state(FILE *f, const ast *atom, const char *err, const char *t){
	const state *s = (state*)atom->text;
	char assigner = s->rule->size == 3 ? *s->rule->children[1]->text : '<';
	switch(assigner){
	case '=':
		write_atom_append(f, atom, err, t);
		break;
	case '<':
		write_atom_merge(f, atom, err, t);
		break;
	default:// assigner == ':'
		write_atom_skip(f, atom, err);
	}
}

void write_atom_special(FILE *f, const ast *atom, const char *err, const char *t){
	write_atom_merge(f, atom, err, t);
}

void write_atom_append(FILE *f, const ast *atom, const char *err, const char *t){
	char *name = get_parser_name(atom);
	fprintf(f, atom_append_fmt, err, t, name);
	free(name);
}

void write_atom_merge(FILE *f, const ast *atom, const char *err, const char *t){
	char *name = get_parser_name(atom);
	fprintf(f, atom_merge_fmt, err, t, name);
	free(name);
}

void write_atom_skip(FILE *f, const ast *atom, const char *err){
	char *name = get_parser_name(atom);
	fprintf(f, atom_skip_fmt, err, name);
	free(name);
}

void write_option_spec(FILE *f, const ast *group){
	fprintf(f, "\"<option of group>\"");//TODO: actually write out a list of options, maybe by saving the source code of every node.
}

