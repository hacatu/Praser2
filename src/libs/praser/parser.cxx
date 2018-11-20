#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include "parser.hxx"

Ast::Ast(const char *name) : name(name), text(), children() {}

Ast &Ast::append_ast(Ast &c){
	this->children.push_back(c);
	return *this;
}

Ast &Ast::merge_ast(Ast &c){
	if(this->children.size()){
		this->children.insert(this->children.end(), c.children.begin(), c.children.end());
	}else{
		this->children = c.children;
	}
	if(this->text.length()){
		this->text.append(c.text);
	}else{
		this->text = c.text;
	}
	return *this;
}

Ast &Ast::add_text(const std::string_view &a){
	this->text.append(a);
	return *this;
}

Ast &Ast::add_text(std::string &&a){
	this->text.append(a);
	return *this;
}
Ast &Ast::set_tag(const char *a){
	this->name = a;
	return *this;
}

Ast &Ast::print(std::size_t indent){
	return const_cast<Ast&>(const_cast<const Ast*>(this)->print(indent));
}

const Ast &Ast::print(std::size_t indent) const {
	if(this->children.empty()){
		std::printf("%*s%s\n", (int)indent, "", this->name);
	}else{
		std::printf("%*s%s: %s\n", (int)indent, "", this->name, this->text.data());
	}
	for(const Ast &c : this->children){
		c.print(indent + 1);
	}
	return *this;
}

Ast &Ast::clear(){
	this->children.clear();
	this->text.clear();
	return *this;
}

Position::Position(const std::string_view &start) : start(start), curr(0) {}

Position &Position::set_curr(std::size_t i){
	this->curr = i;
	return *this;
}

Position::operator std::size_t () const {
	return this->curr;
}

bool Position::read_setrange(char a, char b, Ast *t){
	if(this->is_end()){
		return false;
	}
	if(a <= this->start[this->curr] && this->start[this->curr] <= b){
		if(t)t->add_text(std::string(1, this->start[this->curr]));
		++this->curr;
		return true;
	}
	return false;
}

bool Position::read_string(const std::string &a, Ast *t){
	if(this->is_end() || this->start.substr(this->curr, this->start.length()) != a){
		return false;
	}
	if(t)t->add_text(a);
	this->curr += a.length();
	return true;
}

bool Position::read_oneOf(const std::string &a, Ast *t){
	if(this->is_end() || a.find(this->start[this->curr]) == a.npos){
		return false;
	}
	if(t)t->add_text(std::string(1, this->start[this->curr]));
	++this->curr;
	return true;
}

bool Position::read_noneOf(const std::string &a, Ast *t){
	if(this->is_end() || a.find(this->start[this->curr]) != a.npos){
		return false;
	}
	if(t)t->add_text(std::string(1, this->start[this->curr]));
	++this->curr;
	return true;
}

bool Position::read_charset_prefix(const std::string &a, Ast *t){
	if(this->is_end()){
		return false;
	}
	bool found = false;
	for(const char *s = a.data() + 1; *s;){
		++s;
		if(s[-1] == '.'){
			if(this->start[this->curr] == *s++){
				found = true;
				break;
			}
		}else if(*s++ > this->start[this->curr]){
			s++;
		}else if(this->start[this->curr] <= *s++){
			found = true;
			break;
		}
	}
	if(found ^ (a[0] == '-')){
		if(t)t->add_text(std::string(1, this->start[this->curr]));
		++p->curr;
		return true;
	}
	return false;
}

bool Position::read_newline(){
	if(this->is_end() || this->start[this->curr] != '\n'){
		return false;
	}
	++this->curr;
	return true;
}

bool Position::parse_hex2(Ast *t){
	Position s = *this;
	Ast *c = alloc_ast();
	if(this->read_string("x", nullptr) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c)) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c))){
		unsigned x, f;
		f = std::sscanf(c->text.data(), "%2x", &x);
		delete_ast(c);
		if(!f){
			this->set_curr(s);
			return false;
		}
		if(t)t->add_text(std::string(1, *(char*)&x));
		return true;
	}
	delete_ast(c);
	return false;
}

bool Position::parse_hex4(Ast *t){
	Position s = *this;
	Ast *c = alloc_ast();
	if(this->read_string("X", nullptr) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c)) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c)) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c)) &&
	   (this->read_setrange('0', '9', c) || this->read_setrange('a', 'f', c) || this->read_setrange('A', 'F', c))){
		unsigned x, f;
		f = std::sscanf(c->text.data(), "%4x", &x);
		delete_ast(c);
		if(!f){
			this->set_curr(s);
			return false;
		}
		if(t)t->add_text(std::string(1, *(char*)&x));
		return true;
	}
	delete_ast(c);
	return false;
}

const char *esc_seq_parser(Ast &t, Position &p){
	Position s(p);
	if(!p.read_string("\\", nullptr)){
		return "esc_seq";
	}
	if(p.parse_hex2(&t) || p.parse_hex4(&t)){
		return "";
	}
	//abfnrtv
	if(!p.is_end()){
		char repr;
		switch(p.start[p.curr]){
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
			repr = p.start[p.curr];
			break;
		}
		++p.curr;
		t.add_text(std::string(1, repr));
		return "";
	}
	p.set_curr(s);
	return "esc_seq";
}

const char *always_fail_parser(Ast &t, Position &p){
	return "to fail";
}

bool Position::is_end() const {
	return this->curr == this->start.length();
}

void Position::log_err(const std::string &err){
	std::size_t line = 1, col = 1, remaining = 0;
	Position e = *this, s = *this;
	while(--this->curr >= 0 && this->start[this->curr] != '\n'){
		++col;
	}
	++this->curr;
	s.set_curr(*this);
	while(--this->curr >= 0){
		if(this->start[this->curr] == '\n'){
			++line;
		}
	}
	printf("Line %zu, col %zu: expected %s but found ", line, col, err.data());
	if(e.is_end()){
		printf("end\n");
	}else if(e.start[e.curr] == '\n'){
		printf("newline\n");
	}else{
		this->set_curr(e);
		while(!this->is_end() && this->start[this->curr++] != '\n'){
			++remaining;
		}
		printf("\"%.*s\"\n", (int)(1 + remaining), this->start.data() + e.curr);
	}
	printf("%.*s\n", (int)(col + remaining), this->start.data() + s.curr);
	printf("%*s\n", (int)col, "^");
}

Ast *(*alloc_ast)();
void (*delete_ast)(Ast*);
void (*free_ast)(Ast*);

