/*
 * language_generator.c
 * Uses an fsa as from ast_interpreter.ast_to_fsa to generate text matching a language description for testing.
 * Note that this will require special functions to provide generators, which is nyi.  But then again neither are any of these functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast_interpreter.h"
#include "language_generator.h"

static void state_gen_rule(const state *self, position *out);
static void state_gen_special(const state *self, position *out);

static void gen_atom(const state *self, position *out){
	
}

static void gen_option(const state *self, position *out){
	
}

static void gen_group(const state *self, position *out){
	
}

void state_gen_rule(const state *self, position *out){
	const ast *pattern;
	
}

void state_gen_special(const state *self, position *out){
	
}

