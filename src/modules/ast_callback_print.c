/*
 * ast_callback_print.c
 * Simplest ast callback for parser_runner.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int ast_callback(ast *t, int argc, char **argv){
	print_ast(t);
	return 0;
}

