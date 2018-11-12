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
#include "betest.h"

const char *(*start_parser)(ast*, position*);

int main(){
	void *parser_so_handle = dlopen("lib/libparser_parser.so", RTLD_LAZY);
	if(!parser_so_handle){
		fprintf(stderr, "dlopen failed for library \"%s\": %s\n", "lib/libparser_parser.so", dlerror());
		return 1;
	}
	*(void**)&start_parser = dlsym_or_exit(parser_so_handle, "start_parser");
	ast *t;
	position p;
	const char *err;
	if((err = mmap_open("src/parsers/parser.pra", &p))){
		fprintf(stderr, "mmap_open failed on file \"%s\": %s\n", "src/parsers/parser.pra", err);
		dlclose(parser_so_handle);
		return 1;
	}
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		mmap_close(&p);
		dlclose(parser_so_handle);
		return 1;
	}
	if((err = start_parser(t, &p))){
		log_err(err, p);
		mmap_close(&p);
	}else{
		mmap_close(&p);
		t = flatten_ast(t);
		print_ast(t);
	}
	dlclose(parser_so_handle);
	delete_ast(t);
	if((err = mmap_open("src/test/test_builtin_transformers.c", &p))){
		fprintf(stderr, "mmap_open failed on file \"%s\": %s\n", "src/test/test_builtin_transformers.c", err);
		return 1;
	}
	position pt = canonicalize_indents(&p, 4);
	mmap_close(&p);
	free((char*)pt.start);//discard const
}

