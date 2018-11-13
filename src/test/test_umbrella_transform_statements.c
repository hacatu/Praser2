#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"
#include "umbrella_interpreter.h"
#include "umbrella_ast_transform.h"
#include "betest.h"

/* Untested umbrella ast transformers:
 * transform_ast
 * make_empty_block
 * transform_statements with labels
 * make_nested_singletons with nonzero nesting
 * transform_expr_rec with comparison operators
 * transform_expr with in_operator || has_comma
 * transform_expr_postfix2 with OP_GET (_._)
 * compute_operator_postfix with access (_._)
 * transform_atom with bare_block or identifier
 */

const char *(*expr_postfix_parser)(ast*, position*);
const char *(*expr_prefix_parser)(ast*, position*);
const char *(*expr_parser)(ast*, position*);

int main(){
	void *parser_so_handle = dlopen("lib/libumbrella_parser.so", RTLD_LAZY);
	if(!parser_so_handle){
		fprintf(stderr, "dlopen failed for library \"%s\": %s\n", "lib/libumbrella_parser.so", dlerror());
		return 1;
	}
	*(void**)&expr_postfix_parser = dlsym_or_exit(parser_so_handle, "expr_postfix_parser");
	*(void**)&expr_prefix_parser = dlsym_or_exit(parser_so_handle, "expr_prefix_parser");
	*(void**)&expr_parser = dlsym_or_exit(parser_so_handle, "expr_parser");
	const char *err = NULL;
	position p;
	expression _res = {};
	ast *t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		return 1;
	}
	const char *expr_postfix_test_strings[] = {"1", "1?", "1++", "@1", "@1++", "1()", "1[1]", "1@1", "1--", "1??", "\"\"..", "\"\".1"};
	for(size_t i = 0; i < sizeof(expr_postfix_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, expr_postfix_test_strings[i]);
		if((err = expr_postfix_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_expr_postfix(&_res, t);
			printf("Result: <expression>\n");
		}
		clear_ast(t);
	}
	const char *expr_prefix_test_strings[] = {"1", "++1", "**1"};
	for(size_t i = 0; i < sizeof(expr_prefix_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, expr_prefix_test_strings[i]);
		if((err = expr_prefix_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_expr_prefix(&_res, t);
			printf("Result: <expression>\n");
		}
		clear_ast(t);
	}
	const char *lassoc_expr_test_strings[] = {"1", "1=1", "1=1 = 1"};
	for(size_t i = 0; i < sizeof(lassoc_expr_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, lassoc_expr_test_strings[i]);
		if((err = expr_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_expr(&_res, t, 0, 0);
			printf("Result: <expression>\n");
		}
		clear_ast(t);
	}
	const char *cassoc_expr_test_strings[] = {"1 <=1", "1>1>1"};
	for(size_t i = 0; i < sizeof(cassoc_expr_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, cassoc_expr_test_strings[i]);
		if((err = expr_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_expr(&_res, t, 0, 0);
			printf("Result: <expression>\n");
		}
		clear_ast(t);
	}
	dlclose(parser_so_handle);
	delete_ast(t);
}

