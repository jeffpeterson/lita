CC = clang
FLAGS := # -t
SHELL := /bin/bash
WARN_ERRORS := -Werror -Wno-error=unused-variable -Wno-unused-function -Wno-unused-command-line-argument
CFLAGS := -g -Isrc -I/opt/homebrew/include -L/opt/homebrew/lib -lpcre2-8 -lreadline -Wall $(WARN_ERRORS)

TARGET := .bin/lita
DEV := .bin/lita-dev
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

default: test assertions $(TARGET)

# zig not working yet
zig: $(TARGET).zig.wasm

# WASM
js: $(TARGET).js
html: $(TARGET).html

lita: $(TARGET)
all: default $(TEST) lib
db: db/assertions
db/test: $(TEST)
	@lldb -- $(TEST)

db/%: $(DEV)
	@lldb -- $(DEV) $(FLAGS) examples/$*.lita

%: examples/%.lita $(DEV)
	@$(DEV) $(FLAGS) $<
	@git diff --quiet && git notes --ref=$@ add -fm OK 2>/dev/null || true

lib: $(LITA_LIB)
test: $(TEST)
	$(TEST) $(FLAGS)
	@git diff --quiet && git notes --ref=test add -fm OK 2>/dev/null || true

$(TARGET).wasm $(TARGET).js $(TARGET).html: $(TARGET_O:%.o=%.wasm.o)
	@mkdir -p $(dir $@)
	emcc -lc $(CFLAGS) -o $(TARGET).html $^

$(TARGET).zig.wasm: $(filter-out src/flecs/%,$(TARGET_C))
	@mkdir -p $(dir $@)
	zig cc $(CFLAGS) --shared -D_WASI_EMULATED_PROCESS_CLOCKS -lwasi-emulated-process-clocks --target=wasm32-wasi $(TARGET).zig.wasm $^

# $(TARGET).wasm $(TARGET).js: $(TARGET_C)
# 	@mkdir -p $(dir $@)
# 	emcc $(CFLAGS) -o $(TARGET).js $^

$(DEV): $(TARGET_O) | test
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET): $(DEV) | assertions
	-cp $@ $@-$(shell date -r $@ "+%Y-%m-%d-%H:%M:%S")
	cp $< $@
	chmod +x $@

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(LITA_LIB): $(LITA_O) $(TARGET_O) | test
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

repl: $(DEV)
	@$(DEV) -r $(FLAGS)

db/repl: $(DEV)
	@lldb -- $(DEV) -r $(FLAGS)

serve: html
	python -m http.server 8000 --directory .bin

clean:
	-rm -f $(DEV) $(TEST) $(shell find _build -name "*.o")

flecs:
	curl https://raw.githubusercontent.com/SanderMertens/flecs/v4.0.1/flecs.c > src/lita/flecs.c
	curl https://raw.githubusercontent.com/SanderMertens/flecs/v4.0.1/flecs.h > src/lita/flecs.h

.PHONY: default all clean test db db/test lib
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c
