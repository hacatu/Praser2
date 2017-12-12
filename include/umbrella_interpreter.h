#ifndef __UMBRELLA_INTERPRETER_H__
#define __UMBRELLA_INTERPRETER_H__

#include <stddef.h>
#include "parser.h"
#include "expression.h"

void um_transform_ast(expression *out, ast *r);
void um_eval(value *out, expression *expr, frame *scope, value *cntr);

#endif

