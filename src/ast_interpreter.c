//ast_interpreter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef void (*ast_fn)(ast*, void*);
typedef struct state state;
typedef const char *(*state_parse_fn)(const state*, ast*, position*);
struct state{
	const ast *rule;
	state_parse_fn parse;
};

const char *state_parse_rule(const state *self, ast*, position *p);
const char *state_parse_special(const state *self, ast*, position *p);

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

void ast_fn_count_outrules(const ast *n, size_t *c){
	if((!strcmp("rule", n->name)) || (!strcmp("parens", n->name))){
		++*c;
	}
}

void make_state(state *fsa, ast *r, size_t *u){
	ast *pattern;
	if(!strcmp("rule", r->name)){
		pattern = r->children[2];
		if(pattern->size == 1){
			const ast *group = pattern->children[0];
			if(group->size == 1){
				const ast *option = group->children[0];
				if(option->size == 1){
					const ast *atom = option->children[0];
					if((!strcmp("name", atom->name)) && (!strncmp("special", atom->text, atom->length))){
						fsa[(*u)++] = (state){.rule = r, .parse = state_parse_special};//TODO: find the actual special function to use
						return;
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
				make_state(fsa, atom->children[0], u);
				atom->children[0] = newCall;
			}
		}
	}
	fsa[(*u)++] = (state){.rule = r, .parse = state_parse_rule};
}

void link_rule_calls(size_t num_states, state *fsa){
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
					for(state *s = fsa; s < fsa + num_states; ++s){
						if(strcmp("rule", s->rule->name)){
							continue;
						}
						if(atom->children[0]->length != s->rule->children[0]->length){
							continue;
						}
						if(!strncmp(atom->children[0]->text, s->rule->children[0]->text, atom->children[0]->length)){
							*atom->children[0] = (ast){.name = "state", .text = (char*)s};
							break;
						}
					}
				}
			}
		}
	}
}

const state *ast_to_fsa(ast *r){
	size_t num_states = 0;
	forall_ast_nodes_postorder((ast_fn)ast_fn_count_outrules, r, (void*)&num_states);
	state *fsa = malloc(num_states*sizeof(state));
	size_t num_states_created = 0;
	for(size_t i = 0; i < r->size; ++i){
		make_state(fsa, r->children[i], &num_states_created);
	}
	link_rule_calls(num_states, fsa);
	return fsa;
}

const char *parse_atom(const ast *atom, ast *t, position *p){
	//state | string | charset | invset
	if(!strcmp("state", atom->name)){
		const state *s = (state*)atom->text;
		ast *c;
		const char *err;
		switch(*s->rule->children[1]->text){
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
		ast r;
		err = s->parse(s, &r, p);
		clear_ast(&r);
		return err;
	}else if(!strcmp("string", atom->name)){
		char *s = malloc((atom->length + 1)*sizeof(char));
		if(read_string(strncpy(s, atom->text, atom->length), NULL, p)){
			return NULL;
		}
		return s;
	}else{
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
			++p->curr;
			return NULL;
		}
		return "charset char";
	}
}

const char *parse_option(const ast *option, ast *t, position *p){//TODO: Replace incorrect append_ast() calls with merge_ast() and maybe find a way to cut down on allocations.
	position l = *p;
	const char *err;
	const ast *atom = option->children[0];
	if(option->size == 1){
		return parse_atom(atom, t, p);
	}else if(*option->children[1]->text == '?'){
		if(parse_atom(atom, t, p)){
			*p = l;
		}
		return NULL;
	}else if(*option->children[1]->text == '*'){
		ast *c = alloc_ast();
		while(!parse_atom(atom, t, p)){
			append_ast(t, c);
			c = alloc_ast();
			l = *p;
		};
		delete_ast(c);
		*p = l;
		return NULL;
	}else{//quantifier == "+"
		ast *c = alloc_ast();
		err = parse_atom(atom, t, p);
		if(err){
			delete_ast(c);
			return err;
		}
		do{
			append_ast(t, c);
			c = alloc_ast();
			l = *p;
		}while(!parse_atom(atom, c, p));
		delete_ast(c);
		*p = l;
		return NULL;
	}
}

const char *parse_group(const ast *group, ast *t, position *p){
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
	}
	return NULL;
}

const char *state_parse_special(const state *self, ast *t, position *p){
	return "NYI";
}

//TODO: Unit test this to bits, and be lenient on the extra layers generated by improper merging -- it's an error I anticipate and I've got bigger fish to fry.

int main(void){
	
}

