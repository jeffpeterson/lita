CC = clang
CFLAGS := -g -Werror -Wall -Wno-error=unused-variable -Wno-error=unused-function -Isrc

TARGET := .bin/sol
TEST := $(TARGET)-test

SOL_SRC := $(shell find src/sol/lib -name "*.sol")
SOL_C   := $(SOL_SRC:.sol=.sol.c)
SOL_O   := $(SOL_C:src/%.c=_build/%.o)
SOURCES := $(shell find src -name "*.c")
HEADERS := $(shell find src -name "*.h")

TARG_C := $(filter-out %_test.c,$(SOURCES))

OBJECTS := $(patsubst src/%.c,_build/%.o, $(SOURCES))
TARG_O  := $(filter-out %_test.o,$(OBJECTS))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean test db db/test lib
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c

default: $(TARGET)
all: default $(TEST) lib
db/test: $(TEST)
	@lldb $(TEST)

db/%: $(TARGET)
	@lldb sol examples/$*.sol

%: examples/%.sol $(TARGET)
	@$(TARGET) $<

lib: $(SOL_O)
test: $(TEST) assertions
	@$(TEST)

$(TARGET): $(TARG_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

_build/%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.sol.c: %.sol bin/sol
	bin/sol -c $<

clean:
	-rm -f $(TARGET) $(TEST) $(OBJECTS)
