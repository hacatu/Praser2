#ifndef __UM_SCOPE_H__
#define __UM_SCOPE_H__

#include "avl.h"
#include "expression.h"

typedef struct oscope oscope;
struct oscope{
	size_t elems_len;
	expression *elems;
};

typedef struct cscope cscope;
struct cscope{
	size_t statements_len;
	expression *statements;
};

#endif

