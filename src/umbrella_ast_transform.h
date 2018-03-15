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
void um_transform_block(block *out, ast *r);//
inline void transform_value_comp_statement(value *out, ast *r);//
inline void transform_block_comp_statement(block *out, ast *r);//
inline expression *um_transform_comp_statement(ast *r);//
inline size_t fold_prec(ast *r);//
inline size_t fold_prec_rec(ast ***cur, size_t len, int prec);//
inline size_t count_prefix(ast *r);//
inline size_t count_postfix(ast *r);//
inline expression *transform_expr_node(expression *out, ast *o, expression *buf);//
inline expression *transform_prefix_node(expression *out, ast *o, expression *buf);//
inline expression *transform_postfix_node(expression *out, ast *o, expression *buf);//
void delete_folded_expr_ast(ast *r);//TODO: NYI NEEDS TO BE WRITTEN
void um_transform_expr(expression *out, ast *r);//
void insert_cstmt(expression *out, ast *r);//
void transform_literal(value *out, ast *r);//
void transform_compound_literal(value *out, ast *r);//
intptr_t transform_digit_groups_base(ast *r, size_t base);//
void transform_int_literal(value *out, ast *r);//
void transform_float_literal(value *out, ast *r);//
void transform_complex_literal(value *out, ast *r);
void transform_string_literal(value *out, ast *r);
void transform_char_literal(value *out, ast *r);
void um_transform_atom(expression *out, ast *r);//

#endif

