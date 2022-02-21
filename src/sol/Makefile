CC = clang
CFLAGS := -g -Werror -Wall -I..

TARGET := .bin/sol
TEST := $(TARGET)-test

SOL_SRC := $(shell find ./lib -name "*.sol")
SOL_C   := $(SOL_SRC:.sol=.sol.c)
SOURCES := $(shell find . -name "*.c")
HEADERS := $(shell find . -name "*.h")
OBJECTS := $(patsubst ./%.c,_build/%.o, $(SOURCES))
TARG_O  := $(filter-out %_test.o,$(OBJECTS))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean core
.PRECIOUS: $(TARGET)
.SUFFIXES: # disable crazy built-in rules that append .c

default: $(TARGET) $(TEST) core
all: default
core: $(SOL_C)

$(TARGET): $(TARG_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

_build/%.o: ./%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.sol.c: %.sol
	sol -c $<

clean:
	-rm -f $(TARGET) $(TEST) $(OBJECTS)
