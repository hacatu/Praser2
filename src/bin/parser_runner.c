/*
 * parser_runner.c
 * Default glue code to run a parser (specified by linking to an object file with a start_parser function)
 * and an ast callback (specified by linking to an object file with an ast_callback function).
 * This is basically for rapid prototyping and internal testing since it's limited to that functionality.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "parser.h"

const char *(*start_parser)(ast*, position*);//Entry point for parser.  Load from shared library at runtime

int (*ast_callback)(ast*, int argc, char **argv);//Entry point for parser ast callback.

int main(int argc, char **argv){
	if(argc < 4){
		fprintf(stderr, "Please specify the parser, callback, and file to parse.\n");
		return 1;
	}
	void *parser_so_handle = NULL, *cb_so_handle = NULL;
	{
		size_t buf_len = strlen(argv[1]) + strlen("lib/parsers/lib_parser.so"), cb_so_name_len = strlen(argv[2]) + strlen("lib/ast_callbacks/libast_callback_.so");
		if(cb_so_name_len > buf_len){
			buf_len = cb_so_name_len;
		}
		char buf[buf_len + 1];
		sprintf(buf, "lib/parsers/lib%s_parser.so", argv[1]);
		parser_so_handle = dlopen(buf, RTLD_LAZY);
		if(!parser_so_handle){
			fprintf(stderr, "dlopen failed for library \"%s\": %s\n", buf, dlerror());
			return 1;
		}
		*(void**)&start_parser = dlsym(parser_so_handle, "start_parser");
		if(!*(void**)&start_parser){
			fprintf(stderr, "parser .so did not contain \"start_parser\"\n");
			dlclose(parser_so_handle);
			return 1;
		}
		sprintf(buf, "lib/ast_callbacks/libast_callback_%s.so", argv[2]);
		cb_so_handle = dlopen(buf, RTLD_LAZY);
		if(!cb_so_handle){
			fprintf(stderr, "dlopen failed for library \"%s\": %s\n", buf, dlerror());
			dlclose(parser_so_handle);
			return 1;
		}
		*(void**)&ast_callback = dlsym(cb_so_handle, "ast_callback");
		if(!*(void**)&start_parser){
			fprintf(stderr, "ast callback .so did not contain \"ast_callback\"\n");
			dlclose(parser_so_handle);
			dlclose(cb_so_handle);
			return 1;
		}
	}
	ast *t;
	position p;
	const char *err;
	if((err = mmap_open(argv[3], &p))){
		fprintf(stderr, "mmap_open failed on file \"%s\": %s\n", argv[3], err);
		dlclose(parser_so_handle);
		dlclose(cb_so_handle);
		return 1;
	}
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		mmap_close(&p);
		dlclose(parser_so_handle);
		dlclose(cb_so_handle);
		return 1;
	}
	int status = 1;
	if((err = start_parser(t, &p))){
		log_err(err, p);
		mmap_close(&p);
	}else{
		mmap_close(&p);
		status = ast_callback(t, argc - 4, argv + 4);
	}
	delete_ast(t);
	dlclose(parser_so_handle);
	dlclose(cb_so_handle);
	return status;
}

