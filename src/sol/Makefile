CC = clang
CFLAGS := -g -Werror -Wall -Wno-error=unused-variable -Wno-error=unused-function -I..

TARGET := .bin/sol
TEST := $(TARGET)-test

SOL_SRC := $(shell find ./lib -name "*.sol")
SOL_C   := $(SOL_SRC:.sol=.sol.c)
SOL_O   := $(SOL_C:%.c=_build/%.o)
SOURCES := $(shell find . -name "*.c")
HEADERS := $(shell find . -name "*.h")
OBJECTS := $(patsubst ./%.c,_build/%.o, $(SOURCES))
TARG_O  := $(filter-out %_test.o,$(OBJECTS))
TARG_O  := $(filter-out %.sol.o,$(TARG_O))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean test db
.PRECIOUS: $(TARGET)
.SUFFIXES: # disable crazy built-in rules that append .c

default: $(TARGET)
all: default $(TEST) lib
db/%: $(TARGET)
	@lldb sol examples/$*.sol

%: examples/%.sol $(TARGET)
	@$(TARGET) $<

lib: $(SOL_O)
test: $(TEST)
	@$(TEST)

$(TARGET): $(TARG_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(SOL_O)

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

_build/%.o: ./%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.sol.c: %.sol $(TARGET)
	sol -c $<

clean:
	-rm -f $(TARGET) $(TEST) $(OBJECTS)
