#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

const char *start_parser(ast*, position*);
static const char start_tag[] = "start";
const char *rule_parser(ast*, position*);
static const char rule_tag[] = "rule";
const char *name_parser(ast*, position*);
static const char name_tag[] = "name";
const char *assign_parser(ast*, position*);
static const char assign_tag[] = "assign";
const char *gen0XFFFF80E3ED3AA6FC_parser(ast*, position*);
static const char gen0XFFFF80E3ED3AA6FC_tag[] = "gen0XFFFF80E3ED3AA6FC";
const char *pattern_parser(ast*, position*);
static const char pattern_tag[] = "pattern";
const char *gen0XFFFF80E3ED3AA72C_parser(ast*, position*);
static const char gen0XFFFF80E3ED3AA72C_tag[] = "gen0XFFFF80E3ED3AA72C";
const char *group_parser(ast*, position*);
static const char group_tag[] = "group";
const char *option_parser(ast*, position*);
static const char option_tag[] = "option";
const char *atom_parser(ast*, position*);
static const char atom_tag[] = "atom";
const char *quantifier_parser(ast*, position*);
static const char quantifier_tag[] = "quantifier";
const char *parens_parser(ast*, position*);
static const char parens_tag[] = "parens";
const char *gen0XFFFF80E3ED3AA7BC_parser(ast*, position*);
static const char gen0XFFFF80E3ED3AA7BC_tag[] = "gen0XFFFF80E3ED3AA7BC";
const char *invset_parser(ast*, position*);
static const char invset_tag[] = "invset";
const char *gen0XFFFF80E3ED3AA7EC_parser(ast*, position*);
static const char gen0XFFFF80E3ED3AA7EC_tag[] = "gen0XFFFF80E3ED3AA7EC";
const char *charset_parser(ast*, position*);
static const char charset_tag[] = "charset";
const char *setrange_parser(ast*, position*);
static const char setrange_tag[] = "setrange";
const char *setchar_parser(ast*, position*);
static const char setchar_tag[] = "setchar";
const char *gen0XFFFF80E3ED3AA84C_parser(ast*, position*);
static const char gen0XFFFF80E3ED3AA84C_tag[] = "gen0XFFFF80E3ED3AA84C";
const char *string_parser(ast*, position*);
static const char string_tag[] = "string";
const char *whitespace_parser(ast*, position*);
static const char whitespace_tag[] = "whitespace";
const char *lparen_parser(ast*, position*);
static const char lparen_tag[] = "lparen";
const char *rparen_parser(ast*, position*);
static const char rparen_tag[] = "rparen";
const char *lbracket_parser(ast*, position*);
static const char lbracket_tag[] = "lbracket";
const char *rbracket_parser(ast*, position*);
static const char rbracket_tag[] = "rbracket";
const char *caret_parser(ast*, position*);
static const char caret_tag[] = "caret";
const char *quote_parser(ast*, position*);
static const char quote_tag[] = "quote";
const char *bar_parser(ast*, position*);
static const char bar_tag[] = "bar";
const char *dash_parser(ast*, position*);
static const char dash_tag[] = "dash";
const char *backslash_parser(ast*, position*);
static const char backslash_tag[] = "backslash";
const char *newline_parser(ast*, position*);
static const char newline_tag[] = "newline";

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
				err = rule_parser(r, p);
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

const char *rule_parser(ast *t, position *p){
	set_tag(t, rule_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = name_parser(r, p);
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
				ast *r = alloc_ast();
				err = assign_parser(r, p);
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
				ast *r = alloc_ast();
				err = pattern_parser(r, p);
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
				err = newline_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *name_parser(ast *t, position *p){
	set_tag(t, name_tag);
	{
		const char *err = NULL;
		{
			position l;
			ast *c;
			char matched = 0;
			while(1){
				l = *p;
				c = alloc_ast();
				err = read_charset_prefix("+-az-AZ-09._", c, p) ? NULL : "+-az-AZ-09._";
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

const char *assign_parser(ast *t, position *p){
	set_tag(t, assign_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.:.=.<", t, p) ? NULL : "+.:.=.<";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *gen0XFFFF80E3ED3AA6FC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF80E3ED3AA6FC_tag);
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
				err = group_parser(r, p);
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

const char *pattern_parser(ast *t, position *p){
	set_tag(t, pattern_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = group_parser(r, p);
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
				err = gen0XFFFF80E3ED3AA6FC_parser(c, p);
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

const char *gen0XFFFF80E3ED3AA72C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF80E3ED3AA72C_tag);
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
				err = bar_parser(r, p);
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
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = option_parser(r, p);
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

const char *group_parser(ast *t, position *p){
	set_tag(t, group_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = option_parser(r, p);
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
				err = gen0XFFFF80E3ED3AA72C_parser(c, p);
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

const char *option_parser(ast *t, position *p){
	set_tag(t, option_tag);
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
				err = quantifier_parser(r, p);
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

const char *atom_parser(ast *t, position *p){
	set_tag(t, atom_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
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
				terr = name_parser(r, p);
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
				terr = invset_parser(r, p);
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
				terr = charset_parser(r, p);
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

const char *quantifier_parser(ast *t, position *p){
	set_tag(t, quantifier_tag);
	{
		const char *err = NULL;
		{
				err = read_charset_prefix("+.+.*.?", t, p) ? NULL : "+.+.*.?";
		}
		if(err){
			return err;
		}
	}
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
				err = pattern_parser(r, p);
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

const char *gen0XFFFF80E3ED3AA7BC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF80E3ED3AA7BC_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = setrange_parser(r, p);
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
				terr = setchar_parser(r, p);
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

const char *invset_parser(ast *t, position *p){
	set_tag(t, invset_tag);
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
				ast *r = &(ast){0};
				err = caret_parser(r, p);
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
				err = gen0XFFFF80E3ED3AA7BC_parser(c, p);
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

const char *gen0XFFFF80E3ED3AA7EC_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF80E3ED3AA7EC_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				ast *r = alloc_ast();
				terr = setrange_parser(r, p);
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
				terr = setchar_parser(r, p);
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

const char *charset_parser(ast *t, position *p){
	set_tag(t, charset_tag);
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
				err = gen0XFFFF80E3ED3AA7EC_parser(c, p);
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

const char *setrange_parser(ast *t, position *p){
	set_tag(t, setrange_tag);
	{
		const char *err = NULL;
		{
				ast *r = alloc_ast();
				err = setchar_parser(r, p);
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
				err = dash_parser(r, p);
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
				err = setchar_parser(r, p);
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

const char *setchar_parser(ast *t, position *p){
	set_tag(t, setchar_tag);
	do{
		const char *err = NULL, *terr = NULL;
		position s = *p, e = s;
		{
				terr = read_charset_prefix("-.\\.-.]", t, p) ? NULL : "-.\\.-.]";
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

const char *gen0XFFFF80E3ED3AA84C_parser(ast *t, position *p){
	set_tag(t, gen0XFFFF80E3ED3AA84C_tag);
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

const char *string_parser(ast *t, position *p){
	set_tag(t, string_tag);
	{
		const char *err = NULL;
		{
				ast *r = &(ast){0};
				err = quote_parser(r, p);
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
				err = gen0XFFFF80E3ED3AA84C_parser(c, p);
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
				err = quote_parser(r, p);
				clear_ast(r);
		}
		if(err){
			return err;
		}
	}
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
				err = read_charset_prefix("+. .\t", c, p) ? NULL : "+. .\t";
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

const char *lbracket_parser(ast *t, position *p){
	set_tag(t, lbracket_tag);
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

const char *rbracket_parser(ast *t, position *p){
	set_tag(t, rbracket_tag);
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

const char *caret_parser(ast *t, position *p){
	set_tag(t, caret_tag);
	{
		const char *err = NULL;
		{
				err = read_string("^", t, p) ? NULL : "^";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *quote_parser(ast *t, position *p){
	set_tag(t, quote_tag);
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

const char *bar_parser(ast *t, position *p){
	set_tag(t, bar_tag);
	{
		const char *err = NULL;
		{
				err = read_string("|", t, p) ? NULL : "|";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *dash_parser(ast *t, position *p){
	set_tag(t, dash_tag);
	{
		const char *err = NULL;
		{
				err = read_string("-", t, p) ? NULL : "-";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *backslash_parser(ast *t, position *p){
	set_tag(t, backslash_tag);
	{
		const char *err = NULL;
		{
				err = read_string("\\", t, p) ? NULL : "\\";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

const char *newline_parser(ast *t, position *p){
	set_tag(t, newline_tag);
	{
		const char *err = NULL;
		{
				err = read_string("\n", t, p) ? NULL : "\n";
		}
		if(err){
			return err;
		}
	}
	return NULL;
}

