#ifndef __LL_H__
#define __LL_H__

#include <stddef.h>

typedef struct ll_node ll_node;
struct ll_node{
	ll_node *next;
	char data[];
};

typedef struct{//function table to hold function pointers and related data
	size_t size;
	void *(*alloc)(void*);
	void (*free)(void*, void*);
	void *alloc_data;
} ll_ft;

ll_node *ll_new(void *data, ll_node *next, ll_ft *ft);
int ll_push(ll_node **h, void *data, avl_ft *ft);
int cl_pushl(ll_node **t, void *data, avl_ft *ft);
int cl_pushr(ll_node **t, void *data, avl_ft *ft);
int ll_pop(ll_node **h, avl_ft *ft);
int cl_popl(ll_node **t, avl_ft *ft);
int cl_popr(ll_node **t, avl_ft *ft);
void ll_delete(ll_node *h, avl_ft *ft);
void cl_delete(ll_node *h, avl_ft *ft);

#endif

