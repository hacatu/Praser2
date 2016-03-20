#ifndef __AVL_CHECK_H__
#define __AVL_CHECK_H__

inline static int avl_check_links(avl_node *n){
	if(!n)return 1;
	if(n->left){
		if(n->left->parent != n)return 0;
		if(!avl_check_links(n->left))return 0;
	}
	if(n->right){
		if(n->right->parent != n)return 0;
		if(!avl_check_links(n->right))return 0;
	}
	return 1;
}

inline static int avl_check_balance(avl_node *n){
	if(!n)return 0;
	int l, r;
	if((l = avl_check_balance(n->left)) == -1)return -1;
	if((r = avl_check_balance(n->right)) == -1)return -1;
	if(r - l == n->balance)return 1 + (l > r ? l : r);
	return -1;
}

#endif

