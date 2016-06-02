#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

const char *start_parser(ast*, position*);
static const char start_tag[] = "start";
const char *statement_parser(ast*, position*);
static const char statement_tag[] = "statement";
const char *gen0XFFFF8090FFA2705C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2705C_tag[] = "gen0XFFFF8090FFA2705C";
const char *bare_statement_parser(ast*, position*);
static const char bare_statement_tag[] = "bare_statement";
const char *label_tag_parser(ast*, position*);
static const char label_tag_tag[] = "label_tag";
const char *expr_parser(ast*, position*);
static const char expr_tag[] = "expr";
const char *gen0XFFFF8090FFA270BC_parser(ast*, position*);
static const char gen0XFFFF8090FFA270BC_tag[] = "gen0XFFFF8090FFA270BC";
const char *expr10_parser(ast*, position*);
static const char expr10_tag[] = "expr10";
const char *op10_parser(ast*, position*);
static const char op10_tag[] = "op10";
const char *gen0XFFFF8090FFA27104_parser(ast*, position*);
static const char gen0XFFFF8090FFA27104_tag[] = "gen0XFFFF8090FFA27104";
const char *expr9_parser(ast*, position*);
static const char expr9_tag[] = "expr9";
const char *op9_parser(ast*, position*);
static const char op9_tag[] = "op9";
const char *gen0XFFFF8090FFA2714C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2714C_tag[] = "gen0XFFFF8090FFA2714C";
const char *expr8_parser(ast*, position*);
static const char expr8_tag[] = "expr8";
const char *op8_parser(ast*, position*);
static const char op8_tag[] = "op8";
const char *gen0XFFFF8090FFA27194_parser(ast*, position*);
static const char gen0XFFFF8090FFA27194_tag[] = "gen0XFFFF8090FFA27194";
const char *expr7_parser(ast*, position*);
static const char expr7_tag[] = "expr7";
const char *op7_parser(ast*, position*);
static const char op7_tag[] = "op7";
const char *gen0XFFFF8090FFA271DC_parser(ast*, position*);
static const char gen0XFFFF8090FFA271DC_tag[] = "gen0XFFFF8090FFA271DC";
const char *expr6_parser(ast*, position*);
static const char expr6_tag[] = "expr6";
const char *op6_parser(ast*, position*);
static const char op6_tag[] = "op6";
const char *gen0XFFFF8090FFA27224_parser(ast*, position*);
static const char gen0XFFFF8090FFA27224_tag[] = "gen0XFFFF8090FFA27224";
const char *expr5_parser(ast*, position*);
static const char expr5_tag[] = "expr5";
const char *op5_parser(ast*, position*);
static const char op5_tag[] = "op5";
const char *gen0XFFFF8090FFA2726C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2726C_tag[] = "gen0XFFFF8090FFA2726C";
const char *expr4_parser(ast*, position*);
static const char expr4_tag[] = "expr4";
const char *op4_parser(ast*, position*);
static const char op4_tag[] = "op4";
const char *gen0XFFFF8090FFA272B4_parser(ast*, position*);
static const char gen0XFFFF8090FFA272B4_tag[] = "gen0XFFFF8090FFA272B4";
const char *expr3_parser(ast*, position*);
static const char expr3_tag[] = "expr3";
const char *op3_parser(ast*, position*);
static const char op3_tag[] = "op3";
const char *gen0XFFFF8090FFA272FC_parser(ast*, position*);
static const char gen0XFFFF8090FFA272FC_tag[] = "gen0XFFFF8090FFA272FC";
const char *expr2_parser(ast*, position*);
static const char expr2_tag[] = "expr2";
const char *op2_parser(ast*, position*);
static const char op2_tag[] = "op2";
const char *gen0XFFFF8090FFA27344_parser(ast*, position*);
static const char gen0XFFFF8090FFA27344_tag[] = "gen0XFFFF8090FFA27344";
const char *expr1_parser(ast*, position*);
static const char expr1_tag[] = "expr1";
const char *op1_parser(ast*, position*);
static const char op1_tag[] = "op1";
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
const char *gen0XFFFF8090FFA2747C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2747C_tag[] = "gen0XFFFF8090FFA2747C";
const char *compound_statement_parser(ast*, position*);
static const char compound_statement_tag[] = "compound_statement";
const char *dict_parser(ast*, position*);
static const char dict_tag[] = "dict";
const char *block_parser(ast*, position*);
static const char block_tag[] = "block";
const char *int_parser(ast*, position*);
static const char int_tag[] = "int";
const char *gen0XFFFF8090FFA274F4_parser(ast*, position*);
static const char gen0XFFFF8090FFA274F4_tag[] = "gen0XFFFF8090FFA274F4";
const char *int_b_parser(ast*, position*);
static const char int_b_tag[] = "int_b";
const char *gen0XFFFF8090FFA27524_parser(ast*, position*);
static const char gen0XFFFF8090FFA27524_tag[] = "gen0XFFFF8090FFA27524";
const char *int_o_parser(ast*, position*);
static const char int_o_tag[] = "int_o";
const char *gen0XFFFF8090FFA27554_parser(ast*, position*);
static const char gen0XFFFF8090FFA27554_tag[] = "gen0XFFFF8090FFA27554";
const char *int_h_parser(ast*, position*);
static const char int_h_tag[] = "int_h";
const char *gen0XFFFF8090FFA27584_parser(ast*, position*);
static const char gen0XFFFF8090FFA27584_tag[] = "gen0XFFFF8090FFA27584";
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
const char *gen0XFFFF8090FFA27614_parser(ast*, position*);
static const char gen0XFFFF8090FFA27614_tag[] = "gen0XFFFF8090FFA27614";
const char *gen0XFFFF8090FFA2762C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2762C_tag[] = "gen0XFFFF8090FFA2762C";
const char *complex_parser(ast*, position*);
static const char complex_tag[] = "complex";
const char *string_parser(ast*, position*);
static const char string_tag[] = "string";
const char *char_parser(ast*, position*);
static const char char_tag[] = "char";
const char *gen0XFFFF8090FFA2768C_parser(ast*, position*);
static const char gen0XFFFF8090FFA2768C_tag[] = "gen0XFFFF8090FFA2768C";
const char *whitespace_parser(ast*, position*);
static const char whitespace_tag[] = "whitespace";
const char *space_parser(ast*, position*);
static const char space_tag[] = "space";
const char *single_comment_parser(ast*, position*);
static const char single_comment_tag[] = "single_comment";
const char *multi_comment_parser(ast*, position*);
static const char multi_comment_tag[] = "multi_comment";
const char *gen0XFFFF8090FFA27704_parser(ast*, position*);
static const char gen0XFFFF8090FFA27704_tag[] = "gen0XFFFF8090FFA27704";
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
const char *gen0XFFFF8090FFA27914_parser(ast*, position*);
static const char gen0XFFFF8090FFA27914_tag[] = "gen0XFFFF8090FFA27914";
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

const char *gen0XFFFF8090FFA2705C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2705C_tag);
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
				err = gen0XFFFF8090FFA2705C_parser(c, p);
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
				err = expr10_parser(r, p);
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

const char *gen0XFFFF8090FFA270BC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA270BC_tag);
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
				err = op10_parser(t, p);
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
				err = expr9_parser(r, p);
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

const char *expr10_parser(ast *t, position *p){
	set_tag(t, expr10_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr9_parser(r, p);
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
				err = gen0XFFFF8090FFA270BC_parser(c, p);
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

const char *op10_parser(ast *t, position *p){
	set_tag(t, op10_tag);
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
				terr = read_string("=", t, p) ? NULL : "=";
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA27104_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27104_tag);
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
				err = op9_parser(t, p);
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
				err = expr8_parser(r, p);
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

const char *expr9_parser(ast *t, position *p){
	set_tag(t, expr9_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr8_parser(r, p);
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
				err = gen0XFFFF8090FFA27104_parser(c, p);
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

const char *op9_parser(ast *t, position *p){
	set_tag(t, op9_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA2714C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2714C_tag);
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
				err = op8_parser(t, p);
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
				err = expr7_parser(r, p);
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

const char *expr8_parser(ast *t, position *p){
	set_tag(t, expr8_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr7_parser(r, p);
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
				err = gen0XFFFF8090FFA2714C_parser(c, p);
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

const char *op8_parser(ast *t, position *p){
	set_tag(t, op8_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA27194_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27194_tag);
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
				err = op7_parser(t, p);
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
				err = expr6_parser(r, p);
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

const char *expr7_parser(ast *t, position *p){
	set_tag(t, expr7_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr6_parser(r, p);
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
				err = gen0XFFFF8090FFA27194_parser(c, p);
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

const char *op7_parser(ast *t, position *p){
	set_tag(t, op7_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	{
		const char *err = NULL;
		{
				err = read_string("~^", t, p) ? NULL : "~^";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF8090FFA271DC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA271DC_tag);
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
				err = op6_parser(t, p);
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
				err = expr5_parser(r, p);
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

const char *expr6_parser(ast *t, position *p){
	set_tag(t, expr6_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr5_parser(r, p);
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
				err = gen0XFFFF8090FFA271DC_parser(c, p);
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

const char *op6_parser(ast *t, position *p){
	set_tag(t, op6_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA27224_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27224_tag);
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
				err = op5_parser(t, p);
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
				err = expr4_parser(r, p);
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

const char *expr5_parser(ast *t, position *p){
	set_tag(t, expr5_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr4_parser(r, p);
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
				err = gen0XFFFF8090FFA27224_parser(c, p);
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

const char *op5_parser(ast *t, position *p){
	set_tag(t, op5_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA2726C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2726C_tag);
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
				err = op4_parser(t, p);
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
				err = expr3_parser(r, p);
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

const char *expr4_parser(ast *t, position *p){
	set_tag(t, expr4_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr3_parser(r, p);
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
				err = gen0XFFFF8090FFA2726C_parser(c, p);
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

const char *op4_parser(ast *t, position *p){
	set_tag(t, op4_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
		if(e.curr > s.curr){
			*p = e;
			return err;
		}
		return "<option of group>";
	}while(0);
	return NULL;
}

const char *gen0XFFFF8090FFA272B4_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA272B4_tag);
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
				err = op3_parser(t, p);
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
				err = expr2_parser(r, p);
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

const char *expr3_parser(ast *t, position *p){
	set_tag(t, expr3_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = expr2_parser(r, p);
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
				err = gen0XFFFF8090FFA272B4_parser(c, p);
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

const char *op3_parser(ast *t, position *p){
	set_tag(t, op3_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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

const char *gen0XFFFF8090FFA272FC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA272FC_tag);
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
				err = op2_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr2_parser(ast *t, position *p){
	set_tag(t, expr2_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			while(1){
				l = *p;
				c = alloc_ast();
				err = gen0XFFFF8090FFA272FC_parser(c, p);
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
				err = expr1_parser(r, p);
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

const char *op2_parser(ast *t, position *p){
	set_tag(t, op2_tag);
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

const char *gen0XFFFF8090FFA27344_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27344_tag);
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
				err = op1_parser(t, p);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *expr1_parser(ast *t, position *p){
	set_tag(t, expr1_tag);
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
				err = gen0XFFFF8090FFA27344_parser(c, p);
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

const char *op1_parser(ast *t, position *p){
	set_tag(t, op1_tag);
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

const char *gen0XFFFF8090FFA2747C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2747C_tag);
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
				err = gen0XFFFF8090FFA2747C_parser(c, p);
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

const char *gen0XFFFF8090FFA274F4_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA274F4_tag);
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
				err = gen0XFFFF8090FFA274F4_parser(c, p);
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

const char *gen0XFFFF8090FFA27524_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27524_tag);
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
				err = gen0XFFFF8090FFA27524_parser(c, p);
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

const char *gen0XFFFF8090FFA27554_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27554_tag);
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
				err = gen0XFFFF8090FFA27554_parser(c, p);
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

const char *gen0XFFFF8090FFA27584_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27584_tag);
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
				err = gen0XFFFF8090FFA27584_parser(c, p);
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

const char *gen0XFFFF8090FFA27614_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27614_tag);
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

const char *gen0XFFFF8090FFA2762C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2762C_tag);
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
				terr = gen0XFFFF8090FFA27614_parser(t, p);
		}
		if(!terr){break;}
		if(p->curr > s.curr){
			err = terr;
			e = *p;
			*p = s;
		}
		{
				terr = gen0XFFFF8090FFA2762C_parser(t, p);
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

const char *gen0XFFFF8090FFA2768C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA2768C_tag);
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
				err = gen0XFFFF8090FFA2768C_parser(c, p);
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

const char *gen0XFFFF8090FFA27704_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27704_tag);
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
				err = gen0XFFFF8090FFA27704_parser(c, p);
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

const char *gen0XFFFF8090FFA27914_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF8090FFA27914_tag);
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
				err = gen0XFFFF8090FFA27914_parser(c, p);
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

