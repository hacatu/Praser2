#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

const char *start_parser(ast *t, position *p){
	fprintf(stderr, "\e[1;31mERROR: start_parser not bound.\e[0m\n");
	exit(1);
	return "start_parser";
}

