#ifndef __UM_OBJECT_H__
#define __UM_OBJECT_H__

#include "avl.h"

typedef enum{
	OP_ID,
	OP_NEWL,
	OP_INCR,
	OP_DECR,
	OP_SPLAT,
	OP_MAYBE,
	OP_APP,
	OP_IDX,
	OP_NEWM,
	OP_GET,
	OP_INCL,
	OP_DECL,
	OP_POS,
	OP_NEG,
	OP_NOT,
	OP_INV,
	OP_REF,
	OP_DREF,
	OP_CURRY,
	OP_CAST,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_SMS,
	OP_SLS,
	OP_ADD,
	OP_SUB,
	OP_BAND,
	OP_BOR,
	OP_BXOR,
	OP_BNAND,
	OP_BNOR,
	OP_BXNOR,
	OP_GT,
	OP_LT,
	OP_GTE,
	OP_LTE,
	OP_EQ,
	OP_NEQ,
	OP_ORD,
	OP_IN,
	OP_LAND,
	OP_LOR,
	OP_LXOR,
	OP_LNAND,
	OP_LNOR,
	OP_LXNOR,
	OP_FUN,
	OP_SET,
	OP_CCURRY,
	OP_CMUL,
	OP_CDIV,
	OP_CMOD,
	OP_CSMS,
	OP_CSLS,
	OP_CADD,
	OP_CSUB,
	OP_CBAND,
	OP_CBOR,
	OP_CBXOR,
	OP_CBNAND,
	OP_CBNOR,
	OP_CBXNOR,
	OP_CLAND,
	OP_CLOR,
	OP_CLXOR,
	OP_CLNAND,
	OP_CLNOR,
	OP_CLXNOR,
} operator;

typedef struct expression expression;
struct expression{
	operator op;
	char assign_undesignated;
	void *args;
};

typedef struct frame frame;
struct frame{
	avl_node *variables;
	frame *closure;
	size_t statements_len;
	expression *statements;
};

#endif

