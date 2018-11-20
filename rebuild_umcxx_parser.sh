#!/usr/bin/env bash
gcc -std=c99 -Wall -c -o obj/libs/praser/ast_compiler.o src/libs/praser/ast_compiler.c -Iinclude -fPIC
ar rcs lib/libpraser.a obj/libs/praser/*.o
gcc -o lib/libast_callback_compile.so obj/modules/ast_callback_compile.o -Llib -lpraser --coverage -shared -fPIC
bin/parser_runner parser compile src/parsers/umbrella.pra src/modules/umbrella_parser.gen.cxx

