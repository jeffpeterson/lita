CC = clang
LITA_FLAGS := # -t
WARN_ERRORS := -Werror -Wno-error=unused-variable -Wno-error=unused-function
CFLAGS := -g -Isrc -Wall $(WARN_ERRORS)

TARGET := .bin/lita
TEST := $(TARGET)-test
LITA_LIB := _build/lita.so

SOURCES := $(shell find src -name "*.c")
HEADERS := $(shell find src -name "*.h")
OBJECTS := $(patsubst src/%.c,_build/%.o, $(SOURCES))

LITA_SRC := $(shell find src/lita -name "*.lita" -not -path "*/ideas/*")
LITA_C   := $(LITA_SRC:.lita=.lita.c)
LITA_O   := $(LITA_C:src/%.c=_build/%.o)
NON_LITA_C := $(filter-out %.lita.c,$(SOURCE))
# LITA_EXISTING_C := $(shell find src/lita/lib -name "*.c")

TARGET_C := $(filter-out %_test.c,$(SOURCES))

TARGET_O  := $(TARGET_C:src/%.c=_build/%.o)
# TARGET_O  := $(filter-out %.lita.o,$(TARGET_O))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean test db db/test lib
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c

default: test assertions

# zig not working yet
zig: $(TARGET).zig.wasm

# WASM
js: $(TARGET).js
html: $(TARGET).html

lita: $(TARGET)
all: default $(TEST) lib
db/test: $(TEST)
	@lldb $(TEST)

db/%: $(TARGET)
	@lldb lita examples/$*.lita

%: examples/%.lita $(TARGET)
	@$(TARGET) $(LITA_FLAGS) $<

lib: $(LITA_LIB)
test: $(TEST)
	@$(TEST) $(LITA_FLAGS)

$(TARGET).wasm $(TARGET).js $(TARGET).html: $(TARGET_O:%.o=%.wasm.o)
	@mkdir -p $(dir $@)
	emcc -lc $(CFLAGS) -o $(TARGET).html $^

$(TARGET).zig.wasm: $(filter-out src/flecs/%,$(TARGET_C))
	@mkdir -p $(dir $@)
	zig cc $(CFLAGS) --shared -D_WASI_EMULATED_PROCESS_CLOCKS -lwasi-emulated-process-clocks --target=wasm32-wasi $(TARGET).zig.wasm $^

# $(TARGET).wasm $(TARGET).js: $(TARGET_C)
# 	@mkdir -p $(dir $@)
# 	emcc $(CFLAGS) -o $(TARGET).js $^

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

_build/%.wasm.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	emcc $(CFLAGS) -c -o $@ $<

# This recipe creates the circular dependency between the lita library and the
# lita compiler.
%.lita.c: %.lita $(NON_LITA_C)
	$(TARGET) -c $<

serve: html
	python -m http.server 8000 --directory .bin

clean:
	-rm -f $(TARGET) $(TEST) $(shell find _build -name "*.o")
