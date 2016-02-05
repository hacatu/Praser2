#ifndef __PARSER_PARSER_H__
#define __PARSER_PARSER_H__

#include "parser.h"

extern const char const
*start_tag,
*rule_tag,
*name_tag,
*assign_tag,
*pattern_tag,
*group_tag,
*option_tag,
*atom_tag,
*quantifier_tag,
*parens_tag,
*invset_tag,
*charset_tag,
*setrange_tag,
*setchar_tag,
*string_tag;

const char *start_parser(ast*, position*);
const char *rule_parser(ast*, position*);
const char *name_parser(ast*, position*);
const char *assign_parser(ast*, position*);
const char *pattern_parser(ast*, position*);
const char *group_parser(ast*, position*);
const char *option_parser(ast*, position*);
const char *atom_parser(ast*, position*);
const char *quantifier_parser(ast*, position*);
const char *parens_parser(ast*, position*);
const char *invset_parser(ast*, position*);
const char *charset_parser(ast*, position*);
const char *setrange_parser(ast*, position*);
const char *setchar_parser(ast*, position*);
const char *string_parser(ast*, position*);
const char *hex_parser(ast*, position*);
const char *dec_parser(ast*, position*);
const char *whitespace_parser(ast*, position*);
const char *lparen_parser(ast*, position*);
const char *rparen_parser(ast*, position*);
const char *lbracket_parser(ast*, position*);
const char *rbracket_parser(ast*, position*);
const char *caret_parser(ast*, position*);
const char *quote_parser(ast*, position*);
const char *bar_parser(ast*, position*);
const char *dash_parser(ast*, position*);
const char *backslash_parser(ast*, position*);
const char *newline_parser(ast*, position*);

#endif

