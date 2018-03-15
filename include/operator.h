#ifndef __UM_OPERATOR_H__
#define __UM_OPERATOR_H__

#define OPERATOR_PRECEDENCE_LEVELS 13

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
	OP_MUL,//a*b
	OP_DIV,//a/b
	OP_MOD,//a%b
	OP_SMS,//a<<b
	OP_SLS,//a>>b
	OP_ADD,//a+b
	OP_SUB,//a-b
	OP_BAND,//a&b
	OP_BOR,//a|b
	OP_BXOR,//a^b
	OP_BNAND,//a~&b
	OP_BNOR,//a~|b
	OP_BXNOR,//a~^b
	OP_GT,//a>b
	OP_LT,//a<b
	OP_GTE,//a>=b
	OP_LTE,//a<=b
	OP_EQ,//a==b
	OP_NEQ,//a!=b
	OP_ORD,//a<=>b
	OP_IN,//a<-b
	OP_LAND,//a&&b
	OP_LOR,//a||b
	OP_LXOR,//a^^b
	OP_LNAND,//a!&&b
	OP_LNOR,//a!||b
	OP_LXNOR,//a!^^b
	OP_FUN,//a->b
	OP_SET,//a=b
	OP_CCURRY,//a$=b
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
	OP_ENUM_COUNT,//enum constant equal to the number of actual operators.  operarors after this are synthetic
	OP_CSTMT,//indicates compound statement name (eg if, while, ...)
	OP_CSTMT_ARGS,//indicates arguments for compound statement
} operator;

operator str_prefix_to_op(const char *s);
operator str_infix_to_op(const char *s);

extern const unsigned op_precedence[OP_ENUM_COUNT];
extern const int op_associativity[OPERATOR_PRECEDENCE_LEVELS];

#endif

