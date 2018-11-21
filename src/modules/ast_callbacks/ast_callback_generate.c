/*
 * ast_callback_generate.c
 * Run language_generator on an ast from a file with a given random seed and output to a file.
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast_interpreter.h"
#include "language_generator.h"

void state_gen_esc_seq(const state *self, FILE *out){
	fprintf(out, "\\n");//TODO: generate more than just one escape sequence
}

int ast_callback(ast *r, int argc, char **argv){
	if(argc < 1){
		fprintf(stderr, "Please use the language generator with a language description file, output file, and optionally random seed.\n");
		return 1;
	}
	if(argc > 1){
		srand(atoi(argv[1]));
	}
	FILE *out = fopen(argv[0], "w");
	if(!out){
		fprintf(stderr, "Could not open file \"%s\".\n", argv[0]);
		return 1;
	}
	size_t num_states;
	register_special_states((special_state){"esc_seq", NULL, state_gen_esc_seq});
	state *fsa = (state*)ast_to_fsa(r, &num_states, 0);
	if(!fsa){
		fprintf(stderr, "ast_to_fsa failed.\n");
		return 1;
	}
	fsa_invsets(fsa, num_states);
	state_gen(fsa, out);
	delete_nonroot_fsa(fsa, num_states);
	fclose(out);
	return 0;
}

