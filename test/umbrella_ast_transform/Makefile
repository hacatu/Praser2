test: test.o ../../obj/umbrella_ast_transform.o ../../obj/umbrella_interpreter.o ../../lib/libpraser.a ../../lib/libumbrella_parser.so
	gcc -Llib -fPIC --coverage -o $@ $^

test.o: test.c
	gcc -c -I../../include -I../.. -g -Wall -Wno-switch -fPIC -o $@ $^

clean:
	rm test.o test

