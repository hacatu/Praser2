#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"
#include "umbrella_interpreter.h"
#include "src/umbrella_ast_transform.h"

const char *int_parser(ast*, position*);

int main(){
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
	}
	const char *complex_test_strings[] = {"4 i", "1i", "3+4i"};
	for(size_t i = 0; i < sizeof(complex_test_strings)/sizeof(const char*); ++i){
		init_position_from_str(&p, complex_test_strings[i]);
		if((err = complex_parser(t, &p))){
			log_err(err, p);
		}else{
			transform_complex_literal(&_res, t);
			printf("Result: type=%i, data=%f%+fi\n", (int)_res.type, creal(*(double complex*)&_res.data), cimag(*(double complex*)&_res.data));
			free(_res.data);
		}
		clear_ast(t);
	}
	delete_ast(t);
}

