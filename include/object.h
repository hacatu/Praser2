#ifndef __UM_OBJECT_H__
#define __UM_OBJECT_H__

#include <stddef.h>
#include <inttypes.h>
#include "avl.h"

typedef enum{
	VTYPE_VOID,
	VTYPE_I,
	VTYPE_Z,
	VTYPE_Q,
	VTYPE_R,
	VTYPE_CI,
	VTYPE_CZ,
	VTYPE_CQ,
	VTYPE_CR,
	VTYPE_STR,
	VTYPE_OBJ,
	VTYPE_BLOCK,
} vtype;

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

#endif

