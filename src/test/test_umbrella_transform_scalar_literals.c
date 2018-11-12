#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <complex.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"
#include "umbrella_interpreter.h"
#include "umbrella_ast_transform.h"
#include "betest.h"

const char *(*int_parser)(ast*, position*);
const char *(*float_parser)(ast*, position*);
const char *(*complex_parser)(ast*, position*);
const char *(*string_parser)(ast*, position*);
const char *(*char_parser)(ast*, position*);

const char *(*literal_parser)(ast*, position*);

int main(){
	void *parser_so_handle = dlopen("lib/libumbrella_parser.so", RTLD_LAZY);
	if(!parser_so_handle){
		fprintf(stderr, "dlopen failed for library \"%s\": %s\n", "lib/libumbrella_parser.so", dlerror());
		return 1;
	}
	*(void**)&int_parser = dlsym_or_exit(parser_so_handle, "int_parser");
	*(void**)&float_parser = dlsym_or_exit(parser_so_handle, "float_parser");
	*(void**)&complex_parser = dlsym_or_exit(parser_so_handle, "complex_parser");
	*(void**)&string_parser = dlsym_or_exit(parser_so_handle, "string_parser");
	*(void**)&char_parser = dlsym_or_exit(parser_so_handle, "char_parser");
	*(void**)&literal_parser = dlsym_or_exit(parser_so_handle, "literal_parser");
	const char *err = NULL;
	position p;
	value _res = {};
	ast *t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		return 1;
	}
	const char *int_test_strings[] = {"123'456'789", "0xDEAD", "0b111", "0o777"};
	for(size_t i = 0; i < sizeof(int_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, int_test_strings[i]);
		if((err = int_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_int_literal(&_res, t);
			printf("Result: type=%i, data=%i\n", (int)_res.type, (int)(intptr_t)_res.data);
		}
		clear_ast(t);
		init_position_from_str(&p, int_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=%i\n", (int)_res.type, (int)(intptr_t)_res.data);
		}
		clear_ast(t);
	}
	const char *float_test_strings[] = {"3.14", ".1", "2.", "3e3"};
	for(size_t i = 0; i < sizeof(float_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, float_test_strings[i]);
		if((err = float_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_float_literal(&_res, t);
			printf("Result: type=%i, data=%f\n", (int)_res.type, *(double*)&_res.data);
		}
		clear_ast(t);
		init_position_from_str(&p, float_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=%f\n", (int)_res.type, *(double*)&_res.data);
		}
		clear_ast(t);
	}
	const char *complex_test_strings[] = {"4 i", "1.i", "3.+4i", "3-4.i"};
	for(size_t i = 0; i < sizeof(complex_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, complex_test_strings[i]);
		if((err = complex_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_complex_literal(&_res, t);
			printf("Result: type=%i, data=%f%+fi\n", (int)_res.type, creal(*(double complex*)_res.data), cimag(*(double complex*)_res.data));
			free(_res.data);
		}
		clear_ast(t);
		init_position_from_str(&p, complex_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=%f%+fi\n", (int)_res.type, creal(*(double complex*)_res.data), cimag(*(double complex*)_res.data));
			free(_res.data);
		}
		clear_ast(t);
	}
	const char *string_test_strings[] = {"\"\"", "\"big spatula\"", "\"\\\"\\\\%\""};
	for(size_t i = 0; i < sizeof(string_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, string_test_strings[i]);
		if((err = string_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_string_literal(&_res, t);
			printf("Result: type=%i, data=\"%.*s\"\n", (int)_res.type, (int)((vstr*)_res.data)->len, ((vstr*)_res.data)->buf);
			free(_res.data);
		}
		clear_ast(t);
		init_position_from_str(&p, string_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data=\"%.*s\"\n", (int)_res.type, (int)((vstr*)_res.data)->len, ((vstr*)_res.data)->buf);
			free(_res.data);
		}
		clear_ast(t);
	}
	const char *char_test_strings[] = {"'\\x00'", "'\\a'", "'\\\"'"};
	for(size_t i = 0; i < sizeof(char_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, char_test_strings[i]);
		if((err = char_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_char_literal(&_res, t);
			printf("Result: type=%i, data='%c'\n", (int)_res.type, (char)(intptr_t)_res.data);
		}
		clear_ast(t);
		init_position_from_str(&p, char_test_strings[i]);
		if((err = literal_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_literal(&_res, t);
			printf("Result: type=%i, data='%c'\n", (int)_res.type, (char)(intptr_t)_res.data);
		}
		clear_ast(t);
	}
	dlclose(parser_so_handle);
	delete_ast(t);
}

