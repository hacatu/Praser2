#ifndef __AST_COMPILER_H__
#define __AST_COMPILER_H__

#include <stdio.h>
#include "parser.h"
#include "ast_interpreter.h"

void *read_fmts(const char *filename);
void release_fmts(void *handle);

void write_all(FILE *f, const state *fsm, size_t num_states);

#endif

