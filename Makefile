CC := gcc
LD := gcc
AR := ar
CFLAGS := -Iinclude -Llib -g -Wall -Wno-switch -fPIC
LDFLAGS := -Llib
BUILD_ROOT := $(shell pwd)
SOURCES := $(shell find src -name '*.c')
MODULE_SOURCES := $(shell find src/modules -name '*.c')
LIB_SOURCES := $(shell find src/libs -name '*.c')
TEST_SOURCES := $(shell find src/test -name '*.c')
MODULES := $(patsubst src/modules/%.c,lib/lib%.so,$(MODULE_SOURCES))
LIB_OBJS := $(patsubst src/libs/%.c,obj/libs/%.o,$(LIB_SOURCES))
TEST_OBJS := $(patsubst src/test/%.c,obj/test/%.o,$(TEST_SOURCES))
TEST_BINS := $(patsubst src/test/%.c,bin/test/%,$(TEST_SOURCES))

all: $(MODULES) lib/libumbrella_parser.so

.SECONDARY:
bin bin/test lib notes cov obj obj/modules obj/libs obj/test:
	mkdir -p $@

lib/lib%.so: obj/modules/%.o | lib/libpraser.a
	$(CC) -shared --coverage $< -o $@ $|

lib/libast_callback_interpret_umbrella.so : obj/modules/ast_callback_interpret_umbrella.o obj/umbrella_interpreter.o obj/umbrella_ast_transform.o | lib/libpraser.a
	$(CC) -shared --coverage $^ -o $@ $|

lib/libpraser.a: $(LIB_OBJS) | lib
	$(AR) rcs $@ $^

obj/modules/%.o: src/modules/%.c | obj/modules notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

obj/libs/%.o: src/libs/%.c | obj/libs notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

obj/test/%.o: src/test/%.c | obj/test notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

obj/%.o: src/%.c | obj notes
	$(CC) $(CFLAGS) --coverage -c $^ -o notes/$*.o
	mv notes/$*.o $@

bin/test/%: obj/test/%.o | bin/test
	$(LD) $(LDFLAGS) --coverage $< -o $@ -Wl,-rpath=$(BUILD_ROOT)/lib -lpraser -ldl

bin/parser_runner: obj/parser_runner.o lib/libpraser.a bin
	$(LD) $(LDFLAGS) --coverage $< -o $@ -Wl,-rpath=$(BUILD_ROOT)/lib -lpraser -ldl

src/modules/generated_parser.c: src/parser.pra lib/libparser_parser.so lib/libast_callback_compile.so bin/parser_runner
	bin/parser_runner parser compile $< $@

src/modules/umbrella_parser.c: src/umbrella.pra lib/libgenerated_parser.so lib/libast_callback_compile.so bin/parser_runner
	bin/parser_runner generated compile $< $@

.PHONY: test
test: all $(TEST_BINS)
	./test.sh

.PHONY: coverage
coverage: test | cov
	gcovr --html-details -e src/test/.\*\.c -o cov/index.html notes

clean:
	rm -rf bin lib notes obj cov cov.info src/modules/generated_parser.c src/modules/umbrella_parser.c

