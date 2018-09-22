/*
 * parser.c
 * Parser, ast, and position utility functions including ast allocators, position constructors, and special parsers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"

ast *_alloc_ast(void);
void _delete_ast(ast*);
void _free_ast(ast*);

ast *(*alloc_ast)(void) = _alloc_ast;
void (*delete_ast)(ast*) = _delete_ast;
void (*free_ast)(ast*) = _free_ast;

int parse_hex2(ast *t, position *p){//TODO: Make all builtin parse/read functions that are '<' rules respect the merge_ast rule.  Ugh OMG.
	position s = *p;
	ast *c = alloc_ast();
	if(read_string("x", NULL, p) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p)) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p))){
		unsigned x, f;
		f = sscanf(c->text, "%2x", &x);
		delete_ast(c);
		if(!f){
			*p = s;
			return 0;
		}
		add_text(t, (char*)&x, 1);
		return 1;
	}
	delete_ast(c);
	return 0;
}

int parse_hex4(ast *t, position *p){
	position s = *p;
	ast *c = alloc_ast();
	if(read_string("X", NULL, p) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p)) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p)) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p)) &&
	   (read_setrange('0', '9', c, p) || read_setrange('a', 'f', c, p) || read_setrange('A', 'F', c, p))){
		unsigned x, f;
		f = sscanf(c->text, "%4x", &x);
		delete_ast(c);
		if(!f){
			*p = s;
			return 0;
		}
		add_text(t, (char*)&x, 1);
		return 1;
	}
	delete_ast(c);
	return 0;
}

const char *esc_seq_parser(ast *t, position *p){
	position s = *p;
	if(!read_string("\\", NULL, p)){
		return "esc_seq";
	}
	if(parse_hex2(t, p) || parse_hex4(t, p)){
		return NULL;
	}
	//abfnrtv
	if(!is_end(p)){
		char repr;
		switch(*p->curr){
			case 'a':
			repr = '\a';
			break;
			case 'b':
			repr = '\b';
			break;
			case 'f':
			repr = '\f';
			break;
			case 'n':
			repr = '\n';
			break;
			case 'r':
			repr = '\r';
			break;
			case 't':
			repr = '\t';
			break;
			case 'v':
			repr = '\v';
			break;
			default:
			repr = *p->curr;
			break;
		}
		++p->curr;
		add_text(t, &repr, 1);
		return NULL;
	}
	*p = s;
	return "esc_seq";
}

const char *always_fail_parser(ast *t, position *p){
	return "to fail";
}

void append_ast(ast *t, ast *c){
	if(!t){
		delete_ast(c);
		return;
	}
	size_t size = t->size;
	ast **tmp = realloc(t->children, (size + 1)*sizeof(ast*));
	if(!tmp){
		//TODO: Handle error
		return;
	}
	t->children = tmp;
	t->children[size] = c;
	++t->size;
}

void merge_ast(ast *t, ast *c){
	if(!t){
		delete_ast(c);
		return;
	}
	if(t->size){
		size_t size = t->size + c->size;
		void *tmp = realloc(t->children, size*sizeof(ast*));
		if(!tmp){
			//TODO: Handle error
			return;
		}
		t->children = tmp;
		memcpy(t->children + t->size, c->children, c->size*sizeof(ast*));
		t->size = size;
		free(c->children);
	}else{
		t->children = c->children;
		t->size = c->size;
	}
	if(t->length){
		size_t length = t->length + c->length;
		void *tmp = realloc((void*)t->text, length*sizeof(char));
		if(!tmp){
			t->children = realloc(t->children, t->size*sizeof(ast*));
			return;
		}
		t->text = tmp;
		memcpy((void*)t->text + t->length, c->text, c->length*sizeof(char));
		t->length = length;
		free((char*)c->text);//discard const qualifier
	}else{
		t->text = c->text;
		t->length = c->length;
	}
	free_ast(c);
}

int read_setrange(char a, char b, ast *t, position *p){
	if(is_end(p)){
		return 0;
	}
	if(a <= *p->curr && *p->curr <= b){
		add_text(t, p->curr, 1);
		++p->curr;
		return 1;
	}
	return 0;
}

int read_string(const char *a, ast *t, position *p){
	if(is_end(p)){
		return 0;
	}
	position s = *p;
	while(*a && *a == *p->curr){
		++a;
		++p->curr;
	}
	if(*a){
		*p = s;
		return 0;
	}
	add_text(t, s.curr, p->curr - s.curr);
	return 1;
}
/*
char str_getc_esc(const char **s){
	if(*(*s)++ != '\\'){
		return (*s)[-1];
	}
	char ret = 0;
	switch(**s){
	case 'a':
		++*s;
		return '\a';
	case 'b':
		++*s;
		return '\b';
	case 'e':
		++*s;
		return '\e';
	case 'f':
		++*s;
		return '\f';
	case 'n':
		++*s;
		return '\n';
	case 'r':
		++*s;
		return '\r';
	case 't':
		++*s;
		return '\t';
	case 'v':
		++*s;
		return '\v';
	case 'x':
		++*s;
		if('0' <= **s && **s <= '9'){
			ret = (**s - '0') << 4;
		}else if('A' <= **s && **s <= 'F'){
			ret = (**s - 'A' + 10) << 4;
		}else if('a' <= **s && **s <= 'f'){
			ret = (**s - 'a' + 10) << 4;
		}else{
			return '\0';
		}
		++*s;
		if('0' <= **s && **s <= '9'){
			ret |= **s - '0';
		}else if('A' <= **s && **s <= 'F'){
			ret |= **s - 'A' + 10;
		}else if('a' <= **s && **s <= 'f'){
			ret |= **s - 'a' + 10;
		}else{
			return '\0';
		}
		++*s;
		return ret;
	default:
		if('0' <= **s && **s <= '7'){
			ret = (*(*s)++ - '0') << 6; 
		}else{
			return *(*s)++;
		}
		if('0' <= **s && **s <= '7'){
			ret |= (*(*s)++ - '0') << 3;
		}else{
			return '\0';
		}
		return ('0' <= **s && **s <= '7') ? ret | (*(*s)++ - '0') : '\0';
	}
}
*/
int read_charset_prefix(const char *a, ast *t, position *p){
	if(is_end(p)){
		return 0;
	}
	int found = 0;
	for(const char *s = a + 1; *s;){
		++s;
		if(s[-1] == '.'){
			if(*p->curr == *s++){
				found = 1;
				break;
			}
		}else if(*s++ > *p->curr){
			s++;
		}else if(*p->curr <= *s++){
			found = 1;
			break;
		}
	}
	if(found ^ (*a == '-')){
		add_text(t, p->curr, 1);
		++p->curr;
		return 1;
	}
	return 0;
}

int read_oneOf(const char *a, ast *t, position *p){
	if(is_end(p)){
		return 0;
	}
	while(*a && *a != *p->curr){
		++a;
	}
	if(*a){
		add_text(t, p->curr, 1);
		++p->curr;
		return 1;
	}
	return 0;
}

int read_noneOf(const char *a, ast *t, position *p){
	if(is_end(p)){
		return 0;
	}
	while(*a && *a != *p->curr){
		++a;
	}
	if(*a){
		return 0;
	}
	add_text(t, p->curr, 1);
	++p->curr;
	return 1;
}

int is_end(const position *p){
	return p->curr == p->end;
}

int read_newline(position *p){
	if(is_end(p)){
		return 0;
	}
	if(*p->curr == '\n'){
		++p->curr;
		return 1;
	}
	return 0;
}

int read_indent(position *p){
	if(is_end(p)){
		return 0;
	}
	if(*p->curr == '\x12'){//Device control 2, generated by preprocessing
		++p->curr;
		return 1;
	}
	return 0;
}

int read_dedent(position *p){
	if(is_end(p)){
		return 0;
	}
	if(*p->curr == '\x14'){//Device control 4, generated by preprocessing
		++p->curr;
		return 1;
	}
	return 0;
}

void add_text(ast *t, const char *a, size_t l){//no longer uses pointers to input so all text pointers are dynamic memory.
	if(!t){
		return;
	}
	char *tmp = realloc((char*)t->text, (t->length + l)*sizeof(char));
	if(!tmp){
		//TODO: handle memory error
	}else{
		memcpy(tmp + t->length, a, l*sizeof(char));
		t->text = tmp;
		t->length += l;
	}
}

void set_tag(ast *t, const char *a){
	if(t){
		t->name = a;
	}
}

static void print_ast_helper(const ast *r, size_t id, size_t di){
	if(!r){
		return;
	}
	if(!r->length){
		printf("%*s%s\n", (int)id, "", r->name);
	}else{
		printf("%*s%s: %.*s\n", (int)id, "", r->name, (int)r->length, r->text);
	}
	for(int i = 0; i < r->size; ++i){
		print_ast_helper(r->children[i], id + di, di);
	}
}

void print_ast(const ast *t){
	print_ast_helper(t, 0, 1);
}

ast *_alloc_ast(void){
	return calloc(1, sizeof(ast));
}

void _delete_ast(ast *t){
	for(size_t i = 0; i < t->size; ++i){
		_delete_ast(t->children[i]);
	}
	free((char*)t->text);//discard const qualifier
	free(t->children);
	free_ast(t);
}

void _free_ast(ast *t){
	free(t);
}

void clear_ast(ast *t){
	for(size_t i = 0; i < t->size; ++i){
		delete_ast(t->children[i]);
	}
	free(t->children);
	t->children = NULL;
	t->size = 0;
	free((char*)t->text);
	t->text = NULL;
	t->length = 0;
}

void log_err(const char *err, position p){
	size_t line = 1, col = 1, remaining = 0;
	position e = p, s;
	while(--p.curr >= p.start && *p.curr != '\n'){
		++col;
	}
	++p.curr;
	s = p;
	while(--p.curr >= p.start){
		if(*p.curr == '\n'){
			++line;
		}
	}
	printf("Line %zu, col %zu: expected %s but found ", line, col, err);
	if(e.curr == e.end){
		printf("end\n");
	}else if(*e.curr == '\n'){
		printf("newline\n");
	}else{
		p = e;
		while(++p.curr < p.end && *p.curr != '\n'){
			++remaining;
		}
		printf("\"%.*s\"\n", (int)(1 + remaining), e.curr);
	}
	printf("%.*s\n", (int)(col + remaining), s.curr);
	printf("%*s\n", (int)col, "^");
}

ast *flatten_ast(ast *t){
	ast *ret = t;
	for(size_t i = 0; i < t->size; ++i){
		t->children[i] = flatten_ast(t->children[i]);
	}
	if(t->size == 1){
		if(t->children[0]->name){
			ret = t->children[0];
			free_ast(t);
		}else{
			t->text = t->children[0]->text;
			t->length = t->children[0]->length;
			free_ast(t->children[0]);
			free(t->children);
			t->size = 0;
		}
	}
	return ret;
}

void init_position_from_str(position *self, const char *str){
	self->curr = self->start = str;
	self->end = str + strlen(str);
}

position canonicalize_indents(const position *p, size_t tab_spaces){//note this does not currently produce multiple indent/dedent characters in a row even if multiple indents or dedents are performed because this is a problem with mixed tabs and spaces.  If you promise not to mix tabs and spaces I might fix this.
	position ret = {0};
	ret.start = malloc(sizeof(char)*(p->end - p->start));
	if(!ret.start){
		return ret;
	}
	ret.end = ret.start + (p->end - p->start);
	ret.curr = ret.start;
	size_t last_indent = 0;
	size_t indent = 0;
	char *ir = (char*)ret.curr;
	const char *ip = p->curr;
	while(ip < p->end){
		last_indent = indent;
		indent = 0;
		while(ip < p->end){
			if(*ip == ' '){
				++ip;
				++indent;
			}else if(*ip == '\t'){
				++ip;
				indent += tab_spaces;
			}else{
				break;
			}
		}
		if(indent < last_indent){
			*(ir++) = '\x14';//Device control 4, should not be in properly formed input, although presently this is not checked.
		}else if(indent > last_indent){
			*(ir++) = '\x12';//Device control 2
		}
		do{
			*(ir++) = *ip;
		}while(*(ip++) != '\n');
	}
	ret.end = ir;
	ret.start = realloc((char*)ret.start, (ret.end - ret.start)*sizeof(char));
	ret.end = ret.start + (ret.end - ret.curr);
	ret.curr = ret.start;
	return ret;
}

const char *mmap_open(const char *name, position *out){
	int fd = open(name, O_RDONLY);
	if(fd == -1){
		return "Could not open file";
	}
	struct stat buf;
	if(fstat(fd, &buf)){
		close(fd);
		return "Could not stat file";
	}
	out->start = mmap(NULL, buf.st_size*sizeof(char), PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if(out->start == MAP_FAILED){
		return "Could not mmap file";
	}
	out->curr = out->start;
	out->end = out->start + buf.st_size;
	return NULL;
}

void mmap_close(const position *p){
	munmap((void*)p->start, p->end - p->start);//cast to non const pointer.
}

