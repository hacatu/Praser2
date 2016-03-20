#ifndef __AVL_H__
#define __AVL_H__

typedef int (*avl_cmp_fn)(const void*, const void*);
typedef void (*avl_del_fn)(void*);
typedef void *(*avl_alloc_fn)(void*);//Types for allocator methods
typedef void (*avl_free_fn)(void*, void*);//This typedef is named for what it should do; free does not match this signature.

typedef struct avl_node avl_node;
struct avl_node{
	void *data;
	avl_node *left, *right, *parent;
	signed char balance;
};

typedef struct{//function table to hold function pointers and related data
	avl_cmp_fn cmp;
	avl_del_fn del;
	avl_alloc_fn alloc;
	avl_free_fn free;
	avl_del_fn alloc_free;
	void *alloc_data;
} avl_ft;

avl_node *avl_new(void *key, avl_node *left, avl_node *right, avl_node *parent, char balance, avl_ft *ft);
int avl_insert(avl_node **r, void *key, avl_ft *ft);
int avl_remove(avl_node **r, void *key, avl_ft *ft);
avl_node *avl_remove_node(avl_node *n, avl_ft *ft);
avl_node *avl_get(avl_node *r, void *key, avl_ft *ft);
avl_node *avl_root(avl_node *n);
avl_node *avl_first(avl_node *r);
avl_node *avl_next(avl_node *n);
avl_node *avl_last(avl_node *n);
avl_node *avl_prev(avl_node *n);
avl_node *avl_lower_bound(avl_node *r, void *key, avl_ft *ft);
avl_node *avl_upper_bound(avl_node *r, void *key, avl_ft *ft);
void avl_delete(avl_node *r, avl_ft *ft);

#endif

