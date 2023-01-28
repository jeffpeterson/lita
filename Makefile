CC = clang
CFLAGS := -g -Werror -Wall -Wno-error=unused-variable -Wno-error=unused-function -Isrc

TARGET := .bin/lita
TEST := $(TARGET)-test
LITA_LIB := _build/lita.so

SOURCES := $(shell find src -name "*.c")
HEADERS := $(shell find src -name "*.h")
OBJECTS := $(patsubst src/%.c,_build/%.o, $(SOURCES))

LITA_SRC := $(shell find src/lita/lib -name "*.lita")
LITA_C   := $(LITA_SRC:.lita=.lita.c)
LITA_O   := $(LITA_C:src/%.c=_build/%.o)
# LITA_EXISTING_C := $(shell find src/lita/lib -name "*.c")

TARGET_C := $(filter-out %_test.c,$(SOURCES))

TARGET_O  := $(filter-out %_test.o,$(OBJECTS))
# TARGET_O  := $(filter-out %.lita.o,$(TARGET_O))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean test db db/test lib
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c

default: test
lita: $(TARGET)
all: default $(TEST) lib
db/test: $(TEST)
	@lldb $(TEST)

db/%: $(TARGET)
	@lldb lita examples/$*.lita

%: examples/%.lita $(TARGET)
	@$(TARGET) $<

lib: $(LITA_LIB)
test: $(TEST) assertions
	@$(TEST)

$(TARGET): $(TARGET_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(LITA_LIB): $(LITA_O) $(TARGET_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -shared -o $@ $^

_build/%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# This recipe creates the circular dependency between the lita library and the
# lita compiler.
%.lita.c: %.lita
	$(TARGET) -c $<

clean:
	-rm -f $(TARGET) $(TEST) $(OBJECTS)
