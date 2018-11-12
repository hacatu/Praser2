#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(){
	ast *t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
	}
	position p;
	const char *err;
	init_position_from_str(&p, "\\x41");
	if((err = esc_seq_parser(t, &p))){
		log_err(err, p);
	}
	print_ast(t);
	clear_ast(t);
	init_position_from_str(&p, "\\X0041");
	if((err = esc_seq_parser(t, &p))){
		log_err(err, p);
	}
	print_ast(t);
	clear_ast(t);
	init_position_from_str(&p, "\\a");
	if((err = esc_seq_parser(t, &p)) || t->length != 1 || t->text[0] != '\a'){
		log_err(err, p);
	}
	clear_ast(t);
	init_position_from_str(&p, "\\b");
	if((err = esc_seq_parser(t, &p)) || t->length != 1 || t->text[0] != '\b'){
		log_err(err, p);
	}
	clear_ast(t);
	init_position_from_str(&p, "\\");
	if(!(err = esc_seq_parser(t, &p))){
		fprintf(stderr, "esc_seq_parser didn't fail on string \"\\\"\n");
	}
	printf("The next test should fail\n");
	log_err(err, p);
	clear_ast(t);
	if(!(err = always_fail_parser(t, &p))){
		fprintf(stderr, "always_fail_parser didn't fail\n");
	}
	printf("The next test should fail\n");
	log_err(err, p);
	clear_ast(t);
	init_position_from_str(&p, "");
	if(read_setrange('a', 'b', t, &p)){
		fprintf(stderr, "read_setrange didn't fail at end of string\n");
	}
	clear_ast(t);
	if(read_string("a", t, &p)){
		fprintf(stderr, "read_string didn't fail at end of string\n");
	}
	clear_ast(t);
	if(read_oneOf("a", t, &p)){
		fprintf(stderr, "read_oneOf didn't fail at end of string\n");
	}
	clear_ast(t);
	if(read_noneOf("a", t, &p)){
		fprintf(stderr, "read_noneOf didn't fail at end of string\n");
	}
	clear_ast(t);
	if(read_newline(&p)){
		fprintf(stderr, "read_newline didn't fail at end of string\n");
	}
	if(read_indent(&p)){
		fprintf(stderr, "read_indent didn't fail at end of string\n");
	}
	if(read_dedent(&p)){
		fprintf(stderr, "read_dedent didn't fail at end of string\n");
	}
	init_position_from_str(&p, "a");
	if(read_newline(&p)){
		fprintf(stderr, "read_newline didn't fail but there wasn't a new line\n");
	}
	if(read_indent(&p)){
		fprintf(stderr, "read_indent didn't fail but there wasn't an indent\n");
	}
	if(read_dedent(&p)){
		fprintf(stderr, "read_dedent didn't fail but there wasn't a dedent\n");
	}
	init_position_from_str(&p, "\x12\x14");
	if(!read_indent(&p)){
		fprintf(stderr, "read_indent failed when there was an indent\n");
	}
	if(!read_dedent(&p)){
		fprintf(stderr, "read_dedent failed when there was a dedent\n");
	}
	delete_ast(t);
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
	}
	append_ast(NULL, t);
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
	}
	merge_ast(NULL, t);
	print_ast(NULL);
	set_tag(NULL, "a");
}

