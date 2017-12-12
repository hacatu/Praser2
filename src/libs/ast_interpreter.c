/*
 * ast_interpreter.c
 * Runs a parser specified by an ast on some text.  The ast should be obtained by using a compiled version of parser_parser on a description (.pra).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast_interpreter.h"

struct{
	size_t len, cap;
	special_state *states;
} special_states;

void forall_ast_nodes_postorder(ast_fn f, ast *t, void *data){
	for(size_t i = 0; i < t->size; ++i){
		forall_ast_nodes_postorder(f, t->children[i], data);
	}
	f(t, data);
}

void forall_ast_nodes_preorder(ast_fn f, ast *t, void *data){
	f(t, data);
	for(size_t i = 0; i < t->size; ++i){
		forall_ast_nodes_preorder(f, t->children[i], data);
	}
}

static void ast_fn_count_outrules(const ast *n, size_t *c){
	if((!strcmp("rule", n->name)) || (!strcmp("parens", n->name))){
		++*c;
	}
}

static int cmp_special_states(const void *a, const void *b){
	return strcmp(*(const char*const*)a, *(const char*const*)b);
}

void _register_special_states(special_state s, ...){
	va_list args;
	va_start(args, s);
	for(; s.name; s = va_arg(args, special_state)){
		if(special_states.len == special_states.cap){
			size_t cap = special_states.cap ? 1.6*special_states.cap : 2;
			special_state *tmp = realloc(special_states.states, cap*sizeof(special_state));
			if(!tmp){
				//TODO: handle memory error.
			}else{
				special_states.states = tmp;
				special_states.cap = cap;
			}
		}
		special_states.states[special_states.len++] = s;
	}
	va_end(args);
	qsort(special_states.states, special_states.len, sizeof(special_state), cmp_special_states);
}

static special_state find_special_parse_fn(const ast *key){
	char *name = calloc(key->length + 1, sizeof(char));
	if(!name){
		return (special_state){0};
	}
	memcpy(name, key->text, key->length*sizeof(char));
	special_state *s = bsearch(&name, special_states.states, special_states.len, sizeof(special_state), cmp_special_states);
	free(name);
	if(!s){
		return (special_state){0};
	}
	return *s;
}

static int make_state(state *fsa, ast *r, size_t *u, int unbound_specials){
	ast *pattern;
	if(!strcmp("rule", r->name)){
		pattern = r->children[2];
		if(pattern->size == 1){
			const ast *group = pattern->children[0];
			if(group->size == 1){
				const ast *option = group->children[0];
				if(option->size == 1){
					const ast *atom = option->children[0]->children[0];
					if((!strcmp("name", atom->name)) && (!strncmp("special", atom->text, atom->length))){
						special_state s = find_special_parse_fn(r->children[0]);
						if(!s.name && !unbound_specials){
							printf("No special state is registered for \"%*s\".\n", (int)r->children[0]->length, r->children[0]->text);
							return 0;
						}
						fsa[(*u)++] = (state){.rule = r, .parse = s.parse, .gen = s.gen};
						return 1;
					}
				}
			}
		}
	}else{//parens
		pattern = r->children[0];
	}
	for(ast **group = pattern->children; group < pattern->children + pattern->size; ++group){
		for(ast **option = (*group)->children; option < (*group)->children + (*group)->size; ++option){
			ast *atom = (*option)->children[0];
			if(!strcmp("parens", atom->children[0]->name)){
				ast *newCall = alloc_ast();
				*newCall = (ast){.name = "state", .text = (char*)(fsa + *u)};
				make_state(fsa, atom->children[0], u, unbound_specials);
				atom->children[0] = newCall;
			}
		}
	}
	fsa[(*u)++] = (state){.rule = r, .parse = state_parse_rule, .gen = state_gen_rule};
	return 1;
}

static int link_rule_calls(size_t num_states, state *fsa){
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
				ast *atom = (*option)->children[0];
				if(!strcmp("name", atom->children[0]->name)){
					int linked = 0;
					for(state *s = fsa; s < fsa + num_states; ++s){
						if(strcmp("rule", s->rule->name)){
							continue;
						}
						if(atom->children[0]->length != s->rule->children[0]->length){
							continue;
						}
						if(!strncmp(atom->children[0]->text, s->rule->children[0]->text, atom->children[0]->length)){
							free((void*)atom->children[0]->text);
							*atom->children[0] = (ast){.name = "state", .text = (char*)s};
							linked = 1;
							break;
						}
					}
					if((!linked) && strncmp("special", atom->children[0]->text, atom->children[0]->length)){
						printf("No rule with name \"%*s\" found.\n", (int)atom->children[0]->length, atom->children[0]->text);
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

static void canonicalize_used_text(size_t num_states, state *fsa){
	for(state *s = fsa; s < fsa + num_states; ++s){
		if(s->parse != state_parse_rule){
			continue;
		}
		ast *pattern;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
			size_t length = s->rule->children[0]->length + 1;
			char *tmp = realloc((void*)s->rule->children[0]->text, length*sizeof(char));
			if(!tmp){
				//TODO: Handle memory error.
				return;
			}
			tmp[length - 1] = '\0';
			s->rule->children[0]->text = tmp;
		}else{
			pattern = s->rule->children[0];
		}
		for(ast **group = pattern->children; group < pattern->children + pattern->size; ++group){
			for(ast **option = (*group)->children; option < (*group)->children + (*group)->size; ++option){
				ast *atom = (*option)->children[0];
				if(!strcmp("string", atom->children[0]->name)){
					size_t length = atom->children[0]->length + 1;
					char *tmp = realloc((void*)atom->children[0]->text, length*sizeof(char));
					if(!tmp){
						//TODO: Handle memory error.
						return;
					}
					tmp[length - 1] = '\0';
					atom->children[0]->text = tmp;
				}
			}
		}
	}
}

const state *ast_to_fsa(ast *r, size_t *num_states, int unbound_specials){
	*num_states = 0;
	forall_ast_nodes_postorder((ast_fn)ast_fn_count_outrules, r, num_states);
	state *fsa = malloc(*num_states*sizeof(state));
	if(!fsa){
		return NULL;
	}
	size_t num_states_created = 0;
	for(size_t i = 0; i < r->size; ++i){
		if(!make_state(fsa, r->children[i], &num_states_created, unbound_specials)){
			memset(fsa + num_states_created, 0, (*num_states - num_states_created)*sizeof(state));
			delete_nonroot_fsa(fsa, *num_states);
			*num_states = 0;
			return NULL;
		}
	}
	canonicalize_used_text(*num_states, fsa);
	if(!link_rule_calls(*num_states, fsa)){
		memset(fsa + num_states_created, 0, (*num_states - num_states_created)*sizeof(state));
		delete_nonroot_fsa(fsa, *num_states);
		*num_states = 0;
		return NULL;
	}
	return fsa;
}

static const char *parse_atom(const ast *atom, ast *t, position *p){
	//state | string | charset | invset
	if(!strcmp("state", atom->name)){
		const state *s = (state*)atom->text;
		ast *c;
		const char *err;
		char assigner = s->rule->size == 3 ? *s->rule->children[1]->text : '<';
		switch(assigner){
			case '=':
			c = alloc_ast();
			err = s->parse(s, c, p);
			if(err){
				delete_ast(c);
				return err;
			}
			append_ast(t, c);
			return NULL;
			break;//better safe than sorry with these switch statements, am I right?
			case '<':
			return s->parse(s, t, p);
			break;
		}
		//case ':':
		ast r = {0};
		err = s->parse(s, &r, p);
		clear_ast(&r);
		return err;
	}else if(!strcmp("string", atom->name)){
		if(read_string(atom->text, t, p)){
			return NULL;
		}
		return atom->text;
	}else{//invset or charset
		if(is_end(p)){
			return "charset char";
		}
		int matches = 0;
		for(size_t i = 0; i < atom->size; ++i){
			const ast *elem = atom->children[i];
			if(!strcmp("setchar", elem->name)){
				if(*elem->text == *p->curr){
					matches = 1;
					break;
				}
			}else{//elem->name == "setrange"
				if(*p->curr >= *elem->children[0]->text && *p->curr <= *elem->children[1]->text){
					matches = 1;
					break;
				}
			}
		}
		if(matches ^ !strcmp("invset", atom->name)){
			add_text(t, p->curr, 1);
			++p->curr;
			return NULL;
		}
		return "charset char";
	}
}

static const char *parse_option(const ast *option, ast *t, position *p){//TODO: Replace incorrect append_ast() calls with merge_ast() and maybe find a way to cut down on allocations.
	position l = *p;
	const char *err;
	const ast *atom = option->children[0]->children[0];
	if(option->size == 1){
		return parse_atom(atom, t, p);
	}else if(*option->children[1]->text == '?'){
		if(parse_atom(atom, t, p)){
			*p = l;
		}
		return NULL;
	}else if(*option->children[1]->text == '*'){
		ast *c = alloc_ast();
		while(!parse_atom(atom, c, p)){
			merge_ast(t, c);
			c = alloc_ast();
			l = *p;
		};
		delete_ast(c);
		*p = l;
		return NULL;
	}else{//quantifier == "+"
		ast *c = alloc_ast();
		err = parse_atom(atom, c, p);
		if(err){
			delete_ast(c);
			return err;
		}
		do{
			merge_ast(t, c);
			c = alloc_ast();
			l = *p;
		}while(!parse_atom(atom, c, p));
		delete_ast(c);
		*p = l;
		return NULL;
	}
}

static const char *parse_group(const ast *group, ast *t, position *p){
	position s = *p, e;
	const char *err = NULL, *terr = NULL;
	for(size_t i = 0; i < group->size; ++i){
		const ast *option = group->children[i];
		terr = parse_option(option, t, p);
		if(terr){
			if(p->curr != s.curr){
				e = *p;
				*p = s;
				err = terr;
			}
			if(i < group->size - 1){
				clear_ast(t);
			}
		}else{
			return NULL;
		}
	}
	if(!err){
		return terr;
	}
	*p = e;
	return err;
}

const char *state_parse_rule(const state *self, ast *t, position *p){//These two functions definitely need more data.  And will be hard to write.  Nevermind, I did it after like three or four days, no big deal.
	const ast *pattern;
	if(!strcmp("rule", self->rule->name)){//TODO: Remove this check by having two separate functions.
		pattern = self->rule->children[2];
		t->name = self->rule->children[0]->text;
	}else{
		pattern = self->rule->children[0];
	}
	//pattern = group+
	//group = option+
	//option = atom quantifier?
	//atom = state | string | charset | invset
	const char *err = NULL;
	for(size_t i = 0; i < pattern->size; ++i){
		const ast *group = pattern->children[i];
		ast *c = alloc_ast();
		err = parse_group(group, c, p);
		if(err){
			delete_ast(c);
			return err;
		}
		merge_ast(t, c);
	}
	return NULL;
}

const char *state_parse(const state *fsa, ast *t, position *p){
	const char *err = fsa->parse(fsa, t, p);
	if(err){
		return err;
	}else if(!is_end(p)){
		return "EOF";
	}
	return NULL;
}

void delete_nonroot_fsa(state *fsa, size_t num_states){
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
				ast *atom = (*option)->children[0];
				if(!strcmp("state", atom->children[0]->name)){
					atom->children[0]->text = NULL;
				}
			}
		}
		if(strcmp("rule", s->rule->name)){//s->rule->name == "parens"
			delete_ast((ast*)s->rule);//discard const qualifier
		}
	}
	free(special_states.states);
	special_states.states = NULL;
	special_states.cap = special_states.len = 0;
	free(fsa);
}

