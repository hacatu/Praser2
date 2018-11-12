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

//literal= empty_tuple | list | dict | block | complex | real_numeric | string | char

//block= label_tag? bare_block
//bare_block= lparen whitespace? statements? rparen
//list= label_tag? bare_list
//bare_list= lbrace whitespace? statements? rbrace
//dict= label_tag? lbracket whitespace? statements whitespace? rbracket

const char *(*empty_tuple_parser)(ast*, position*);
const char *(*list_parser)(ast*, position*);
const char *(*dict_parser)(ast*, position*);
const char *(*block_parser)(ast*, position*);

const char *(*literal_parser)(ast*, position*);

int main(){
	void *parser_so_handle = dlopen("lib/libumbrella_parser.so", RTLD_LAZY);
	if(!parser_so_handle){
		fprintf(stderr, "dlopen failed for library \"%s\": %s\n", "lib/libumbrella_parser.so", dlerror());
		return 1;
	}
	*(void**)&empty_tuple_parser = dlsym_or_exit(parser_so_handle, "empty_tuple_parser");
	*(void**)&list_parser = dlsym_or_exit(parser_so_handle, "list_parser");
	*(void**)&dict_parser = dlsym_or_exit(parser_so_handle, "dict_parser");
	*(void**)&block_parser = dlsym_or_exit(parser_so_handle, "block_parser");
	*(void**)&literal_parser = dlsym_or_exit(parser_so_handle, "literal_parser");
	const char *err = NULL;
	position p;
	value _res = {};
	ast *t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		return 1;
	}
	const char *empty_tuple_test_strings[] = {"()", "( )"};
	for(size_t i = 0; i < sizeof(empty_tuple_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, empty_tuple_test_strings[i]);
		if((err = empty_tuple_parser(t, &p))){
			log_err(err, p);
		}else{
			make_empty_tuple(&_res);
			printf("Result: type=%i, data=()\n", (int)_res.type);
		}
		clear_ast(t);
		init_position_from_str(&p, empty_tuple_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=()\n", (int)_res.type);
		}
		clear_ast(t);
	}
	const char *list_test_strings[] = {"[]", "[ ]", "[1]", "[1, 2]"};
	for(size_t i = 0; i < sizeof(list_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, list_test_strings[i]);
		if((err = list_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_compound_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
		init_position_from_str(&p, list_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
	}
	const char *dict_test_strings[] = {"{}", "{ }", "{1=1}", "{1=1; 2=2}"};
	for(size_t i = 0; i < sizeof(dict_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, dict_test_strings[i]);
		if((err = dict_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_compound_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
		init_position_from_str(&p, dict_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
	}
	const char *block_test_strings[] = {"()", "( )", "(1)", "(1; 2)"};
	for(size_t i = 0; i < sizeof(dict_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, block_test_strings[i]);
		if((err = block_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_compound_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
		init_position_from_str(&p, block_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=NYI\n", (int)_res.type);
		}
		clear_ast(t);
	}
	dlclose(parser_so_handle);
	delete_ast(t);
}

