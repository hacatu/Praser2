#ifndef __UM_OPERATOR_H__
#define __UM_OPERATOR_H__

#define MIN_INFIX_PRECEDENCE 3
#define COMPARISON_PRECEDENCE 9
#define MAX_PRECEDENCE 14

typedef enum{
	OP_ID,//no operator
	OP_NEWL,//@a		new local
	OP_INCR,//a++
	OP_DECR,//a--
	OP_SPLAT,//a..
	OP_MAYBE,//a?
	OP_APP,//a()
	OP_IDX,//a[]
	OP_NEWM,//a@b		new member
	OP_GET,//a.b
	OP_INCL,//++a
	OP_DECL,//--a
	OP_POS,//+a
	OP_NEG,//-a
	OP_NOT,//!a
	OP_INV,//~a
	OP_REF,//&a
	OP_DREF,//*a
	OP_CURRY,//a$b
	OP_CAST,//a:b
	OP_EXP,//a**b
	OP_MUL,//a*b		this operator takes 2+ arguments
	OP_DIV,//a/b
	OP_MOD,//a%b
	OP_SMS,//a<<b
	OP_SLS,//a>>b
	OP_ADD,//a+b		this operator takes 2+ arguments
	OP_SUB,//a-b
	OP_BAND,//a&b		this operator takes 2+ arguments
	OP_BOR,//a|b		this operator takes 2+ arguments
	OP_BXOR,//a^b		this operator takes 2+ arguments
	OP_BNAND,//a~&b
	OP_BNOR,//a~|b
	OP_BXNOR,//a~^b
	OP_TUPLE,//a,b		this operator takes 1+ arguments
	OP_GT,//a>b
	OP_LT,//a<b
	OP_GTE,//a>=b
	OP_LTE,//a<=b
	OP_EQ,//a==b		this operator takes 2+ arguments
	OP_NEQ,//a!=b
	OP_ORD,//a<=>b
	OP_IN,//a<-b
	OP_LAND,//a&&b		this operator takes 2+ arguments
	OP_LOR,//a||b		this operator takes 2+ arguments
	OP_LXOR,//a^^b		this operator takes 2+ arguments
	OP_LNAND,//a!&&b
	OP_LNOR,//a!||b
	OP_LXNOR,//a!^^b
	OP_FUN,//a->b
	OP_SET,//a=b
	OP_CCURRY,//a$=b
	OP_CEXP,//**=
	OP_CMUL,//a*=b
	OP_CDIV,//a/=b
	OP_CMOD,//a%=b
	OP_CSMS,//a<<=b
	OP_CSLS,//a>>=b
	OP_CADD,//a+=b
	OP_CSUB,//a-=b
	OP_CBAND,//a&=b
	OP_CBOR,//a|=b
	OP_CBXOR,//a^=b
	OP_CBNAND,//a~&=b
	OP_CBNOR,//a~|=b
	OP_CBXNOR,//a~^=b
	OP_CLAND,//a&&=b
	OP_CLOR,//a||=b
	OP_CLXOR,//a^^=b
	OP_CLNAND,//a!&&=b
	OP_CLNOR,//a!||=b
	OP_CLXNOR,//a!^^=b
	OP_ENUM_COUNT,//operarors after this are synthetic
} operator;

typedef enum{
	OP_ASSOC_COMPOUND = 0,
	OP_ASSOC_LEFT = 1,
	OP_ASSOC_RIGHT = 2,
	OP_ASSOC_BOTH = 3,
} operator_assoc;

typedef struct{
	const char *name;
	const char *example;
	const char *symbol;
	size_t precedence;
	operator_assoc assoc;
	size_t min_args;
	size_t max_args;
	operator inverse;
} operator_traits;

operator str_prefix_to_op(const char *s);
operator str_infix_to_op(const char *s, size_t len);

extern operator_traits op_traits[OP_ENUM_COUNT];
extern operator_assoc op_prec_assocs[MAX_PRECEDENCE];

#endif

