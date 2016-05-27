#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int ast_callback(ast *r, int argc, char **argv){
	fprintf(stderr, "\e[1;31mERROR: ast_callback not bound.\e[0m\n");
	exit(1);
	return 1;
}

