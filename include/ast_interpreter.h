#ifndef __AST_INTERPRETER_H__
#define __AST_INTERPRETER_H__

#include <stdarg.h>
#include "parser.h"

typedef void (*ast_fn)(ast*, void*);
typedef struct state state;
typedef const char *(*state_parse_fn)(const state*, ast*, position*);
typedef void (*state_gen_fn)(const state*, position*);

typedef struct{
	const char *name;
	state_parse_fn parse;
	state_gen_fn gen;
} special_state;

struct state{
	const ast *rule;
	state_parse_fn parse;
	state_gen_fn gen;
};

void forall_ast_nodes_postorder(ast_fn f, ast *t, void *data);

void forall_ast_nodes_preorder(ast_fn f, ast *t, void *data);

const state *ast_to_fsa(ast *r, size_t *num_states);

const char *state_parse(const state *fsa, ast*, position*);

void delete_nonroot_fsa(state *fsa, size_t num_states);

#define register_special_states(s...) _register_special_states(s, (special_state){0})
void _register_special_states(special_state s, ...);

#endif

