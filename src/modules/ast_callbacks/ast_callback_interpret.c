/*
 * ast_callback_interpret.c
 * Run ast_interpreter on an ast and a file specified by argv[2] to parser_runner.main, then print the result.
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast_interpreter.h"

static const char *state_parse_esc_seq(const state *self, ast *t, position *p){
	return esc_seq_parser(t, p);
}

int ast_callback(ast *r, int argc, char **argv){
	if(argc < 1){
		fprintf(stderr, "Please specify the second file to parse.\n");
		return 1;
	}
	size_t num_states;
	register_special_states((special_state){"esc_seq", state_parse_esc_seq, NULL});
	const state *fsa = ast_to_fsa(r, &num_states, 0);
	if(!fsa){
		fprintf(stderr, "ast_to_fsa failed.\n");
		return 1;
	}
	ast *t;
	position p;
	const char *err;
	if((err = mmap_open(argv[0], &p))){
		fprintf(stderr, "mmap_open failed on file \"%s\": %s\n", argv[0], err);
		delete_nonroot_fsa((state*)fsa, num_states);//discard const qualifier
		return 1;
	}
	t = alloc_ast();
	if(!t){
		fprintf(stderr, "alloc_ast could not allocate memory.\n");
		mmap_close(&p);
		delete_nonroot_fsa((state*)fsa, num_states);//discard const qualifier
		return 1;
	}
	if((err = state_parse(fsa, t, &p))){
		log_err(err, p);
		mmap_close(&p);
	}else{
		mmap_close(&p);
		print_ast(t);
	}
	delete_ast(t);
	delete_nonroot_fsa((state*)fsa, num_states);//discard const qualifier
	return 0;
}

