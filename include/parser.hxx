#ifndef __UMBRELLA_PARSER_HXX__
#define __UMBRELLA_PARSER_HXX__

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include <functional>

struct Ast{
	const char *name;
	std::string text;
	std::vector<std::reference_wrapper<Ast>> children;
	
	Ast(const char* = nullptr);
	
	Ast &append_ast(Ast&);
	Ast &merge_ast(Ast&);
	Ast &add_text(const std::string_view&);
	Ast &add_text(std::string&&);
	Ast &set_tag(const char*);
	Ast &print(std::size_t = 0);
	const Ast &print(std::size_t = 0) const;
	Ast &clear();
};

struct Position{
	const std::string_view start;
	std::size_t curr;
	
	Position(const std::string_view&);
	
	Position &set_curr(std::size_t);
	operator std::size_t () const;
	
	bool read_setrange(char a, char b, Ast*);
	bool read_string(const std::string&, Ast*);
	bool read_oneOf(const std::string&, Ast*);
	bool read_noneOf(const std::string&, Ast*);
	bool read_charset_prefix(const std::string&, Ast*);
	bool read_newline();
	bool parse_hex2(Ast*);
	bool parse_hex4(Ast*);
	bool is_end() const;
	void log_err(const std::string&);
};

const char *esc_seq_parser(Ast&, Position&);
const char *always_fail_parser(Ast&, Position&);

extern Ast *(*alloc_ast)();
extern void (*delete_ast)(Ast*);
extern void (*free_ast)(Ast*);

#endif

