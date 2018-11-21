/*
 * ast_callback_compile.c
 * Run ast_compiler on an ast and a file specified by argv[2] to parser_runner.main, then print the result.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast_interpreter.h"
#include "ast_compiler.h"

int ast_callback(ast *r, int argc, char **argv){
	if(argc < 2){
		fprintf(stderr, "Please specify the backend and output.\n");
		return 1;
	}
	size_t buf_len = strlen(argv[0]) + strlen("lib/backend_fmts/lib_backend_fmts.so");
	char buf[buf_len + 1];
	memset(buf, 0, (buf_len + 1)*sizeof(char));
	sprintf(buf, "lib/backend_fmts/lib%s_backend_fmts.so", argv[0]);
	void *handle = read_fmts(buf);
	if(!handle){
		fprintf(stderr, "Could not open backend so.\n");
		return 1;
	}
	size_t num_states = 0;
	const state *fsa = ast_to_fsa(r, &num_states, 1);
	if(!fsa){
		fprintf(stderr, "ast_to_fsa failed.\n");
		return 1;
	}
	FILE *f = fopen(argv[1], "w");
	write_all(f, fsa, num_states);
	fclose(f);
	release_fmts(handle);
	delete_nonroot_fsa((state*)fsa, num_states);//discard const qualifier
	return 0;
}

