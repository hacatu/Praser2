#ifndef __LANGUAGE_GENERATOR_H__
#define __LANGUAGE_GENERATOR_H__

#include "parser.h"
#include "ast_interpreter.h"

typedef enum{
	ATOM_STRING=0,
	ATOM_CHARSET=1,
	ATOM_SPECIAL=2,
	ATOM_PARENS=3,
	ATOM_RULE=4,
	ATOM_TYPES_LEN=5
} atom_type;

typedef enum{
	ATOM_X_ONCE=0,
	ATOM_X_OPTIONAL=1,
	ATOM_X_MULTIPLE=2,
	ATOM_X_REPEATED=3,
	ATOM_QUANTIFIERS_LEN=4
} atom_quantifier;

extern int lgen_atom_weight[ATOM_TYPES_LEN][ATOM_QUANTIFIERS_LEN];

extern int (*lgen_repetition_rand)(void);

void fsa_invsets(state *fsa, size_t num_states);

void state_gen(const state *fsa, FILE *out);

#endif

