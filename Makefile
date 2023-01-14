CC = clang
CFLAGS := -g -Werror -Wall -Wno-error=unused-variable -Wno-error=unused-function -Isrc

TARGET := .bin/sol
TEST := $(TARGET)-test
SOL_LIB := _build/sol.so

SOURCES := $(shell find src -name "*.c")
HEADERS := $(shell find src -name "*.h")
OBJECTS := $(patsubst src/%.c,_build/%.o, $(SOURCES))

SOL_SRC := $(shell find src/sol/lib -name "*.sol")
SOL_C   := $(SOL_SRC:.sol=.sol.c)
SOL_O   := $(SOL_C:src/%.c=_build/%.o)
# SOL_EXISTING_C := $(shell find src/sol/lib -name "*.c")

TARGET_C := $(filter-out %_test.c,$(SOURCES))

TARGET_O  := $(filter-out %_test.o,$(OBJECTS))
# TARGET_O  := $(filter-out %.sol.o,$(TARGET_O))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean test db db/test lib
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c

default: test
sol: $(TARGET)
all: default $(TEST) lib
db/test: $(TEST)
	@lldb $(TEST)

db/%: $(TARGET)
	@lldb sol examples/$*.sol

%: examples/%.sol $(TARGET)
	@$(TARGET) $<

lib: $(SOL_LIB)
test: $(TEST) assertions
	@$(TEST)

$(TARGET): $(TARGET_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(SOL_LIB): $(SOL_O) $(TARGET_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -shared -o $@ $^

_build/%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# This recipe creates the circular dependency between the sol library and the
# sol compiler.
%.sol.c: %.sol
	$(TARGET) -c $<

clean:
	-rm -f $(TARGET) $(TEST) $(OBJECTS)
