#ifndef __UMBRELLA_PARSER_H__
#define __UMBRELLA_PARSER_H__

#include <stddef.h>

typedef struct ast{
	const char *name;
	const char *text;
	size_t length;
	//TODO: Replace with vector or something.
	size_t size;
	struct ast **children;
} ast;

typedef struct{
	const char *start;
	const char *end;
	const char *curr;
} position;

position canonicalize_indents(const position *p, size_t tab_spaces);

void append_ast(ast *t, ast *c);
void merge_ast(ast *t, ast *c);
void add_text(ast *t, const char *a, size_t l);
void set_tag(ast *t, const char *a);
int read_setrange(char a, char b, ast *t, position *p);
int read_string(const char *a, ast *t, position *p);
int read_oneOf(const char *a, ast *t, position *p);
int read_noneOf(const char *a, ast *t, position *p);
int read_newline(position *p);
int read_indent(position *p);
int read_dedent(position *p);
int is_end(const position *p);

void print_ast(const ast *t);
void log_err(const char *err, position p);

extern ast *(*alloc_ast)(void);
extern void (*delete_ast)(ast*);
extern void (*free_ast)(ast*);
void clear_ast(ast*);
ast *flatten_ast(ast*);

int parse_hex2(ast*, position*);
int parse_hex4(ast*, position*);

const char *mmap_open(const char *name, position *out);

void mmap_close(const position *p);

const char *esc_seq_parser(ast*, position*);

#endif

