/*
 * language_generator.c
 * Uses an fsa as from ast_interpreter.ast_to_fsa to generate text matching a language description for testing.
 * Note that this will require special functions to provide generators, which is nyi.  But then again neither are any of these functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast_interpreter.h"
#include "language_generator.h"

int lgen_atom_weight[ATOM_TYPES_LEN][ATOM_QUANTIFIERS_LEN] = {
//         ?    *    +
	{180, 270,  90,  60},//ATOM_STRING
	{150, 225,  75,  50},//ATOM_CHARSET
	{120, 180,  60,  40},//ATOM_SPECIAL
	{ 90, 135,  45,  30},//ATOM_PARENS
	{ 60,  90,  30,  20},//ATOM_RULE
};

static int lgen_repetition_few(void){
	return rand()%2;
}

int (*lgen_repetition_rand)(void) = lgen_repetition_few;

static atom_type get_atom_type(const ast *atom){
	atom = atom->children[0];
	if(!strcmp("string", atom->name)){
		return ATOM_STRING;
	}else if((!strcmp("charset", atom->name)) || (!strcmp("invset", atom->name))){
		return ATOM_CHARSET;
	}else if(((const state*)atom->text)->parse != state_parse_rule){
		return ATOM_SPECIAL;
	}else if(strcmp("rule", ((const state*)atom->text)->rule->name)){
		return ATOM_PARENS;
	}else{
		return ATOM_RULE;
	}
}

static atom_quantifier get_option_quantifier(const ast *option){
	if(option->size < 2){
		return ATOM_X_ONCE;
	}else switch(*option->children[1]->text){
	case '?':
		return ATOM_X_OPTIONAL;
	case '*':
		return ATOM_X_MULTIPLE;
	default:
		return ATOM_X_REPEATED;
	}
}

static void gen_charset(const ast *charset, FILE *out){//TODO: handle invsets properly
	int num_chars = 0;
	for(size_t i = 0; i < charset->size; ++i){
		const ast *elem = charset->children[i];
		if(!strcmp("setchar", elem->name)){
			++num_chars;
		}else{//elem->name == "setrange"
			num_chars += *elem->children[1]->text - *elem->children[0]->text + 1;
		}
	}
	int x = rand()%num_chars;
	for(size_t i = 0; i < charset->size; ++i){
		const ast *elem = charset->children[i];
		if(!strcmp("setchar", elem->name)){
			if(!x--){
				fputc(*elem->text, out);
				break;
			}
		}else{//elem->name == "setrange"
			int range_chars = *elem->children[1]->text - *elem->children[0]->text + 1;
			if(x < range_chars){
				fputc(*elem->children[0]->text + x, out);
				break;
			}
			x -= range_chars;
		}
	}
}

static void gen_atom(const ast *atom, FILE *out){
	const state *s;
	switch(get_atom_type(atom)){
	case ATOM_STRING:
		fprintf(out, "%s", atom->children[0]->text);
		break;
	case ATOM_CHARSET:
		gen_charset(atom->children[0], out);
		break;
	case ATOM_SPECIAL:
	case ATOM_PARENS:
	case ATOM_RULE:
		s = (const state*)atom->children[0]->text;
		s->gen(s, out);
		break;
	}
}

static void gen_option(const ast *option, FILE *out){
	int repetitions = 1;
	switch(get_option_quantifier(option)){
	case ATOM_X_ONCE:
		repetitions = 1;
		break;
	case ATOM_X_OPTIONAL:
		repetitions = rand()%2;//I've heard rand() has terrible low bits, and that it is terrible in general
		break;
	case ATOM_X_MULTIPLE:
		repetitions = lgen_repetition_rand();
		break;
	case ATOM_X_REPEATED:
		repetitions = lgen_repetition_rand() + 1;
		break;
	}
	while(repetitions-- > 0){
		gen_atom(option->children[0], out);
	}
}

static void gen_group(const ast *group, FILE *out){
	int total_weight = 0;
	for(size_t i = 0; i < group->size; ++i){
		const ast *option = group->children[i];
		atom_type type = get_atom_type(option->children[0]);
		atom_quantifier quantifier = get_option_quantifier(option);
		total_weight += lgen_atom_weight[type][quantifier];
	}
	int x = rand()%total_weight;
	for(size_t i = 0; i < group->size; ++i){
		const ast *option = group->children[i];
		atom_type type = get_atom_type(option->children[0]);
		atom_quantifier quantifier = get_option_quantifier(option);
		int weight = lgen_atom_weight[type][quantifier];
		if(x < weight){
			gen_option(option, out);
			break;
		}
		x -= weight;
	}
}

void state_gen_rule(const state *self, FILE *out){
	const ast *pattern;
	if(!strcmp("rule", self->rule->name)){
		pattern = self->rule->children[2];
	}else{
		pattern = self->rule->children[0];
	}
	//pattern = group+
	//group = option+
	//option = atom quantifier?
	//atom = state | string | charset | invset
	for(size_t i = 0; i < pattern->size; ++i){
		const ast *group = pattern->children[i];
		gen_group(group, out);
	}
}

static int cmp_setrangep_a(const void *_a, const void *_b){
	const ast *a = *(const ast**)_a, *b = *(const ast**)_b;
	int aa, ba;
	if(!strcmp("setchar", a->name)){
		aa = *a->text;
	}else{
		aa = *a->children[0]->text;
	}
	if(!strcmp("setchar", b->name)){
		ba = *b->text;
	}else{
		ba = *b->children[0]->text;
	}
	return aa - ba;
}

static void charset_make_range(ast *self, char l, char u){
	clear_ast(self);
	if(l == u){
		self->name = strdup("setchar");//TODO: check allocations
		self->text = strdup((char[]){l, '\0'});
		self->length = 1;
	}else{
		self->name = strdup("setrange");
		self->children = malloc(2*sizeof(ast*));
		self->size = 2;
		self->children[0] = calloc(1, sizeof(ast));
		self->children[0]->text = strdup((char[]){l, '\0'});
		self->children[0]->length = 1;
		self->children[1] = calloc(1, sizeof(ast));
		self->children[1]->text = strdup((char[]){u, '\0'});
		self->children[1]->length = 1;
	}
}

static void charset_invert(ast *atom){
	atom->name = "charset";
	qsort(atom->children, atom->size, sizeof(ast*), cmp_setrangep_a);
	atom->children = realloc(atom->children, (atom->size + 1)*sizeof(ast*));//TODO: check return value
	atom->children[atom->size] = calloc(1, sizeof(ast));
	char l = '\0', u = '\x7F';
	size_t i = 0, j = 0;
	for(char a, b, c, d;;){
		if(i == atom->size){
			charset_make_range(atom->children[j++], l, u);
			break;
		}
		if(!strcmp("setchar", atom->children[i]->name)){
			a = b = *atom->children[i]->text;
		}else{
			a = *atom->children[i]->children[0]->text;
			b = *atom->children[i]->children[1]->text;
		}
		if(++i == atom->size){
			charset_make_range(atom->children[j++], l, a - 1);
			charset_make_range(atom->children[j++], b + 1, u);
			break;
		}
		if(!strcmp("setchar", atom->children[i]->name)){
			c = d = *atom->children[i]->text;
		}else{
			c = *atom->children[i]->children[0]->text;
			d = *atom->children[i]->children[1]->text;
		}
		if(c <= b){
			charset_make_range(atom->children[i], a, d);
		}else{
			charset_make_range(atom->children[j++], l, a - 1);
			u = b + 1;
		}
	}
	for(size_t k = j; k < atom->size; ++k){
		delete_ast(atom->children[k]);
	}
	atom->size = j - 1;
	atom->children = realloc(atom->children, atom->size*sizeof(ast*));
}

void fsa_invsets(state *fsa, size_t num_states){
	for(state *s = fsa; s < fsa + num_states; ++s){
		if(s->parse != state_parse_rule){
			continue;
		}
		ast *pattern;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
		}else{
			pattern = s->rule->children[0];
		}
		for(ast **group = pattern->children; group < pattern->children + pattern->size; ++group){
			for(ast **option = (*group)->children; option < (*group)->children + (*group)->size; ++option){
				ast *atom = (*option)->children[0]->children[0];
				if(strcmp("invset", atom->name)){
					continue;
				}
				charset_invert(atom);
			}
		}
	}
}

void state_gen(const state *fsa, FILE *out){
	state_gen_rule(fsa, out);
}

