#ifndef __PARSER_GENERATOR_H__
#define __PARSER_GENERATOR_H__

#include "parser.h"

const char const
*start_tag = "start",
*rule_tag = "rule",
*name_tag = "name",
*assign_tag = "assign",
*pattern_tag = "pattern",
*group_tag = "group",
*option_tag = "option",
*atom_tag = "atom",
*quantifier_tag = "quantifier",
*parens_tag = "parens",
*invset_tag = "invset",
*charset_tag = "charset",
*setrange_tag = "setrange",
*setchar_tag = "setchar",
*string_tag = "string";

const char *start_parser(ast*, position*) __attribute__((warn_unused_result));
const char *rule_parser(ast*, position*) __attribute__((warn_unused_result));
const char *name_parser(ast*, position*) __attribute__((warn_unused_result));
const char *assign_parser(ast*, position*) __attribute__((warn_unused_result));
const char *pattern_parser(ast*, position*) __attribute__((warn_unused_result));
const char *group_parser(ast*, position*) __attribute__((warn_unused_result));
const char *option_parser(ast*, position*) __attribute__((warn_unused_result));
const char *atom_parser(ast*, position*) __attribute__((warn_unused_result));
const char *quantifier_parser(ast*, position*) __attribute__((warn_unused_result));
const char *parens_parser(ast*, position*) __attribute__((warn_unused_result));
const char *invset_parser(ast*, position*) __attribute__((warn_unused_result));
const char *charset_parser(ast*, position*) __attribute__((warn_unused_result));
const char *setrange_parser(ast*, position*) __attribute__((warn_unused_result));
const char *setchar_parser(ast*, position*) __attribute__((warn_unused_result));
const char *string_parser(ast*, position*) __attribute__((warn_unused_result));
const char *esc_seq_parser(ast*, position*) __attribute__((warn_unused_result));
const char *hex_parser(ast*, position*) __attribute__((warn_unused_result));
const char *dec_parser(ast*, position*) __attribute__((warn_unused_result));
const char *whitespace_parser(ast*, position*);
const char *lparen_parser(ast*, position*) __attribute__((warn_unused_result));
const char *rparen_parser(ast*, position*) __attribute__((warn_unused_result));
const char *lbracket_parser(ast*, position*) __attribute__((warn_unused_result));
const char *rbracket_parser(ast*, position*) __attribute__((warn_unused_result));
const char *caret_parser(ast*, position*) __attribute__((warn_unused_result));
const char *quote_parser(ast*, position*) __attribute__((warn_unused_result));
const char *bar_parser(ast*, position*) __attribute__((warn_unused_result));
const char *dash_parser(ast*, position*) __attribute__((warn_unused_result));
const char *backslash_parser(ast*, position*) __attribute__((warn_unused_result));
const char *newline_parser(ast*, position*) __attribute__((warn_unused_result));

#endif

