#ifndef __UM_EXPRESSION_H__
#define __UM_EXPRESSION_H__

#include <stddef.h>
#include "avl.h"
#include "operator.h"
#include "object.h"

typedef enum{
	//atom= compound_statement | identifier | literal | parens | implicit__
	ATOM_IDENT,
	ATOM_VALUE,
	ATOM_EXPR,
	ATOM_BLOCK,
} atom_type;

typedef enum{
	FRAME_CODE,
	FRAME_OBJECT,
} frame_type;

typedef struct expression expression;
struct expression{
	operator op;
	size_t len;
	atom_type type;
	void *args[2];
};

typedef struct{
	size_t len;
	size_t tag_len;
	char *tag;
	avl_node *labels;/*(char* -> expression*)*/
	expression *statements;
} block;

typedef struct frame frame;
struct frame{
	avl_node *variables;/*(char* -> value)*/
	frame *closure;
	value *container;
	frame_type type;
	block block;
};

typedef struct{char *key; expression *val;} avl_node_char__expression_;
extern avl_ft avl_ft_char__expression_;

void print_expression(const expression *expr, size_t indent);
void print_block(const block *b, size_t indent);

#endif

