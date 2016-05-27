/*
 * ast_callback_compile.c
 * Run ast_compiler on an ast and a file specified by argv[2] to parser_runner.main, then print the result.
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast_interpreter.h"
#include "ast_compiler.h"

int ast_callback(ast *r, int argc, char **argv){
	if(argc < 1){
		fprintf(stderr, "Please specify the output.\n");
		return 1;
	}
	size_t num_states;
	const state *fsa = ast_to_fsa(r, &num_states, 1);
	if(!fsa){
		fprintf(stderr, "ast_to_fsa failed.\n");
		return 1;
	}
	FILE *f = fopen(argv[0], "w");
	write_all(f, fsa, num_states);
	fclose(f);
	delete_nonroot_fsa((state*)fsa, num_states);//discard const qualifier
	return 0;
}

