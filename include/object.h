#ifndef __UM_OBJECT_H__
#define __UM_OBJECT_H__

#include "avl.h"

typedef enum{
	VTYPE_I,
	VTYPE_Z,
	VTYPE_Q,
	VTYPE_R,
	VTYPE_CI,
	VTYPE_CZ,
	VTYPE_CQ,
	VTYPE_CR,
	VTYPE_STR,
	VTYPE_O,
} vtype;

typedef struct object object;
struct object{
	uint64_t tid;
	avl_node *members;
	avl_node *interfaces;
	object *dict;
	object *list;
};

typedef struct value value;
struct value{
	ll_node *cleanup;
	vtype type;
	void *data;
};

#endif

