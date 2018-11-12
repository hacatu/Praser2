#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "betest.h"

void *dlsym_or_exit(void *lib_handle, const char *name){
	void *ret = dlsym(lib_handle, name);
	if(!ret){
		fprintf(stderr, "parser .so did not contain \"%s\"\n", name);
		dlclose(lib_handle);
		exit(1);
	}
	return ret;
}

