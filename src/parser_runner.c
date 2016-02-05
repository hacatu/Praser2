/*
 * parser_runner.c
 * Default glue code to run a parser (specified by linking to an object file with a start_parser function)
 * and an ast callback (specified by linking to an object file with an ast_callback function).
 * This is basically for rapid prototyping and internal testing since it's limited to that functionality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"

const char *start_parser(ast*, position*);//Entry point for parser.  Link parser object file with this object file.

int ast_callback(ast*, int argc, char **argv);//Entry point for parser ast callback.

int main(int argc, char **argv){
	if(argc < 2){
		fprintf(stderr, "Please specify the file to parse.\n");
		return 1;
	}
	ast *t;
	position p;
	const char *err;
	if((err = mmap_open(argv[1], &p))){
		fprintf(stderr, "mmap_open failed on file \"%s\": %s\n", argv[1], err);
		return 1;
	}
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		mmap_close(&p);
		return 1;
	}
	if((err = start_parser(t, &p))){
		log_err(err, p);
		mmap_close(&p);
	}else{
		mmap_close(&p);
		ast_callback(t, argc - 2, argv + 2);
	}
	delete_ast(t);
}

