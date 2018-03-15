CC := gcc
LD := gcc
AR := ar
CFLAGS := -Iinclude -Llib -g -Wall -Wno-switch -fPIC
LDFLAGS := -Llib
BUILD_ROOT := $(shell pwd)
SOURCES := $(shell find src -name '*.c')
MODULE_SOURCES := $(shell find src/modules -name '*.c')
LIB_SOURCES := $(shell find src/libs -name '*.c')
MODULES := $(patsubst src/modules/%.c,lib/lib%.so,$(MODULE_SOURCES))
LIB_OBJS := $(patsubst src/libs/%.c,obj/libs/%.o,$(LIB_SOURCES))

all: $(MODULES) lib/libumbrella_parser.so

.SECONDARY:
bin lib notes obj obj/modules obj/libs:
	mkdir -p $@

lib/lib%.so: obj/modules/%.o | lib/libpraser.a
	$(CC) -shared --coverage $< -o $@ $|

lib/libast_callback_interpret_umbrella.so : obj/modules/ast_callback_interpret_umbrella.o obj/umbrella_interpreter.o obj/umbrella_ast_transform.o | lib/libpraser.a
	$(CC) -shared --coverage $^ -o $@ $|

lib/libpraser.a: $(LIB_OBJS) | lib
	$(AR) rcs $@ $^

obj/modules/%.o: src/modules/%.c | obj obj/modules notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

obj/libs/%.o: src/libs/%.c | obj obj/libs notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

obj/%.o: src/%.c | obj notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

bin/parser_runner: obj/parser_runner.o bin lib/libstub_parser.so lib/libast_callback_stub.so lib/libpraser.a
	$(LD) $(LDFLAGS) --coverage $< -o $@ -Wl,-rpath=$(BUILD_ROOT)/lib -lstub_parser -last_callback_stub -lpraser

src/modules/generated_parser.c: src/parser.pra lib/libparser_parser.so lib/libast_callback_compile.so bin/parser_runner
	./parser_runner.sh parser compile $< $@

src/modules/umbrella_parser.c: src/umbrella.pra lib/libgenerated_parser.so lib/libast_callback_compile.so bin/parser_runner
	./parser_runner.sh generated compile $< $@

.PHONY: test
test: all
	./parser_runner.sh generated interpret src/parser.pra src/umbrella.pra

.PHONY: coverage
coverage: test
	lcov -t "result" -o cov.info -c -d notes
	genhtml -o cov cov.info

clean:
	rm -rf bin lib notes obj cov cov.info src/modules/generated_parser.c src/modules/umbrella_parser.c

