#define _GNU_SOURCE //asprintf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#include <dlfcn.h>
#include "parser.h"
#include "ast_compiler.h"

#define _STRINGIFY(z) #z
#define STRINGIFY(z) _STRINGIFY(z)

const char
*src_pre_fmt,
*src_mid_fmt,
*pattern_decl_fmt,//1$<rule_name>
*pattern_pre_merge_fmt,//1$<rule_name>
*pattern_pre_fmt,//1$<rule_name>
*pattern_post_fmt,
*group_pre_fmt,
*group_post1_fmt,
*group_post2_fmt,
*group_singular_pre_fmt,
*group_singular_post_fmt,
*option_fmt,
*atom_once_pre_fmt,
*atom_once_post_fmt,
*atom_optional_pre_fmt,
*atom_optional_post_fmt,//1$<err>
*atom_multiple_pre_fmt,
*atom_multiple_post_fmt,//1$<err>
*atom_repeated_pre_fmt,
*atom_repeated_post_fmt,//1$<err>
*atom_string_fmt,//1$<err>, 2$<t>, 3$<atom->text>
*atom_charset_fmt,//1$<err>, 2$<t>, 3$[charset_spec]
*atom_append_fmt,//1$<err>, 2$<t>, 3$[name]
*atom_merge_fmt,//1$<err>, 2$<t>, 3$[name]
*atom_skip_fmt,//1$<err>, 2$[name]
*state_name_fmt,//1$[name]
*state_name_fmt_trunc,//1$[name], 2$[len]
*state_name_generated_fmt;//1$[offset]

char *get_parser_name(const ast *atom);
char *get_state_name(const state *s);
char *get_charset_spec(const ast *atom);
void write_option_spec(FILE *f, const ast *group);

void write_rule_decl(FILE *f, const ast *pattern, const char *name);

void write_rule(FILE *f, const ast *pattern, const char *name);
void write_generated_rule(FILE *f, const ast *pattern, const char *name);
void write_group(FILE *f, const ast *group);
void write_group_nonsingular(FILE *f, const ast *group);
void write_group_singular(FILE *f, const ast *group);
void write_option(FILE *f, const ast *option);
void write_atom_quantified(FILE *f, const ast *atom, char quantifier, const char *err);
void write_atom_once(FILE *f, const ast *atom, const char *err);
void write_atom_optional(FILE *f, const ast *atom, const char *err);
void write_atom_multiple(FILE *f, const ast *atom, const char *err);
void write_atom_repeated(FILE *f, const ast *atom, const char *err);
void write_atom(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_string(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_charset(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_state(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_special(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_append(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_merge(FILE *f, const ast *atom, const char *err, const char *t);
void write_atom_skip(FILE *f, const ast *atom, const char *err);

int read_symbol(void *dest, size_t size, void *handle, const char *name){
	void *src = dlsym(handle, name);
	if(!src){
		return 0;
	}
	memcpy(dest, &src, size);
	return 1;
}

void *read_fmts(const char *filename){
	void *handle = dlopen(filename, RTLD_LAZY);
	if(!handle){
		fprintf(stderr, "dlopen failed for library \"%s\": %s\n", filename, dlerror());
		return NULL;
	}
#define READ_SYMBOL(name) read_symbol(&name, sizeof(name), handle, STRINGIFY(name))
	if(!(READ_SYMBOL(src_pre_fmt) ||
		READ_SYMBOL(src_mid_fmt) ||
		READ_SYMBOL(pattern_decl_fmt) ||
		READ_SYMBOL(pattern_pre_merge_fmt) ||
		READ_SYMBOL(pattern_pre_fmt) ||
		READ_SYMBOL(pattern_post_fmt) ||
		READ_SYMBOL(group_pre_fmt) ||
		READ_SYMBOL(group_post1_fmt) ||
		READ_SYMBOL(group_post2_fmt) ||
		READ_SYMBOL(group_singular_pre_fmt) ||
		READ_SYMBOL(group_singular_post_fmt) ||
		READ_SYMBOL(option_fmt) ||
		READ_SYMBOL(atom_once_pre_fmt) ||
		READ_SYMBOL(atom_once_post_fmt) ||
		READ_SYMBOL(atom_optional_pre_fmt) ||
		READ_SYMBOL(atom_optional_post_fmt) ||
		READ_SYMBOL(atom_multiple_pre_fmt) ||
		READ_SYMBOL(atom_multiple_post_fmt) ||
		READ_SYMBOL(atom_repeated_pre_fmt) ||
		READ_SYMBOL(atom_repeated_post_fmt) ||
		READ_SYMBOL(atom_string_fmt) ||
		READ_SYMBOL(atom_charset_fmt) ||
		READ_SYMBOL(atom_append_fmt) ||
		READ_SYMBOL(atom_merge_fmt) ||
		READ_SYMBOL(atom_skip_fmt) ||
		READ_SYMBOL(state_name_fmt) ||
		READ_SYMBOL(state_name_fmt_trunc) ||
		READ_SYMBOL(state_name_generated_fmt)
		)){
			dlclose(handle);
			return NULL;
	}
	return handle;
#undef READ_SYMBOL
}

void release_fmts(void *handle){
	src_pre_fmt = NULL;
	src_mid_fmt = NULL;
	pattern_decl_fmt = NULL;
	pattern_pre_merge_fmt = NULL;
	pattern_pre_fmt = NULL;
	pattern_post_fmt = NULL;
	group_pre_fmt = NULL;
	group_post1_fmt = NULL;
	group_post2_fmt = NULL;
	group_singular_pre_fmt = NULL;
	group_singular_post_fmt = NULL;
	option_fmt = NULL;
	atom_once_pre_fmt = NULL;
	atom_once_post_fmt = NULL;
	atom_optional_pre_fmt = NULL;
	atom_optional_post_fmt = NULL;
	atom_multiple_pre_fmt = NULL;
	atom_multiple_post_fmt = NULL;
	atom_repeated_pre_fmt = NULL;
	atom_repeated_post_fmt = NULL;
	atom_string_fmt = NULL;
	atom_charset_fmt = NULL;
	atom_append_fmt = NULL;
	atom_merge_fmt = NULL;
	atom_skip_fmt = NULL;
	state_name_fmt = NULL;
	state_name_fmt_trunc = NULL;
	state_name_generated_fmt = NULL;
	dlclose(handle);
}

void write_rule_decl(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_decl_fmt, name);
}

void write_all(FILE *f, const state *fsm, size_t num_states){
	fprintf(f, src_pre_fmt);
	for(const state *s = fsm; s < fsm + num_states; ++s){
		if(s->parse != state_parse_rule){
			continue;
		}
		ast *pattern;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
		}else{
			pattern = s->rule->children[0];
		}
		char *name = get_state_name(s);
		write_rule_decl(f, pattern, name);
		free(name);
	}
	fprintf(f, src_mid_fmt);
	for(const state *s = fsm; s < fsm + num_states; ++s){
		if(s->parse != state_parse_rule){//s is a special rule that should be defined somewhere else
			continue;
		}
		ast *pattern;
		int is_merge_rule = 1;
		if(!strcmp("rule", s->rule->name)){
			pattern = s->rule->children[2];
			is_merge_rule = *s->rule->children[1]->text == '<';
		}else{
			pattern = s->rule->children[0];//only generated rules do not have name equals "rule", and generated rules are merge rules
		}
		char *name = get_state_name(s);
		//printf("\e[1;32m\"%s\" is %sa merge rule\e[0m\n", name, is_merge_rule ? "" : "NOT ");
		if(is_merge_rule){
			write_generated_rule(f, pattern, name);
		}else{
			write_rule(f, pattern, name);
		}
		free(name);
	}
}

char *get_parser_name(const ast *atom){
	if(!strcmp("special", atom->name)){
		return strdup(atom->text);
	}//otherwise atom->name is "state"
	const state *s = (const state*)atom->text;
	return get_state_name(s);
}

char *get_state_name(const state *s){
	char *ret;
	if(!strcmp("rule", s->rule->name)){//explicit rule, use the name
		asprintf(&ret, state_name_fmt_trunc, s->rule->children[0]->text, (int)s->rule->children[0]->length);
	}else{
		asprintf(&ret, state_name_generated_fmt, (uintptr_t)((void*)s - (void*)get_state_name));
	}
	return ret;
}

void write_rule(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_pre_fmt, name);
	for(size_t i = 0; i < pattern->size; ++i){
		write_group(f, pattern->children[i]);
	}
	fprintf(f, pattern_post_fmt);
}

void write_generated_rule(FILE *f, const ast *pattern, const char *name){
	fprintf(f, pattern_pre_merge_fmt, name);
	for(size_t i = 0; i < pattern->size; ++i){
		write_group(f, pattern->children[i]);
	}
	fprintf(f, pattern_post_fmt);
}

void write_group(FILE *f, const ast *group){
	if(group->size == 1){
		write_group_singular(f, group);
	}else{
		write_group_nonsingular(f, group);
	}
}

void write_group_nonsingular(FILE *f, const ast *group){
	fprintf(f, group_pre_fmt);
	for(size_t i = 0; i < group->size; ++i){
		write_option(f, group->children[i]);
	}
	fprintf(f, group_post1_fmt);
	write_option_spec(f, group);
	fprintf(f, group_post2_fmt);
}

void write_group_singular(FILE *f, const ast *group){
	fprintf(f, group_singular_pre_fmt);
	char quantifier = group->children[0]->size == 2 ? *group->children[0]->children[1]->text : ' ';
	write_atom_quantified(f, group->children[0]->children[0], quantifier, "err");
	fprintf(f, group_singular_post_fmt);
}

void write_option(FILE *f, const ast *option){
	char quantifier = option->size == 2 ? *option->children[1]->text : ' ';
	write_atom_quantified(f, option->children[0], quantifier, "terr");
	fprintf(f, option_fmt);
}

void write_atom_quantified(FILE *f, const ast *atom, char quantifier, const char *err){
	switch(quantifier){
	case ' ':
		write_atom_once(f, atom->children[0], err);
		break;
	case '?':
		write_atom_optional(f, atom->children[0], err);
		break;
	case '*':
		write_atom_multiple(f, atom->children[0], err);
		break;
	default:// quantifier == '+'
		write_atom_repeated(f, atom->children[0], err);
	}
}

void write_atom_once(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_once_pre_fmt);
	write_atom(f, atom, err, "t");
	fprintf(f, atom_once_post_fmt);
}

void write_atom_optional(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_optional_pre_fmt);
	write_atom(f, atom, err, "t");
	fprintf(f, atom_optional_post_fmt, err);
}

void write_atom_multiple(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_multiple_pre_fmt);
	write_atom(f, atom, err, "c");
	fprintf(f, atom_multiple_post_fmt, err);
}

void write_atom_repeated(FILE *f, const ast *atom, const char *err){
	fprintf(f, atom_repeated_pre_fmt);
	write_atom(f, atom, err, "c");
	fprintf(f, atom_repeated_post_fmt, err);
}

void write_atom(FILE *f, const ast *atom, const char *err, const char *t){
	if(!strcmp("state", atom->name)){
		write_atom_state(f, atom, err, t);
	}else if(!strcmp("special", atom->name)){
		write_atom_special(f, atom, err, t);
	}else if(!strcmp("string", atom->name)){
		write_atom_string(f, atom, err, t);
	}else{
		write_atom_charset(f, atom, err, t);
	}
}

static char *charset_spec_add(char *s, char c){
	if(isprint(c)){
		if(c == '\\' || c == '"'){
			*s++ = '\\';
		}
		*s++ = c;
	}else{
		*s++ = '\\';
		switch(c){
		case '\a':
			*s++ = 'a';
			break;
		case '\b':
			*s++ = 'b';
			break;
		case '\f':
			*s++ = 'f';
			break;
		case '\n':
			*s++ = 'n';
			break;
		case '\r':
			*s++ = 'r';
			break;
		case '\t':
			*s++ = 't';
			break;
		case '\v':
			*s++ = 'v';
			break;
		default:
			*s++ = 'x';
			*s++ = "0123456789ABCDEF"[c >> 4];
			*s++ = "0123456789ABCDEF"[c & 0xF];
		}
	}
	return s;
}

void write_atom_string(FILE *f, const ast *atom, const char *err, const char *t){
	char *buf = calloc(1 + 4*strlen(atom->text), sizeof(char));
	for(char *c = (char*)atom->text, *out = buf; *c; ++c){
		out = charset_spec_add(out, *c);
	}
	fprintf(f, atom_string_fmt, err, t, buf);//WARNING: text might not be null terminated.  It isn't normally but I think I fix the strings in ast_interpreter
	free(buf);
}

char *get_charset_spec(const ast *atom){
	char *ret = calloc(2 + 9*atom->size, sizeof(char)), *c = ret;
	if(!strcmp("invset", atom->name)){
		*c++ = '-';
	}else{
		*c++ = '+';
	}
	for(ast **elem = atom->children; elem < atom->children + atom->size; ++elem){
		if(!strcmp("setchar", (*elem)->name)){
			c = charset_spec_add(c, '.');
			c = charset_spec_add(c, *(*elem)->text);
		}else{//(*elem)->name == "setrange"
			c = charset_spec_add(c, '-');
			c = charset_spec_add(c, *(*elem)->children[0]->text);
			c = charset_spec_add(c, *(*elem)->children[1]->text);
		}
	}
	return ret;
}

void write_atom_charset(FILE *f, const ast *atom, const char *err, const char *t){
	char *charset_spec = get_charset_spec(atom);
	fprintf(f, atom_charset_fmt, err, t, charset_spec);
	free(charset_spec);
}

void write_atom_state(FILE *f, const ast *atom, const char *err, const char *t){
	const state *s = (state*)atom->text;
	char assigner = s->rule->size == 3 ? *s->rule->children[1]->text : '<';
	switch(assigner){
	case '=':
		write_atom_append(f, atom, err, t);
		break;
	case '<':
		write_atom_merge(f, atom, err, t);
		break;
	default:// assigner == ':'
		write_atom_skip(f, atom, err);
	}
}

void write_atom_special(FILE *f, const ast *atom, const char *err, const char *t){
	write_atom_merge(f, atom, err, t);
}

void write_atom_append(FILE *f, const ast *atom, const char *err, const char *t){
	char *name = get_parser_name(atom);
	fprintf(f, atom_append_fmt, err, t, name);
	free(name);
}

void write_atom_merge(FILE *f, const ast *atom, const char *err, const char *t){
	char *name = get_parser_name(atom);
	fprintf(f, atom_merge_fmt, err, t, name);
	free(name);
}

void write_atom_skip(FILE *f, const ast *atom, const char *err){
	char *name = get_parser_name(atom);
	fprintf(f, atom_skip_fmt, err, name);
	free(name);
}

void write_option_spec(FILE *f, const ast *group){
	fprintf(f, "\"<option of group>\"");//TODO: actually write out a list of options, maybe by saving the source code of every node.
}

