#ifndef __PARSER_PARSER_H__
#define __PARSER_PARSER_H__

#include "parser.h"

extern const char
*const start_tag,
*const rule_tag,
*const name_tag,
*const assign_tag,
*const pattern_tag,
*const group_tag,
*const option_tag,
*const atom_tag,
*const quantifier_tag,
*const parens_tag,
*const invset_tag,
*const charset_tag,
*const setrange_tag,
*const setchar_tag,
*const string_tag;

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

