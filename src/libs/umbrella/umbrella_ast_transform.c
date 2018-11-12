#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"
#include "umbrella_interpreter.h"
#include "umbrella_ast_transform.h"

#ifndef CMPLX
#define CMPLX(x, y) ((complex double){x, y})
#endif

void transform_ast(block *out, ast *r){
	//start= whitespace? statements?
	if(!r->size){
		make_empty_block(out);
	}else{
		transform_statements(out, r->children[0]);
	}
}

void make_empty_block(block *out){
	*out = (block){};//TODO: is this right?
}

static size_t count_statements(ast *r){
	//statements= (label_tag? whitespace? expr post_comma* semicolon)* label_tag? expr post_comma*
	//post_comma= comma whitespace?
	size_t len = 0;
	for(size_t i = 0; i < r->size; ++i){
		if(!strcmp("expr", r->children[i]->name)){
			++len;
		}
	}
	return len;
}

void transform_statements(block *out, ast *r){
	//statements= (label_tag? whitespace? expr post_comma? semicolon)* label_tag? expr post_comma?
	//label_tag= whitespace? identifier whitespace? colon colon whitespace?
	//post_comma= comma whitespace?
	//size_t len;
	//size_t tag_len;
	//char *tag;
	//avl_node *labels;/*(char* -> expression*)*/
	//expression *statements;
	out->len = count_statements(r);
	out->tag_len = 0;
	out->tag = NULL;
	out->labels = NULL;
	out->statements = malloc(out->len*sizeof(expression));
	if(!out->statements){
		//TODO: handle memory error
	}
	for(size_t i = 0, j = 0; i < r->size; ++i){
		if(!strcmp("label_tag", r->children[i]->name)){
			avl_node_char__expression_ label = {
				strndup(r->children[i]->children[0]->text, r->children[i]->children[0]->length),
				out->statements + j
			};
			int status = avl_insert(&out->labels, &label, &avl_ft_char__expression_);
			if(status == 0){
				//TODO: handle memory error
			}else if(status == 2){
				//TODO: handle duplicate label
			}
		}else if(!strcmp("expr", r->children[i]->name)){
			int has_comma = i + 1 < r->size && !strcmp("post_comma", r->children[i + 1]->name);
			transform_expr(out->statements + j++, r->children[i++], has_comma, 0);
		}
	}
}

static operator compute_operator(ast *r){
	return r->length ? str_infix_to_op(r->text + r->size, r->length - r->size) : OP_TUPLE;
}

static void make_nested_singletons(expression *out, size_t n){
	if(!n){
		return;
	}
	expression *tail = malloc((n - 1)*sizeof(expression));
	for(size_t i = 1; i < n - 1; ++i){
		tail[i - 1] = (expression){
			.op= OP_TUPLE,
			.len=1,
			.type=ATOM_EXPR,
			.args[0]= tail + i
		};
	}
	tail[n - 1] = *out;
	*out = (expression){
		.op= OP_TUPLE,
		.len=1,
		.type=ATOM_EXPR,
		.args[0]=tail
	};
}

static void transform_expr_rec(expression*, size_t n, ast *[static n], size_t);

static void transform_expr_rec_compound(expression *out, size_t n, ast *head[static n], size_t prec){
	//TODO: we may eventually want to handle comparison operators differently, but for now they'll just get built up as right associative
}

static void transform_expr_rec_right(expression *out, size_t n, ast *head[static n], size_t prec){
	size_t a = 0;
	ast **base = head;
	expression *leaf = NULL, *stem = out;
	for(size_t i = 1; i < n; i += 2){
		operator op = compute_operator(base[i]);
		if(op_traits[op].precedence == prec - 1){
			leaf = malloc(1*sizeof(expression));
			*stem = (expression){
				.op=op,
				.len=2,
				.type=ATOM_EXPR,
				.args[0]=leaf,
				.args[1]= malloc(1*sizeof(expression))
			};
			stem = stem->args[1];
			head = base + a;
			transform_expr_rec(leaf, i - a, head, prec - 1);
			make_nested_singletons(leaf, base[i]->size + !!base[i]->length - 1);
			a = i + 1;
		}
	}
	head = base + a;
	transform_expr_rec(stem, n - a, head, prec - 1);
}

static void transform_expr_rec_left(expression *out, size_t n, ast *head[static n], size_t prec){
	size_t b = n;
	ast **base = head;
	expression *leaf = NULL, *stem = out;
	for(size_t i = n; i > 1 && (i -= 2);){
		operator op = compute_operator(base[i]);
		if(op_traits[op].precedence == prec - 1){
			leaf = malloc(1*sizeof(expression));
			*stem = (expression){
				.op=op,
				.len=2,
				.type=ATOM_EXPR,
				.args[1]=leaf,
				.args[0]= malloc(1*sizeof(expression))
			};
			stem = stem->args[0];
			head = base + i + 1;
			transform_expr_rec(leaf, b - i - 1, head, prec - 1);
			make_nested_singletons(leaf, base[i]->size + !!base[i]->length - 1);
			b = i;
		}
	}
	head = base;
	return transform_expr_rec(stem, b - 1, head, prec - 1);
}

static void transform_expr_rec(expression *out, size_t n, ast *head[static n], size_t prec){
	//expr= expr_prefix (whitespace? ocommas_op_infix whitespace? expr_prefix)*
	//ocommas_op_infix= commas_op_infix | op_infix
	//commas_op_infix< post_comma+ op_infix?
	//op_infix< "->"|"$="|"**="|"*="|"/="|"%="|"<<="|">>="|"+="|"-="|"&="|"|="|"^="|"~&="|"~|="|"~^="|"&&="|"||="|"^^="|"!&&="|"!||="|"!^^="|"&&"|"||"|"^^"|"!&&"|"!||"|"!^^"|"<<"|">>"|"<=>"|">="|"<="|"=="|"!="|"<-"|">"|"<"|"="|","|"&"|"|"|"^"|"~&"|"~|"|"~^"|"+"|"-"|"**"|"*"|"/"|"%"|"$"|":"
	//operator op;
	//size_t len;
	//atom_type type;
	//void *args[2];
	//this is pretty hard to do, so for now I'll make something not very efficient that works and I can make it better later if need be
	if(n == 1){
		transform_expr_prefix(out, head[0]);
		return;
	}
	//depending on the associativity of precedence - 1, we will have to scan left to right or right to left
	//scanning to find the end is unnecessary since now we have head to head + n as the elements to process
	//for the precedence level of the compound associativity operators, we will have to improvise
	//also note that the operators and their precedence levels will have to be
	//recomputed a lot since we aren't smashing the input in this version
	if(prec - 1 == COMPARISON_PRECEDENCE){
		//transform_expr_rec_compound(buf, n, head);
		transform_expr_rec_right(out, n, head, prec - 1);
	}else if(op_traits[compute_operator(head[1])].assoc & OP_ASSOC_LEFT){//the transform_expr_rec_left/right functions are named the opposite of OP_ASSOC_LEFT/RIGHT
		transform_expr_rec_right(out, n, head, prec - 1);
	}else{
		transform_expr_rec_left(out, n, head, prec - 1);
	}
}

void transform_expr(expression *out, ast *r, int has_comma, int in_operator){
	//expr= expr_prefix (whitespace? ocommas_op_infix whitespace? expr_prefix)*
	//ocommas_op_infix= commas_op_infix | op_infix
	//commas_op_infix< post_comma+ op_infix?
	//op_infix< "->"|"$="|"**="|"*="|"/="|"%="|"<<="|">>="|"+="|"-="|"&="|"|="|"^="|"~&="|"~|="|"~^="|"&&="|"||="|"^^="|"!&&="|"!||="|"!^^="|"&&"|"||"|"^^"|"!&&"|"!||"|"!^^"|"<<"|">>"|"<=>"|">="|"<="|"=="|"!="|"<-"|">"|"<"|"="|","|"&"|"|"|"^"|"~&"|"~|"|"~^"|"+"|"-"|"**"|"*"|"/"|"%"|"$"|":"
	ast **head = r->children;
	if(!in_operator && !has_comma){
		transform_expr_rec(out, r->size, head, MAX_PRECEDENCE);
	}else{
		//we want to build a degenerate right caterpillar binary tree with comma operators on all internal nodes and the results of transform_expr_rec at each leaf
		//if there are no commas we can just pass out directly to transform_expr_rec
		//otherwise, out should be the root of the tree and we should maintain leaf and stem nodes
		expression *leaf = NULL, *stem = out;
		size_t a = 0;
		for(size_t i = 1; i < r->size; i += 2){
			if(!r->children[i]->length){
				leaf = malloc(1*sizeof(expression));
				*stem = (expression){
					.op=OP_TUPLE,
					.len=2,
					.type=ATOM_EXPR,
					.args[0]=leaf,
					.args[1]= malloc(1*sizeof(expression))
				};
				stem = stem->args[1];
				//TODO: check for out of memory
				head = r->children + a;
				transform_expr_rec(leaf, i - a, head, MAX_PRECEDENCE);
				//TODO: have make_nested_singletons will copy the expression node if it actually has to wrap the argument in any tuples
				make_nested_singletons(leaf, r->children[i]->size + !!r->children[i]->length - 1);
				//TODO: add a transformation stage to coalesce tuples and associative operators
				a = i + 1;
			}
		}
		head = r->children + a;
		transform_expr_rec(stem, r->size - a, head, MAX_PRECEDENCE);
	}
	make_nested_singletons(out, !!has_comma);
}

void transform_expr_prefix(expression *out, ast *r){
	//expr_prefix= (whitespace? op_prefix)* whitespace? expr_postfix
	//op_prefix= "++"|"--"|"+"|"-"|"!"|"~"|"*"|"&"
	if(r->size == 1){
		transform_expr_postfix(out, r->children[0]);
		return;
	}
	expression *tail = malloc((r->size - 1)*sizeof(expression));//NOTE: we actually do some allocation aggregation here
	//TODO: check for out of memory (and have the transformation functions return error codes)
	*out = (expression){
		.op= str_prefix_to_op(r->children[0]->text),
		.len=1,
		.type=ATOM_EXPR,
		.args[0]=tail
	};
	for(size_t i = 1; i < r->size - 1; ++i){
		tail[i - 1] = (expression){
			.op= str_prefix_to_op(r->children[i]->text),
			.len=1,
			.type=ATOM_EXPR,
			.args[0]= tail + i
		};
	}
	transform_expr_postfix(tail + r->size - 1, r->children[r->size - 1]);
}

static void transform_expr_postfix2(expression *out, ast *r){
	if(out->op < OP_APP || OP_GET < out->op){
		return;
	}
	out->args[1] = (expression*)out->args[0] + 1;
	switch(out->op){
		case OP_APP:
		case OP_IDX: {
			block *args = malloc(1*sizeof(block));
			*(expression*)out->args[1] = (expression){
				.op=OP_ID,
				.len=1,
				.type=ATOM_BLOCK,
				.args[0]=args
			};
			transform_statements(args, r->children[0]);
			break;
		}
		case OP_NEWM:
			transform_atom(out, r->children[0]);
			break;
		case OP_GET:
			*(expression*)out->args[1] = (expression){
				.op=OP_ID,
				.len=1,
				.type=ATOM_IDENT,
				.args[0]=strndup(r->children[0]->text, r->children[0]->length)
			};
			break;
	}
}

static operator compute_operator_postfix(ast *r){
	if(!r->size){
		switch(r->text[0]){
			case '+': return OP_INCR;
			case '-': return OP_DECR;
			case '.': return OP_SPLAT;
		}
		return OP_MAYBE;
	}else if(!strcmp("bare_block", r->children[0]->name)){
		return OP_APP;
	}else if(!strcmp("bare_list", r->children[0]->name)){
		return OP_IDX;
	}else if(!strcmp("access", r->children[0]->name)){
		return OP_GET;
	}
	return OP_NEWM;
}

void transform_expr_postfix(expression *out, ast *r){
	//expr_postfix= expr0 (whitespace? post_comma* op_postfix)* whitespace?
	//op_postfix= "++"|"--"|".."|"?"|bare_block|bare_list|access|declaration
	//will also need special handling for the block/list/declaration forms
	if(r->size == 1){
		transform_expr0(out, r->children[0]);
		return;
	}
	size_t tail_len = r->size - 1;
	for(size_t i = 1; i < r->size; ++i){
		if(!r->children[i]->size){
			continue;
		}else if(!strcmp("bare_block", r->children[i]->children[0]->name) ||
		         !strcmp("bare_list", r->children[i]->children[0]->name) ||
		         !strcmp("access", r->children[i]->children[0]->name) ||
		         !strcmp("declaration", r->children[i]->children[0]->name)
		){
			++tail_len;
		}
	}
	expression *tail = malloc(tail_len*sizeof(expression));
	size_t j = 0;
	operator op = compute_operator_postfix(r->children[r->size - 1]);
	*out = (expression){
		.op=op,
		.len= (OP_APP <= op && op <= OP_GET) ? 2 : 1,
		.type=ATOM_EXPR,
		.args[0]=tail
	};
	transform_expr_postfix2(out, r->children[r->size - 1]);
	j += out->len;
	for(size_t i = r->size - 2; i; --i){
		op = compute_operator_postfix(r->children[i]);
		tail[j] = (expression){
			.op=op,
			.len= (OP_INCR <= op && op <= OP_GET) ? 2 : 1,
			.type=ATOM_EXPR
		};
		tail[j].args[0] = tail + j + 1;
		transform_expr_postfix2(tail + j, r->children[i]);
		j += tail[j].len;
	}
}

void transform_expr0(expression *out, ast *r){
	//expr0< declaration | atom
	//declaration= at atom
	if(!strcmp("atom", r->name)){
		transform_atom(out, r);
		return;
	}
	*out = (expression){
		.op=OP_NEWL,
		.len=1,
		.type=ATOM_EXPR,
		.args[0]= malloc(1*sizeof(expression))
	};
	transform_atom(out->args[0], r->children[0]);
}

void transform_atom(expression *out, ast *r){
	//atom= bare_block | literal | identifier
	//identifier= [a-zA-Z_] [a-zA-Z_0-9]*
	//TODO: using the precomputed expression arrays is hard so make the first version just call malloc a ton
	r = r->children[0];
	if(!strcmp("bare_block", r->name)){
		block *args = malloc(1*sizeof(block));
		*out = (expression){
			.op=OP_ID,
			.len=1,
			.type=ATOM_BLOCK,
			.args[0]=args
		};
		transform_statements(args, r->children[0]->children[0]);
	}else if(!strcmp("literal", r->name)){
		value *obj = malloc(1*sizeof(value));
		*out = (expression){
			.op=OP_ID,
			.len=1,
			.type=ATOM_VALUE,
			.args[0]=obj
		};
		transform_literal(obj, r);
	}else{
		*out = (expression){
			.op=OP_ID,
			.len=1,
			.type=ATOM_IDENT,
			.args[0]=strndup(r->children[0]->text, r->children[0]->length)
		};
	}
}

void transform_literal(value *out, ast *r){
	//VTYPE_VOID, VTYPE_I, VTYPE_Z, VTYPE_Q, VTYPE_R, VTYPE_CZ, VTYPE_CQ, VTYPE_CR, VTYPE_STR, VTYPE_OBJ, VTYPE_BLOCK,
	//literal= empty_tuple | list | dict | block | complex | real_numeric | string | char
	//empty_tuple= lparen whitespace? rparen
	//real_numeric< float | int
	r = r->children[0];
	if(!strcmp("list", r->name)){
		transform_compound_literal(out, r);
	}else if(!strcmp("dict", r->name)){
		transform_compound_literal(out, r);
	}else if(!strcmp("block", r->name)){
		transform_compound_literal(out, r);
	}else if(!strcmp("complex", r->name)){
		transform_complex_literal(out, r);
	}else if(!strcmp("float", r->name)){
		transform_float_literal(out, r);
	}else if(!strcmp("int", r->name)){
		transform_int_literal(out, r);
	}else if(!strcmp("string", r->name)){
		transform_string_literal(out, r);
	}else if(!strcmp("char", r->name)){
		transform_char_literal(out, r);
	}else if(!strcmp("empty_tuple", r->name)){
		make_empty_tuple(out);
	}else{
		//TODO: handle error
	}
}

void transform_compound_literal(value *out, ast *r){
	//block= label_tag? bare_block
	//bare_block= lparen whitespace? statements? rparen
	//list= label_tag? bare_list
	//bare_list= lbrace whitespace? statements? rbrace
	//dict= label_tag? lbracket whitespace? statements? whitespace? rbracket
	block *b = out->data = calloc(1, sizeof(block));
	out->cleanup = NULL;
	ast *label = r->size ? r->children[0] : NULL;
	if(label && strcmp("label_tag", label->name)){
		label = NULL;
	}
	if(!strcmp("block", r->name)){
		out->type = VTYPE_BLOCK;
		r = r->children[!!label];
		if(r->size){
			r = r->children[0];
		}else{
			r = NULL;
		}
	}else if(!strcmp("list", r->name)){
		out->type = VTYPE_LIST;
		r = r->children[!!label];
		if(r->size){
			r = r->children[0];
		}else{
			r = NULL;
		}
	}else{
		out->type = VTYPE_DICT;
		if(r->size > !!label){
			r = r->children[!!label];
		}else{
			r = NULL;
		}
	}
	if(r){
		transform_statements(b, r);
	}//otherwise the existing empty block should do fine
}

intptr_t transform_digit_groups_base(ast *r, size_t base){
	static const int char_digit[] = {
	    ['0']=0, ['1']=1, ['2']=2, ['3']=3, ['4']=4, ['5']=5, ['6']=6, ['7']=7, ['8']=8, ['9']=9,
	    ['A']=10, ['B']=11, ['C']=12, ['D']=13, ['E']=14, ['F']=15,
	    ['a']=10, ['b']=11, ['c']=12, ['d']=13, ['e']=14, ['f']=15};
	intptr_t ret = 0;
	for(size_t i = 0; i < r->size; ++i){
		ast *c = r->children[i];
		for(size_t j = 0; j < c->length; ++j){
			if(c->text[j] == '\''){
				continue;
			}
			ret = ret*base + char_digit[(unsigned char)c->text[j]];
		}
	}
	return ret;
}

void transform_int_literal(value *out, ast *r){
	//int= int_b | int_o | int_h | int_d
	//int_b= b_pre [01]+ (squote [01]+)*
	//int_o= o_pre [0-7]+ (squote [0-7]+)*
	//int_h= h_pre [0-9a-fA-F]+ (squote [0-9a-fA-F]+)*
	//int_d= [0-9]+ (squote [0-9]+)*
	out->type = VTYPE_Z;
	ast *f = r->children[0];
	if(!strcmp("int_b", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 2);
	}else if(!strcmp("int_o", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 8);
	}else if(!strcmp("int_h", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 16);
	}else if(!strcmp("int_d", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 10);
	}
}

void transform_float_literal(value *out, ast *r){
	//float= scientific | subnormal | normal
	//scientific< subnormal | normal | [0-9]+ [Ee] [+\-]? [0-9]+
	//subnormal< "." [0-9]+
	//normal< [0-9]+ "." [0-9]*
	out->type = VTYPE_R;
	char buf[r->length + 1];
	memcpy(buf, r->text, r->length);
	buf[r->length] = '\0';
	*(double*)&out->data = strtod(buf, NULL);
}

void transform_complex_literal(value *out, ast *r){
	//complex= (float whitespace? I) | (float whitespace? [+\-] float whitespace? I)
	out->type = VTYPE_CR;
	out->data = malloc(sizeof(double complex));
	value _val_r;
	double val_r, val_i;
	if(r->size == 1){//pure imaginary
		val_r = 0;
		if(!strcmp("float", r->children[0]->name)){//TODO: yo can we like use variables for the tags
			transform_float_literal(&_val_r, r->children[0]);
			val_i = *(double*)&_val_r.data;
		}else{
			transform_int_literal(&_val_r, r->children[0]);
			val_i = (double)(intptr_t)_val_r.data;
		}
		
	}else{//real and imaginary components
		if(!strcmp("float", r->children[0]->name)){
			transform_float_literal(&_val_r, r->children[0]);
			val_r = *(double*)&_val_r.data;
		}else{
			transform_int_literal(&_val_r, r->children[0]);
			val_r = (double)(intptr_t)_val_r.data;
		}
		if(!strcmp("float", r->children[1]->name)){
			transform_float_literal(&_val_r, r->children[1]);
			val_i = *(double*)&_val_r.data;
		}else{
			transform_int_literal(&_val_r, r->children[1]);
			val_i = (double)(intptr_t)_val_r.data;
		}
		if(r->text[0] == '-'){
			val_i = -val_i;
		}
	}
	*(double complex*)out->data = CMPLX(val_r, val_i);
}

void transform_string_literal(value *out, ast *r){
	//string= dquote schar* dquote
	//schar< [^\\"\n] | esc_seq
	out->type = VTYPE_STR;
	out->data = malloc(sizeof(vstr) + r->length);
	vstr *str = out->data;
	str->len = r->length;
	memcpy(str->buf, r->text, r->length);
}

void transform_char_literal(value *out, ast *r){
	//char= squote schar squote
	out->type = VTYPE_CH;
	out->data = (void*)(intptr_t)r->text[0];
}

void make_empty_tuple(value *out){
	out->type = VTYPE_OBJ;
	out->data = calloc(1, sizeof(object));
	((object*)out->data)->tid = 0;//TODO: actually we need to initialize this and give it the tid of a tuple
}

