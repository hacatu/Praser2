#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"

avl_ft avl_ft_char__value;
avl_ft avl_ft_size_value;
avl_ft avl_ft_value_value;
avl_ft avl_ft_char__expression_;

operator str_prefix_to_op(const char *s){//STRONGLY assumes valid input
	switch(s[0]){
	case '@': return OP_NEWL;
	case '+': return s[1] ? OP_INCL : OP_POS;
	case '-': return s[1] ? OP_DECL : OP_NEG;
	case '!': return OP_NOT;
	case '~': return OP_INV;
	case '&': return OP_REF;
	}
	return OP_DREF;
}

operator str_infix_to_op(const char *s, size_t len){//STRONGLY assumes valid input
	switch(s[0]){
	case '$': return len == 2 ? OP_CCURRY : OP_CURRY;
	case ':': return OP_CAST;
	case '*':
		if(len == 1){
			return OP_MUL;
		}
		if(s[1] == '*'){
			return len == 3 ? OP_CEXP : OP_EXP;
		}
		return OP_CMUL;
	case '/': return len == 2 ? OP_CDIV : OP_DIV;
	case '%': return len == 2 ? OP_CMOD : OP_MOD;
	case ',': return OP_TUPLE;
	case '<':
		if(len == 1){
			return OP_LT;
		}
		switch(s[1]){
		case '<': return len == 3 ? OP_CSMS : OP_SMS;
		case '=': return len == 3 ? OP_ORD : OP_LTE;
		}
		/*otherwise we have <-*/return OP_IN;
	case '>':
		if(len == 1){
			return OP_GT;
		}
		if(s[1] == '>'){
			return len == 3 ? OP_CSLS : OP_SLS;
		}
		/*otherwise we have >=*/return OP_GTE;
	case '+': return len == 2 ? OP_CADD : OP_ADD;
	case '-':
		if(len == 1){
			return OP_SUB;
		}
		if(s[1] == '='){
			return OP_CSUB;
		}
		/*otherwise we have ->*/return OP_FUN;
	case '&':
		if(len == 1){
			return OP_BAND;
		}
		if(s[1] == '='){
			return OP_CBAND;
		}
		/*otherwise we have &&*/return len == 3 ? OP_CLAND : OP_LAND;
	case '|':
		if(len == 1){
			return OP_BOR;
		}
		if(s[1] == '='){
			return OP_CBOR;
		}
		/*otherwise we have ||*/return len == 3 ? OP_CLOR : OP_LOR;
	case '^':
		if(len == 1){
			return OP_BXOR;
		}
		if(s[1] == '='){
			return OP_CBXOR;
		}
		/*otherwise we have ^^*/return len == 3 ? OP_CLXOR : OP_LXOR;
	case '~':
		switch(s[1]){
		case '&': return len == 3 ? OP_CBNAND : OP_BNAND;
		case '|': return len == 3 ? OP_CBNOR : OP_BNOR;
		}
		return len == 3 ? OP_CBXNOR : OP_BXNOR;
	case '=': return len == 2 ? OP_EQ : OP_SET;
	}
	switch(s[1]){
	case '=': return OP_NEQ;
	case '&': return len == 4 ? OP_CLNAND : OP_LNAND;
	case '|': return len == 4 ? OP_CLNOR : OP_LNOR;
	}
	return len == 4 ? OP_CLXNOR : OP_LXNOR;
}

void print_expression(const expression *expr, size_t indent){
	const char *type_name = "";
	switch(expr->type){
		case ATOM_IDENT:
			type_name = "ATOM_IDENT";
			break;
		case ATOM_VALUE:
			type_name = "ATOM_VALUE";
			break;
		case ATOM_EXPR:
			type_name = "ATOM_EXPR";
			break;
		case ATOM_BLOCK:
			type_name = "ATOM_BLOCK";
			break;
	}
	printf(
		"{\n"
		"%*s.op=%s,\n"
		"%*s.len=%zu,\n"
		"%*s.type=%s,",
		(int)indent, "", op_traits[expr->op].name,
		(int)indent, "", expr->len,
		(int)indent, "", type_name);
	for(size_t i = 0; i < expr->len; ++i){
		printf("\n%*s.args[%zu]=", (int)indent, "", i);
		switch(expr->type){
			case ATOM_IDENT:
				printf("\"%s\"", (char*)expr->args[i]);
				break;
			case ATOM_VALUE:
				print_value(expr->args[i], indent + 1);
				break;
			case ATOM_EXPR:
				print_expression(expr->args[i], indent + 1);
				break;
			case ATOM_BLOCK:
				print_block(expr->args[i], indent + 1);
				break;
		}
		putchar(',');
	}
	puts("}");
}

void print_block(const block *b, size_t indent){
	printf(
		"{\n"
		"%*s.len=%zu,\n"
		"%*s.tag_len%zu,\n"
		"%*s.tag=%.*s,\n"
		"%*s.labels=%p,",
		(int)indent, "", b->len,
		(int)indent, "", b->tag_len,
		(int)indent, "", (int)b->tag_len, b->tag,
		(int)indent, "", b->labels);
	for(size_t i = 0; i < b->len; ++i){
		printf("\n%*s.statements[%zu]=", (int)indent, "", i);
		print_expression(b->statements + i, indent + 1);
		putchar(',');
	}
	puts("}");
}

void print_value(const value *val, size_t indent){
	switch(val->type){
		case VTYPE_VOID:
			printf("VTYPE_VOID");
			break;
		case VTYPE_I://natural number
			printf("VTYPE_I:%u", (unsigned)(uintptr_t)val->data);
			break;
		case VTYPE_Z://integer
			printf("VTYPE_Z:%d", (int)(intptr_t)val->data);
			break;
		case VTYPE_Q://rational number
			printf("VTYPE_Q:%d/%d", ((int*)val->data)[0], ((int*)val->data)[1]);
			break;
		case VTYPE_R://double
			printf("VTYPE_R:%f", *(double*)&val->data);
			break;
		case VTYPE_CZ://complex integer
			printf("VTYPE_CZ:%d + %dI", ((int*)val->data)[0], ((int*)val->data)[1]);
			break;
		case VTYPE_CQ://complex rational
			printf("VTYPE_CQ:%d/%d + %d/%d I", ((int*)val->data)[0], ((int*)val->data)[1], ((int*)val->data)[2], ((int*)val->data)[3]);
			break;
		case VTYPE_CR://complex double
			printf("VTYPE_CR:%f + %fI", creal(*(double complex*)val->data), cimag(*(double complex*)val->data));
			break;
		case VTYPE_CH://char
			printf("VTYPE_CH:");
			if(isprint((char)(intptr_t)val->data)){
				printf("\'%c\'", (char)(intptr_t)val->data);
			}else{
				printf("0x%2hhx", (unsigned char)(intptr_t)val->data);
			}
			break;
		case VTYPE_STR://string
			printf("VTYPE_STR:[%zu]\"%.*s\"", ((vstr*)val->data)->len, (int)((vstr*)val->data)->len, ((vstr*)val->data)->buf);
			break;
		case VTYPE_OBJ://object
			printf("VTYPE_OBJ:<printing objects nyi>");
			break;
		case VTYPE_BLOCK://code block
			printf("VTYPE_BLOCK:");
			print_block(val->data, indent);
			break;
		case VTYPE_LIST://list block
			printf("VTYPE_LIST:");
			print_block(val->data, indent);
			break;
		case VTYPE_DICT://dict block
			printf("VTYPE_DICT:");
			print_block(val->data, indent);
			break;
	}
}

//set up a top level frame with bindings to the regular variables.
//right now I don't know what these should be and the general philosophy
//of umbrella is that there should be as few as possible until you import something, so import is probably a good start.
void um_init_global_frame(frame *global){
	*global = (frame){};
	global->type = FRAME_CODE;
	avl_insert(&global->variables, &(avl_node_char__value){"import", {0}}, &avl_ft_char__value);
}

void um_eval(value *out, block *r, frame *scope, value *cntr);

operator_traits op_traits[OP_ENUM_COUNT] = {
	[OP_ID]={"OP_ID", "a", "", 0, OP_ASSOC_COMPOUND, 1, 1, OP_ID},
	[OP_NEWL]={"OP_NEWL", "@a", "@", 0, OP_ASSOC_LEFT, 1, 1, OP_ENUM_COUNT},
	[OP_INCR]={"OP_INCR", "a++", "++", 1, OP_ASSOC_RIGHT, 1, 1, OP_DECR},
	[OP_DECR]={"OP_DECR", "a--", "--", 1, OP_ASSOC_RIGHT, 1, 1, OP_INCR},
	[OP_SPLAT]={"OP_SPLAT", "a..", "..", 1, OP_ASSOC_RIGHT, 1, 1, OP_ENUM_COUNT},
	[OP_MAYBE]={"OP_MAYBE", "a?", "?", 1, OP_ASSOC_RIGHT, 1, 1, OP_SPLAT},
	[OP_APP]={"OP_APP", "a()", "()", 1, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_IDX]={"OP_IDX", "a[]", "[]", 1, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_NEWM]={"OP_NEWM", "a@b", "@", 1, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_GET]={"OP_GET", "a.b", ".", 1, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_INCL]={"OP_INCL", "++a", "++", 2, OP_ASSOC_LEFT, 1, 1, OP_DECL},
	[OP_DECL]={"OP_DECL", "--a", "--", 2, OP_ASSOC_LEFT, 1, 1, OP_INCL},
	[OP_POS]={"OP_POS", "+a", "+", 2, OP_ASSOC_LEFT, 1, 1, OP_POS},
	[OP_NEG]={"OP_NEG", "-a", "-", 2, OP_ASSOC_LEFT, 1, 1, OP_NEG},
	[OP_NOT]={"OP_NOT", "!a", "!", 2, OP_ASSOC_LEFT, 1, 1, OP_NOT},
	[OP_INV]={"OP_INV", "~a", "~", 2, OP_ASSOC_LEFT, 1, 1, OP_INV},
	[OP_REF]={"OP_REF", "&a", "&", 2, OP_ASSOC_LEFT, 1, 1, OP_DREF},
	[OP_DREF]={"OP_DREF", "*a", "*", 2, OP_ASSOC_LEFT, 1, 1, OP_REF},
	[OP_CAST]={"OP_CAST", "a:b", ":", 3, OP_ASSOC_RIGHT, 2, 2, OP_CAST},
	[OP_CURRY]={"OP_CURRY", "a$b", "$", 4, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_EXP]={"OP_EXP", "a**b", "**", 5, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_MUL]={"OP_MUL", "a*b", "*", 6, OP_ASSOC_BOTH, 1, 0, OP_DIV},
	[OP_DIV]={"OP_DIV", "a/b", "/", 6, OP_ASSOC_LEFT, 2, 2, OP_MUL},
	[OP_MOD]={"OP_MOD", "a%b", "%", 6, OP_ASSOC_LEFT, 2, 2, OP_ID},
	[OP_SMS]={"OP_SMS", "a<<b", "<<", 7, OP_ASSOC_LEFT, 2, 2, OP_SLS},
	[OP_SLS]={"OP_SLS", "a>>b", ">>", 7, OP_ASSOC_LEFT, 2, 2, OP_SMS},
	[OP_ADD]={"OP_ADD", "a+b", "+", 8, OP_ASSOC_BOTH, 1, 0, OP_SUB},
	[OP_SUB]={"OP_SUB", "a-b", "-", 8, OP_ASSOC_LEFT, 2, 2, OP_ADD},
	[OP_BAND]={"OP_BAND", "a&b", "&", 9, OP_ASSOC_BOTH, 1, 0, OP_ENUM_COUNT},
	[OP_BOR]={"OP_BOR", "a|b", "|", 9, OP_ASSOC_BOTH, 1, 0, OP_ENUM_COUNT},
	[OP_BXOR]={"OP_BXOR", "a^b", "|", 9, OP_ASSOC_BOTH, 1, 0, OP_BXOR},
	[OP_BNAND]={"OP_BNAND", "a~&b", "~&", 9, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_BNOR]={"OP_BNOR", "a~|b", "~|", 9, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_BXNOR]={"OP_BXNOR", "a~^b", "~^", 9, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_TUPLE]={"OP_TUPLE", "a,b", ",", 10, OP_ASSOC_LEFT, 0, 0, OP_SPLAT},
	[OP_GT]={"OP_GT", "a>b", ">", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_LT]={"OP_LT", "a<b", "<", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_GTE]={"OP_GTE", "a>=b", ">=", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_LTE]={"OP_LTE", "a<=b", "<=", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_EQ]={"OP_EQ", "a==b", "==", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_NEQ]={"OP_NEQ", "a!=b", "!=", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_ORD]={"OP_ORD", "a<=>b", "<=>", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_IN]={"OP_IN", "a<-b", "<-", 11, OP_ASSOC_COMPOUND, 2, 2, OP_ENUM_COUNT},
	[OP_LAND]={"OP_LAND", "a&&b", "&&", 12, OP_ASSOC_BOTH, 0, 0, OP_ENUM_COUNT},
	[OP_LOR]={"OP_LOR", "a||b", "||", 12, OP_ASSOC_BOTH, 0, 0, OP_ENUM_COUNT},
	[OP_LXOR]={"OP_LXOR", "a^^b", "^^", 12, OP_ASSOC_BOTH, 0, 0, OP_ENUM_COUNT},
	[OP_LNAND]={"OP_LNAND", "a!&&b", "!&&", 12, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_LNOR]={"OP_LNOR", "a!||b", "!||", 12, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_LXNOR]={"OP_LXNOR", "a!^^b", "!^^", 12, OP_ASSOC_LEFT, 2, 2, OP_ENUM_COUNT},
	[OP_FUN]={"OP_FUN", "a->b", "->", 13, OP_ASSOC_RIGHT, 2, 2, OP_APP},
	[OP_SET]={"OP_SET", "a=b", "=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CCURRY]={"OP_CCURRY", "a$=b", "$=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CEXP]={"OP_CEXP", "a**=b", "**=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CMUL]={"OP_CMUL", "a*=b", "*=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CDIV]={"OP_CDIV", "a/=b", "/=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CMOD]={"OP_CMOD", "a%=b", "%=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CSMS]={"OP_CSMS", "a<<=b", "<<=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CSLS]={"OP_CSLS", "a>>=b", ">>=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CADD]={"OP_CADD", "a+=b", "+=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CSUB]={"OP_CSUB", "a-=b", "-=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBAND]={"OP_CBAND", "a&=b", "&=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBOR]={"OP_CBOR", "a|=b", "|=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBXOR]={"OP_CBXOR", "a^=b", "^=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBNAND]={"OP_CBNAND", "a~&=b", "~&=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBNOR]={"OP_CBNOR", "a~|=b", "~|=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CBXNOR]={"OP_CBXNOR", "a~^=b", "~^=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLAND]={"OP_CLAND", "a&&=b", "&&=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLOR]={"OP_CLOR", "a||=b", "||=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLXOR]={"OP_CLXOR", "a^^=b", "^^=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLNAND]={"OP_CLNAND", "a!&&=b", "!&&=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLNOR]={"OP_CLNOR", "a!||=b", "!||=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
	[OP_CLXNOR]={"OP_CLXNOR", "a!^^=b", "!^^=", 13, OP_ASSOC_RIGHT, 2, 2, OP_ENUM_COUNT},
};

operator_assoc op_prec_assocs[MAX_PRECEDENCE] = {
	[0]=OP_ASSOC_COMPOUND,
	[1]=OP_ASSOC_RIGHT,
	[2]=OP_ASSOC_LEFT,
	[3]=OP_ASSOC_LEFT,
	[4]=OP_ASSOC_RIGHT,
};

