#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

const unsigned op_precedence[OP_ENUM_COUNT];
const int op_associativity[OPERATOR_PRECEDENCE_LEVELS];

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

operator str_infix_to_op(const char *s){//STRONGLY assumes valid input
	switch(s[0]){
	case '$': return s[1] ? OP_CCURRY : OP_CURRY;
	case ':': return OP_CAST;
	case '*': return s[1] ? OP_CMUL : OP_MUL;
	case '/': return s[1] ? OP_CDIV : OP_DIV;
	case '%': return s[1] ? OP_CMOD : OP_MOD;
	case '<':
		switch(s[1]){
		case '<': return s[2] ? OP_CSMS : OP_SMS;
		case '=': return s[2] ? OP_ORD : OP_LTE;
		case '-': return OP_IN;
		}
		return OP_LT;
	case '>':
		switch(s[1]){
		case '>': return s[2] ? OP_CSLS : OP_SLS;
		case '=': return OP_GTE;
		}
		return OP_GT;
	case '+': return s[1] ? OP_CADD : OP_ADD;
	case '-':
		switch(s[1]){
		case '=': return OP_CSUB;
		case '>': return OP_FUN;
		}
		return OP_SUB;
	case '&':
		switch(s[1]){
		case '=': return OP_CBAND;
		case '&': return s[2] ? OP_CLAND : OP_LAND;
		}
		return OP_BAND;
	case '|':
		switch(s[1]){
		case '=': return OP_CBOR;
		case '|': return s[2] ? OP_CLOR : OP_LOR;
		}
		return OP_BOR;
	case '^':
		switch(s[1]){
		case '=': return OP_CBXOR;
		case '^': return s[2] ? OP_CLXOR : OP_LXOR;
		}
		return OP_BXOR;
	case '~':
		switch(s[1]){
		case '&': return s[2] ? OP_CBNAND : OP_BNAND;
		case '|': return s[2] ? OP_CBNOR : OP_BNOR;
		}
		return s[2] ? OP_CBXNOR : OP_BXNOR;
	case '=': return s[1] ? OP_EQ : OP_SET;
	}
	switch(s[1]){
	case '=': return OP_NEQ;
	case '&': return s[3] ? OP_CLNAND : OP_LNAND;
	case '|': return s[3] ? OP_CLNOR : OP_LNOR;
	}
	return s[3] ? OP_CLXNOR : OP_LXNOR;
}

//set up a top level frame with bindings to the regular variables.
//right now I don't know what these should be and the general philosophy
//of umbrella is that there should be as few as possible until you import something, so import is probably a good start.
void um_init_global_frame(frame *global){
	*global = (frame){};
	global->type = FRAME_CODE;
	avl_insert(&global->variables, &(avl_node_char__value){"import", NULL}, &avl_ft_char__value);
}

void um_eval(value *out, block *r, frame *scope, value *cntr);

