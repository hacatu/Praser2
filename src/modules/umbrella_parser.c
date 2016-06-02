#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

const char *start_parser(ast*, position*);
static const char start_tag[] = "start";
const char *statement_parser(ast*, position*);
static const char statement_tag[] = "statement";
const char *gen0XFFFF8092F3835F2C_parser(ast*, position*);
static const char gen0XFFFF8092F3835F2C_tag[] = "gen0XFFFF8092F3835F2C";
const char *bare_statement_parser(ast*, position*);
static const char bare_statement_tag[] = "bare_statement";
const char *label_tag_parser(ast*, position*);
static const char label_tag_tag[] = "label_tag";
const char *expr_parser(ast*, position*);
static const char expr_tag[] = "expr";
const char *gen0XFFFF8092F3835F8C_parser(ast*, position*);
static const char gen0XFFFF8092F3835F8C_tag[] = "gen0XFFFF8092F3835F8C";
const char *expr_infix_parser(ast*, position*);
static const char expr_infix_tag[] = "expr_infix";
const char *op_infix_parser(ast*, position*);
static const char op_infix_tag[] = "op_infix";
const char *gen0XFFFF8092F3835FD4_parser(ast*, position*);
static const char gen0XFFFF8092F3835FD4_tag[] = "gen0XFFFF8092F3835FD4";
const char *expr_prefix_parser(ast*, position*);
static const char expr_prefix_tag[] = "expr_prefix";
const char *op_prefix_parser(ast*, position*);
static const char op_prefix_tag[] = "op_prefix";
const char *gen0XFFFF8092F383601C_parser(ast*, position*);
static const char gen0XFFFF8092F383601C_tag[] = "gen0XFFFF8092F383601C";
const char *expr_postfix_parser(ast*, position*);
static const char expr_postfix_tag[] = "expr_postfix";
const char *op_postfix_parser(ast*, position*);
static const char op_postfix_tag[] = "op_postfix";
const char *expr0_parser(ast*, position*);
static const char expr0_tag[] = "expr0";
const char *access_parser(ast*, position*);
static const char access_tag[] = "access";
const char *declaration_parser(ast*, position*);
static const char declaration_tag[] = "declaration";
const char *atom_parser(ast*, position*);
static const char atom_tag[] = "atom";
const char *implicit___parser(ast*, position*);
static const char implicit___tag[] = "implicit__";
const char *param_parens_parser(ast*, position*);
static const char param_parens_tag[] = "param_parens";
const char *list_parser(ast*, position*);
static const char list_tag[] = "list";
const char *identifier_parser(ast*, position*);
static const char identifier_tag[] = "identifier";
const char *literal_parser(ast*, position*);
static const char literal_tag[] = "literal";
const char *parens_parser(ast*, position*);
static const char parens_tag[] = "parens";
const char *gen0XFFFF8092F3836154_parser(ast*, position*);
static const char gen0XFFFF8092F3836154_tag[] = "gen0XFFFF8092F3836154";
const char *compound_statement_parser(ast*, position*);
static const char compound_statement_tag[] = "compound_statement";
const char *dict_parser(ast*, position*);
static const char dict_tag[] = "dict";
const char *block_parser(ast*, position*);
static const char block_tag[] = "block";
const char *int_parser(ast*, position*);
static const char int_tag[] = "int";
const char *gen0XFFFF8092F38361CC_parser(ast*, position*);
static const char gen0XFFFF8092F38361CC_tag[] = "gen0XFFFF8092F38361CC";
const char *int_b_parser(ast*, position*);
static const char int_b_tag[] = "int_b";
const char *gen0XFFFF8092F38361FC_parser(ast*, position*);
static const char gen0XFFFF8092F38361FC_tag[] = "gen0XFFFF8092F38361FC";
const char *int_o_parser(ast*, position*);
static const char int_o_tag[] = "int_o";
const char *gen0XFFFF8092F383622C_parser(ast*, position*);
static const char gen0XFFFF8092F383622C_tag[] = "gen0XFFFF8092F383622C";
const char *int_h_parser(ast*, position*);
static const char int_h_tag[] = "int_h";
const char *gen0XFFFF8092F383625C_parser(ast*, position*);
static const char gen0XFFFF8092F383625C_tag[] = "gen0XFFFF8092F383625C";
const char *int_d_parser(ast*, position*);
static const char int_d_tag[] = "int_d";
const char *float_parser(ast*, position*);
static const char float_tag[] = "float";
const char *scientific_parser(ast*, position*);
static const char scientific_tag[] = "scientific";
const char *subnormal_parser(ast*, position*);
static const char subnormal_tag[] = "subnormal";
const char *normal_parser(ast*, position*);
static const char normal_tag[] = "normal";
const char *gen0XFFFF8092F38362EC_parser(ast*, position*);
static const char gen0XFFFF8092F38362EC_tag[] = "gen0XFFFF8092F38362EC";
const char *gen0XFFFF8092F3836304_parser(ast*, position*);
static const char gen0XFFFF8092F3836304_tag[] = "gen0XFFFF8092F3836304";
const char *complex_parser(ast*, position*);
static const char complex_tag[] = "complex";
const char *string_parser(ast*, position*);
static const char string_tag[] = "string";
const char *char_parser(ast*, position*);
static const char char_tag[] = "char";
const char *gen0XFFFF8092F3836364_parser(ast*, position*);
static const char gen0XFFFF8092F3836364_tag[] = "gen0XFFFF8092F3836364";
const char *whitespace_parser(ast*, position*);
static const char whitespace_tag[] = "whitespace";
const char *space_parser(ast*, position*);
static const char space_tag[] = "space";
const char *single_comment_parser(ast*, position*);
static const char single_comment_tag[] = "single_comment";
const char *multi_comment_parser(ast*, position*);
static const char multi_comment_tag[] = "multi_comment";
const char *gen0XFFFF8092F38363DC_parser(ast*, position*);
static const char gen0XFFFF8092F38363DC_tag[] = "gen0XFFFF8092F38363DC";
const char *block_comment_parser(ast*, position*);
static const char block_comment_tag[] = "block_comment";
const char *semicolon_parser(ast*, position*);
static const char semicolon_tag[] = "semicolon";
const char *colon_parser(ast*, position*);
static const char colon_tag[] = "colon";
const char *dot_parser(ast*, position*);
static const char dot_tag[] = "dot";
const char *at_parser(ast*, position*);
static const char at_tag[] = "at";
const char *lparen_parser(ast*, position*);
static const char lparen_tag[] = "lparen";
const char *rparen_parser(ast*, position*);
static const char rparen_tag[] = "rparen";
const char *lbrace_parser(ast*, position*);
static const char lbrace_tag[] = "lbrace";
const char *rbrace_parser(ast*, position*);
static const char rbrace_tag[] = "rbrace";
const char *lbracket_parser(ast*, position*);
static const char lbracket_tag[] = "lbracket";
const char *rbracket_parser(ast*, position*);
static const char rbracket_tag[] = "rbracket";
const char *comma_parser(ast*, position*);
static const char comma_tag[] = "comma";
const char *equals_parser(ast*, position*);
static const char equals_tag[] = "equals";
const char *squote_parser(ast*, position*);
static const char squote_tag[] = "squote";
const char *dquote_parser(ast*, position*);
static const char dquote_tag[] = "dquote";
const char *b_pre_parser(ast*, position*);
static const char b_pre_tag[] = "b_pre";
const char *o_pre_parser(ast*, position*);
static const char o_pre_tag[] = "o_pre";
const char *h_pre_parser(ast*, position*);
static const char h_pre_tag[] = "h_pre";
const char *I_parser(ast*, position*);
static const char I_tag[] = "I";
const char *E_parser(ast*, position*);
static const char E_tag[] = "E";
const char *pound_parser(ast*, position*);
static const char pound_tag[] = "pound";
const char *gen0XFFFF8092F38365EC_parser(ast*, position*);
static const char gen0XFFFF8092F38365EC_tag[] = "gen0XFFFF8092F38365EC";
const char *schar_parser(ast*, position*);
static const char schar_tag[] = "schar";
const char *_implicit___parser(ast*, position*);
static const char _implicit___tag[] = "_implicit__";

const char *start_parser(ast *t, position *p){
	set_tag(t, start_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				ast *r = alloc_ast();
				err = statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(c, r);
				}
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *statement_parser(ast *t, position *p){
	set_tag(t, statement_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = label_tag_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = bare_statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = semicolon_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F3835F2C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3835F2C_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = comma_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *bare_statement_parser(ast *t, position *p){
	set_tag(t, bare_statement_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F3835F2C_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = expr_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *label_tag_parser(ast *t, position *p){
	set_tag(t, label_tag_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = identifier_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = colon_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = colon_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr_parser(ast *t, position *p){
	set_tag(t, expr_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_infix_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F3835F8C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3835F8C_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = op_infix_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_prefix_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr_infix_parser(ast *t, position *p){
	set_tag(t, expr_infix_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_prefix_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F3835F8C_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *op_infix_parser(ast *t, position *p){
	set_tag(t, op_infix_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_string("->", t, p) ? NULL : "->";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("$=", t, p) ? NULL : "$=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("*=", t, p) ? NULL : "*=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("/=", t, p) ? NULL : "/=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("%=", t, p) ? NULL : "%=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<<=", t, p) ? NULL : "<<=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string(">>=", t, p) ? NULL : ">>=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("+=", t, p) ? NULL : "+=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("-=", t, p) ? NULL : "-=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("&=", t, p) ? NULL : "&=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("|=", t, p) ? NULL : "|=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("^=", t, p) ? NULL : "^=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~&=", t, p) ? NULL : "~&=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~|=", t, p) ? NULL : "~|=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~^=", t, p) ? NULL : "~^=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("&&=", t, p) ? NULL : "&&=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("||=", t, p) ? NULL : "||=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("^^=", t, p) ? NULL : "^^=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!&&=", t, p) ? NULL : "!&&=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!||=", t, p) ? NULL : "!||=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!^^=", t, p) ? NULL : "!^^=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("&&", t, p) ? NULL : "&&";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("||", t, p) ? NULL : "||";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("^^", t, p) ? NULL : "^^";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!&&", t, p) ? NULL : "!&&";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!||", t, p) ? NULL : "!||";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!^^", t, p) ? NULL : "!^^";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<<", t, p) ? NULL : "<<";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string(">>", t, p) ? NULL : ">>";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<=>", t, p) ? NULL : "<=>";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string(">=", t, p) ? NULL : ">=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<=", t, p) ? NULL : "<=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("==", t, p) ? NULL : "==";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!=", t, p) ? NULL : "!=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<-", t, p) ? NULL : "<-";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string(">", t, p) ? NULL : ">";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("<", t, p) ? NULL : "<";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("=", t, p) ? NULL : "=";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("&", t, p) ? NULL : "&";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("|", t, p) ? NULL : "|";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("^", t, p) ? NULL : "^";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~&", t, p) ? NULL : "~&";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~|", t, p) ? NULL : "~|";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~^", t, p) ? NULL : "~^";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("+", t, p) ? NULL : "+";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("-", t, p) ? NULL : "-";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("*", t, p) ? NULL : "*";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("/", t, p) ? NULL : "/";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("%", t, p) ? NULL : "%";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("$", t, p) ? NULL : "$";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string(":", t, p) ? NULL : ":";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8092F3835FD4_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3835FD4_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = op_prefix_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr_prefix_parser(ast *t, position *p){
	set_tag(t, expr_prefix_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F3835FD4_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_postfix_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *op_prefix_parser(ast *t, position *p){
	set_tag(t, op_prefix_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_string("++", t, p) ? NULL : "++";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("--", t, p) ? NULL : "--";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("+", t, p) ? NULL : "+";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("-", t, p) ? NULL : "-";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("!", t, p) ? NULL : "!";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("~", t, p) ? NULL : "~";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("*", t, p) ? NULL : "*";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("&", t, p) ? NULL : "&";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8092F383601C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F383601C_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = op_postfix_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr_postfix_parser(ast *t, position *p){
	set_tag(t, expr_postfix_tag);
	{
		const char *err = NULL;
		{
				err = expr0_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F383601C_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *op_postfix_parser(ast *t, position *p){
	set_tag(t, op_postfix_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_string("++", t, p) ? NULL : "++";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("--", t, p) ? NULL : "--";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("..", t, p) ? NULL : "..";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = read_string("?", t, p) ? NULL : "?";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = param_parens_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = list_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = access_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = declaration_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *expr0_parser(ast *t, position *p){
	set_tag(t, expr0_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = declaration_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = atom_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *access_parser(ast *t, position *p){
	set_tag(t, access_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = dot_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = identifier_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *declaration_parser(ast *t, position *p){
	set_tag(t, declaration_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = at_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = atom_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *atom_parser(ast *t, position *p){
	set_tag(t, atom_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = compound_statement_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = identifier_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = literal_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = parens_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = implicit___parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *implicit___parser(ast *t, position *p){
	set_tag(t, implicit___tag);
	{
		const char *err = NULL;
		{
				err = _implicit___parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *param_parens_parser(ast *t, position *p){
	set_tag(t, param_parens_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lparen_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = bare_statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rparen_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *list_parser(ast *t, position *p){
	set_tag(t, list_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = label_tag_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lbrace_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = bare_statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rbrace_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *identifier_parser(ast *t, position *p){
	set_tag(t, identifier_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+-az-AZ._", t, p) ? NULL : "+-az-AZ._";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-az-AZ._-09", c, p) ? NULL : "+-az-AZ._-09";
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *literal_parser(ast *t, position *p){
	set_tag(t, literal_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = list_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = dict_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = block_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = int_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = float_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = complex_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = string_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = char_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *parens_parser(ast *t, position *p){
	set_tag(t, parens_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lparen_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rparen_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F3836154_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3836154_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = identifier_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = literal_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = parens_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = param_parens_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = block_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *compound_statement_parser(ast *t, position *p){
	set_tag(t, compound_statement_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F3836154_parser(c, p);
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *dict_parser(ast *t, position *p){
	set_tag(t, dict_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = label_tag_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = bare_statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *block_parser(ast *t, position *p){
	set_tag(t, block_tag);
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = alloc_ast();
				err = label_tag_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				ast *r = alloc_ast();
				err = statement_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(c, r);
				}
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *int_parser(ast *t, position *p){
	set_tag(t, int_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = int_b_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = int_o_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = int_h_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				ast *r = alloc_ast();
				terr = int_d_parser(r, p);
				if(terr){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8092F38361CC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F38361CC_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+.0.1", c, p) ? NULL : "+.0.1";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *int_b_parser(ast *t, position *p){
	set_tag(t, int_b_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = b_pre_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+.0.1", c, p) ? NULL : "+.0.1";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F38361CC_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F38361FC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F38361FC_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-07", c, p) ? NULL : "+-07";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *int_o_parser(ast *t, position *p){
	set_tag(t, int_o_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = o_pre_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-07", c, p) ? NULL : "+-07";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F38361FC_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F383622C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F383622C_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09-af-AF", c, p) ? NULL : "+-09-af-AF";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *int_h_parser(ast *t, position *p){
	set_tag(t, int_h_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = h_pre_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09-af-AF", c, p) ? NULL : "+-09-af-AF";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F383622C_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F383625C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F383625C_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *int_d_parser(ast *t, position *p){
	set_tag(t, int_d_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F383625C_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *float_parser(ast *t, position *p){
	set_tag(t, float_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = scientific_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = subnormal_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = normal_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *scientific_parser(ast *t, position *p){
	set_tag(t, scientific_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = subnormal_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = normal_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				terr = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(terr)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				terr = NULL;
			}
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = E_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				err = read_charset_prefix("+.+.-", t, p) ? NULL : "+.+.-";
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *subnormal_parser(ast *t, position *p){
	set_tag(t, subnormal_tag);
	{
		const char *err = NULL;
		{
				err = read_string(".", t, p) ? NULL : ".";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *normal_parser(ast *t, position *p){
	set_tag(t, normal_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = read_string(".", t, p) ? NULL : ".";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-09", c, p) ? NULL : "+-09";
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F38362EC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F38362EC_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = float_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = I_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F3836304_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3836304_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = float_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.+.-", t, p) ? NULL : "+.+.-";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = float_parser(r, p);
				if(err){
					delete_ast(r);
				}else{
					append_ast(t, r);
				}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l = *p;
				ast *r = &(ast){0};
				err = whitespace_parser(r, p);
				clear_ast(r);
			if(err){
				*p = l;
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = I_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *complex_parser(ast *t, position *p){
	set_tag(t, complex_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = gen0XFFFF8092F38362EC_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = gen0XFFFF8092F3836304_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *string_parser(ast *t, position *p){
	set_tag(t, string_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = dquote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = schar_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = dquote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *char_parser(ast *t, position *p){
	set_tag(t, char_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = schar_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = squote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F3836364_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F3836364_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = &(ast){0};
				terr = space_parser(r, p);
				clear_ast(r);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = multi_comment_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = single_comment_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *whitespace_parser(ast *t, position *p){
	set_tag(t, whitespace_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F3836364_parser(c, p);
				if(err)break;
				matched = 1;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			if(matched){
				err = NULL;
			}
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *space_parser(ast *t, position *p){
	set_tag(t, space_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.\t.\f.\r.\n.\v. ", t, p) ? NULL : "+.\t.\f.\r.\n.\v. ";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *single_comment_parser(ast *t, position *p){
	set_tag(t, single_comment_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = pound_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("-.\n.\r", c, p) ? NULL : "-.\n.\r";
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *multi_comment_parser(ast *t, position *p){
	set_tag(t, multi_comment_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = pound_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = block_comment_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F38363DC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F38363DC_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_charset_prefix("-.{.}", t, p) ? NULL : "-.{.}";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = block_comment_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *block_comment_parser(ast *t, position *p){
	set_tag(t, block_comment_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = lbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F38363DC_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = rbracket_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *semicolon_parser(ast *t, position *p){
	set_tag(t, semicolon_tag);
	{
		const char *err = NULL;
		{
				err = read_string(";", t, p) ? NULL : ";";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *colon_parser(ast *t, position *p){
	set_tag(t, colon_tag);
	{
		const char *err = NULL;
		{
				err = read_string(":", t, p) ? NULL : ":";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *dot_parser(ast *t, position *p){
	set_tag(t, dot_tag);
	{
		const char *err = NULL;
		{
				err = read_string(".", t, p) ? NULL : ".";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *at_parser(ast *t, position *p){
	set_tag(t, at_tag);
	{
		const char *err = NULL;
		{
				err = read_string("@", t, p) ? NULL : "@";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *lparen_parser(ast *t, position *p){
	set_tag(t, lparen_tag);
	{
		const char *err = NULL;
		{
				err = read_string("(", t, p) ? NULL : "(";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *rparen_parser(ast *t, position *p){
	set_tag(t, rparen_tag);
	{
		const char *err = NULL;
		{
				err = read_string(")", t, p) ? NULL : ")";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *lbrace_parser(ast *t, position *p){
	set_tag(t, lbrace_tag);
	{
		const char *err = NULL;
		{
				err = read_string("[", t, p) ? NULL : "[";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *rbrace_parser(ast *t, position *p){
	set_tag(t, rbrace_tag);
	{
		const char *err = NULL;
		{
				err = read_string("]", t, p) ? NULL : "]";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *lbracket_parser(ast *t, position *p){
	set_tag(t, lbracket_tag);
	{
		const char *err = NULL;
		{
				err = read_string("{", t, p) ? NULL : "{";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *rbracket_parser(ast *t, position *p){
	set_tag(t, rbracket_tag);
	{
		const char *err = NULL;
		{
				err = read_string("}", t, p) ? NULL : "}";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *comma_parser(ast *t, position *p){
	set_tag(t, comma_tag);
	{
		const char *err = NULL;
		{
				err = read_string(",", t, p) ? NULL : ",";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *equals_parser(ast *t, position *p){
	set_tag(t, equals_tag);
	{
		const char *err = NULL;
		{
				err = read_string("=", t, p) ? NULL : "=";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *squote_parser(ast *t, position *p){
	set_tag(t, squote_tag);
	{
		const char *err = NULL;
		{
				err = read_string("'", t, p) ? NULL : "'";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *dquote_parser(ast *t, position *p){
	set_tag(t, dquote_tag);
	{
		const char *err = NULL;
		{
				err = read_string("\"", t, p) ? NULL : "\"";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *b_pre_parser(ast *t, position *p){
	set_tag(t, b_pre_tag);
	{
		const char *err = NULL;
		{
				err = read_string("0", t, p) ? NULL : "0";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.b.B", t, p) ? NULL : "+.b.B";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *o_pre_parser(ast *t, position *p){
	set_tag(t, o_pre_tag);
	{
		const char *err = NULL;
		{
				err = read_string("0", t, p) ? NULL : "0";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.o.O", t, p) ? NULL : "+.o.O";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *h_pre_parser(ast *t, position *p){
	set_tag(t, h_pre_tag);
	{
		const char *err = NULL;
		{
				err = read_string("0", t, p) ? NULL : "0";
		}
		if(err){
			return err;
		}
	}
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.x.X", t, p) ? NULL : "+.x.X";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *I_parser(ast *t, position *p){
	set_tag(t, I_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.i.I.j.J", t, p) ? NULL : "+.i.I.j.J";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *E_parser(ast *t, position *p){
	set_tag(t, E_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.e.E", t, p) ? NULL : "+.e.E";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *pound_parser(ast *t, position *p){
	set_tag(t, pound_tag);
	{
		const char *err = NULL;
		{
				err = read_string("#", t, p) ? NULL : "#";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8092F38365EC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8092F38365EC_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_charset_prefix("-.\\.\".\n", t, p) ? NULL : "-.\\.\".\n";
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = esc_seq_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *schar_parser(ast *t, position *p){
	set_tag(t, schar_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8092F38365EC_parser(c, p);
				if(err)break;
				merge_ast(t, c);
			}
			delete_ast(c);
			*p = l;
			err = NULL;
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *_implicit___parser(ast *t, position *p){
	set_tag(t, _implicit___tag);
	{
		const char *err = NULL;
		{
				err = always_fail_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

