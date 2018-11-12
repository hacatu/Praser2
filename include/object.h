#ifndef __UM_OBJECT_H__
#define __UM_OBJECT_H__

#include <stddef.h>
#include <inttypes.h>
#include <complex.h>
#include "avl.h"
#include "ll.h"

typedef enum{
	VTYPE_VOID,
	VTYPE_I,//natural number
	VTYPE_Z,//integer
	VTYPE_Q,//rational number
	VTYPE_R,//double
	VTYPE_CZ,//complex integer
	VTYPE_CQ,//complex rational
	VTYPE_CR,//complex double
	VTYPE_CH,//char
	VTYPE_STR,//string
	VTYPE_OBJ,//object
	VTYPE_BLOCK,//code block
	VTYPE_LIST,//list block
	VTYPE_DICT,//dict block
} vtype;

typedef struct{
	size_t len;
	char buf[];
} vstr;

typedef struct object object;
struct object{
	size_t srefs;
	char gc_visited;
	uint64_t tid;
	avl_node *members;/*(char* -> value)*/
	avl_node *interfaces;/*(char* -> value)*/
	avl_node *dict;/*(value -> value)*/
	avl_node *list;/*(size_t -> value)*/
	size_t index_acc;
};

typedef struct value value;
struct value{
	ll_node *cleanup;
	vtype type;
	void *data;
};

typedef struct{char *key; value val;} avl_node_char__value;
extern avl_ft avl_ft_char__value;
typedef struct{size_t key; value val;} avl_node_size_value;
extern avl_ft avl_ft_size_value;
typedef struct{value key; value val;} avl_node_value_value;
extern avl_ft avl_ft_value_value;

void print_value(const value *val, size_t indent);

#endif

