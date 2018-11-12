CC := gcc
LD := gcc
AR := ar
CFLAGS := @flags/base.cflags
LDFLAGS := -Llib
BUILD_ROOT := $(shell pwd)



PARSER_DESCS := $(shell find src/parsers -name '*.pra')


LIB_SOURCES := $(shell find src/libs -name '*.c')
MODULE_SOURCES := $(shell find src/modules -name '*.c' ! -name '*.gen.c')
TEST_SOURCES := $(shell find src/test -name '*.c')
BINARY_SOURCES := $(shell find src/bin -name '*.c')

GEN_SOURCES := $(patsubst src/parsers/%.pra,src/modules/%_parser.gen.c,$(PARSER_DESCS))

DEBUG_CFLAGS := @flags/debug.cflags
RELEASE_CFLAGS := @flags/release.cflags

RELEASE_LDFLAGS := -flto -fuse-ld=gold

LIB_CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS) --coverage
MODULE_CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS) --coverage
TEST_CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS)
BINARY_CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS)
GEN_CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS)


LIB_OBJS := $(patsubst src/libs/%.c,obj/libs/%.o,$(LIB_SOURCES))
MODULE_OBJS := $(patsubst src/modules/%.c,obj/modules/%.o,$(MODULE_SOURCES))
TEST_OBJS := $(patsubst src/test/%.c,obj/test/%.o,$(TEST_SOURCES))
BINARY_OBJS := $(patsubst src/bin/%.c,obj/bin/%.o,$(BINARY_SOURCES))

GEN_OBJS := $(patsubst src/parsers/%.pra,obj/modules/%_parser.gen.o,$(PARSER_DESCS))

MODULE_LDFLAGS := $(LDFLAGS) --coverage -shared -lpraser -lhac -lumbrella
TEST_LDFLAGS := $(LDFLAGS) --coverage -Wl,-rpath=$(BUILD_ROOT)/lib -lpraser -lumbrella -lhac -ldl
BINARY_LDFLAGS := $(LDFLAGS) --coverage -Wl,-rpath=$(BUILD_ROOT)/lib -lpraser -lumbrella -lhac -ldl
GEN_LDFLAGS := $(LDFLAGS) --coverage -shared -lpraser


SIMPLE_LIB_ARCS := $(patsubst src/libs/%.c,lib/lib%.a,$(shell find src/libs -maxdepth 1 -name '*.c'))
SIMPLE_MODULE_SOS := $(patsubst src/modules/%.c,lib/lib%.so,$(shell find src/modules -maxdepth 1 -name '*.c' ! -name '*.gen.c'))
SIMPLE_TEST_BINS := $(patsubst src/test/%.c,bin/test/%,$(shell find src/test -maxdepth 1 -name '*.c'))
SIMPLE_BINARIES := $(patsubst src/bin/%.c,bin/%,$(shell find src/bin -maxdepth 1 -name '*.c'))

COMPOUND_LIB_ARCS := $(patsubst src/libs/%,lib/lib%.a,$(shell find src/libs -mindepth 1 -maxdepth 1 -type d))
COMPOUND_MODULE_SOS := $(patsubst src/modules/%,lib/lib%.so,$(shell find src/modules -mindepth 1 -maxdepth 1 -type d))
COMPOUND_TEST_BINS := $(patsubst src/test%,bin/test/%,$(shell find src/modules -mindepth 1 -maxdepth 1 -type d))
COMPOUND_BINARIES := $(patsubst src/bin/%,bin/%,$(shell find src/modules -mindepth 1 -maxdepth 1 -type d))

GEN_SOS := $(patsubst src/parsers/%.pra,lib/lib%_parser.so,$(PARSER_DESCS))



-include $(patsubst src/%.c,obj/%.d,$(LIB_SOURCES) $(MODULE_SOURCES) $(TEST_SOURCES) $(BINARY_SOURCES))

.DEFAULT_GOAL := all

all: $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS) $(SIMPLE_MODULE_SOS) $(COMPOUND_MODULE_SOS) $(GEN_SOS) $(SIMPLE_BINARIES) $(COMPOUND_BINARIES)

.SECONDARY:
bin bin/test lib notes notes/modules notes/libs notes/test notes/bin cov obj obj/modules obj/libs obj/test obj/bin log:
	@mkdir -p $@

src/modules/parser_parser.gen.c: src/parsers/parser.pra | bin/parser_runner lib/libbootstrap_parser.so lib/libast_callback_compile.so
	bin/parser_runner bootstrap compile $^ $@

src/modules/%_parser.gen.c: src/parsers/%.pra | bin/parser_runner lib/libparser_parser.so lib/libast_callback_compile.so
	bin/parser_runner parser compile $^ $@

obj/libs/%.o: src/libs/%.c
	@mkdir -p $(@D) notes/libs/$(*D)
	$(CC) $(LIB_CFLAGS) -c -o notes/libs/$*.o $^
	@mv notes/libs/$*.o $@
	@printf "%%s" "$(@D)/" > obj/libs/$*.d
	@$(CC) -Iinclude -std=c99 -MM $^ >> obj/libs/$*.d

obj/modules/%_parser.gen.o: src/modules/%_parser.gen.c | include/parser.h obj/modules notes/modules
	$(CC) $(GEN_CFLAGS) -c $^ -o notes/modules/$*.o
	@mv notes/modules/$*.o $@

obj/modules/%.o: src/modules/%.c
	@mkdir -p $(@D) notes/modules/$(*D)
	$(CC) $(MODULE_CFLAGS) -c $^ -o notes/modules/$*.o
	@mv notes/modules/$*.o $@
	@printf "%%s" "$(@D)/" > obj/modules/$*.d
	@$(CC) -Iinclude -std=c99 -MM $^ >> obj/modules/$*.d

obj/test/%.o: src/test/%.c | obj/test notes/test
	@mkdir -p $(@D) notes/test/$(*D)
	$(CC) $(TEST_CFLAGS) -c $^ -o notes/test/$*.o
	@mv notes/test/$*.o $@
	@printf "%%s" "$(@D)/" > obj/test/$*.d
	@$(CC) -Iinclude -std=c99 -MM $^ >> obj/test/$*.d

obj/bin/%.o: src/bin/%.c | obj/bin notes/bin
	@mkdir -p $(@D) notes/bin/$(*D)
	$(CC) $(BINARY_CFLAGS) -c $^ -o notes/bin/$*.o
	@mv notes/bin/$*.o $@
	@printf "%%s" "$(@D)/" > obj/bin/$*.d
	@$(CC) -Iinclude -std=c99 -MM $^ >> obj/bin/$*.d

$(SIMPLE_LIB_ARCS): lib/lib%.a: obj/libs/%.o | lib
	$(AR) rcs $@ $^

$(COMPOUND_LIB_ARCS): lib/lib%.a: obj/libs/%.compound | lib
	$(AR) rcs $@ $(filter obj/libs/$*/%.o,$(LIB_OBJS))

$(SIMPLE_MODULE_SOS): lib/lib%.so: obj/modules/%.o | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS)
	$(LD) -o $@ $^ $(MODULE_LDFLAGS)

$(GEN_SOS): lib/lib%.so: obj/modules/%.gen.o | lib/libpraser.a
	$(LD) -o $@ $^ $(GEN_LDFLAGS)
	
$(COMPOUND_MODULE_SOS): lib/lib%.so: obj/modules/%.compound | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS)
	$(LD) -o $@ $(filter obj/modules/$*/%.o,$(MODULE_OBJS)) $(MODULE_LDFLAGS)

$(SIMPLE_TEST_BINS): bin/test/%: obj/test/%.o | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS) bin/test
	$(LD) -o $@ $^ $(TEST_LDFLAGS)

$(COMPOUND_TEST_BINS): bin/test/%: obj/test/%.compound | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS) bin/test
	$(LD) -o $@ $(filter obj/test/$*/%.o,$(TEST_OBJS)) $(TEST_LDFLAGS)

$(SIMPLE_BINARIES): bin/%: obj/bin/%.o | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS) bin
	$(LD) -o $@ $^ $(BINARY_LDFLAGS)

$(COMPOUND_BINARIES): bin/%: obj/bin/%.compound | $(SIMPLE_LIB_ARCS) $(COMPOUND_LIB_ARCS) bin
	$(LD) -o $@ $(filter obj/bin/$*/%.o,$(BINARY_OBJS)) $(BINARY_LDFLAGS)

obj/%.compound:
	@touch $@

define make-compound
obj/$(1)/$(2).compound: $(filter obj/$(1)/$(2)/%.o,$(3))
endef

$(foreach c,$(patsubst lib/lib%.a,%,$(COMPOUND_LIB_ARCS)),$(eval $(call make-compound,libs,$c,$(LIB_OBJS))))
$(foreach c,$(patsubst lib/lib%.so,%,$(COMPOUND_MODULE_SOS)),$(eval $(call make-compound,modules,$c,$(MODULE_OBJS))))
$(foreach c,$(patsubst bin/test/%,%,$(COMPOUND_TEST_BINS)),$(eval $(call make-compound,test,$c,$(TEST_OBJS))))
$(foreach c,$(patsubst bin/%,%,$(COMPOUND_BINARIES)),$(eval $(call make-compound,bin,$c,$(BINARY_OBJS))))

.PHONY: test
test: all $(SIMPLE_TEST_BINS) $(COMPOUND_TEST_BINS) log
	#-./test.sh &> log/test`date -u +%s`.log
	./test.sh

.PHONY: coverage
coverage: test | cov
	gcovr --html-details -e src/test/.\*\.c -o cov/index.html notes

clean:
	-rm -rf bin lib notes obj cov log
	-find src/ "(" -name '*.gen.*' -or -name '*.d' ")" -delete

debug_makefile:
	@echo $(SIMPLE_MODULE_SOS)
