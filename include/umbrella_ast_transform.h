#ifndef __UMBRELLA_AST_TRANSFORM_H__
#define __UMBRELLA_AST_TRANSFORM_H__

#include <stddef.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"

//note that none of these functions should actually be exported so I might want to hide them using variant builds, objcopy, or ld version scripts
void transform_ast(block *out, ast *r);
void make_empty_block(block *out);
void transform_statements(block *out, ast *r);
void transform_expr(expression *out, ast *r, int has_comma, int in_operator);
void transform_expr_prefix(expression *out, ast *r);
void transform_expr_postfix(expression *out, ast *r);
void transform_expr0(expression *out, ast *r);
void transform_atom(expression *out, ast *r);
void transform_literal(value *out, ast *r);
void transform_compound_literal(value *out, ast *r);
intptr_t transform_digit_groups_base(ast *r, size_t base);
void transform_int_literal(value *out, ast *r);
void transform_float_literal(value *out, ast *r);
void transform_complex_literal(value *out, ast *r);
void transform_string_literal(value *out, ast *r);
void transform_char_literal(value *out, ast *r);
void make_empty_tuple(value *out);

#endif

