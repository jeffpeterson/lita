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
# LITA_EXISTING_C := $(shell find src/lita/lib -name "*.c")

TARGET_C := $(filter-out %_test.c,$(SOURCES))
NON_LITA_C := $(filter-out %.lita.c,$(TARGET_C))

TARGET_O  := $(TARGET_C:src/%.c=_build/%.o)
# TARGET_O  := $(filter-out %.lita.o,$(TARGET_O))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))
TARGET_GIT := $(TARGET)@$(shell git rev-parse --short HEAD)

PRUNABLES := $(shell find .bin -name 'lita-*' -mtime +14 | tail -n +30)

default: $(TARGET_GIT) test assertions $(TARGET) prune

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
	$(DEV) $(FLAGS) $<
	@git diff --quiet && git notes --ref=$@ add -fm OK 2>/dev/null || true

lib: $(LITA_LIB)
test: $(TEST)
	$(TEST) $(FLAGS)
	@git diff --quiet && git notes --ref=test add -fm OK 2>/dev/null || true

$(TARGET).wasm $(TARGET).js $(TARGET).html: $(TARGET_O:%.o=%.wasm.o)
	@mkdir -p $(dir $@)
	$(eval CFLAGS := -g -DNO_READLINE -DENABLE_REGEX=0 -Isrc -I/opt/homebrew/include -L/opt/homebrew/lib -Wall $(WARN_ERRORS))
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

$(TARGET)@%: $(DEV)
	@git diff --exit-code --quiet && cp $< $@ || true

$(TARGET): $(DEV) | assertions
	-cp $@ $@-$(shell date -r $@ "+%Y-%m-%d-%H_%M_%S")
	cp $< $@

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
%.lita.c: %.lita $(NON_LITA_C) $(HEADERS)
	$(TARGET) -c $<

repl: $(DEV)
	@$(DEV) -r $(FLAGS)

db/repl: $(DEV)
	@lldb -- $(DEV) -r $(FLAGS)

serve: html
	python -m http.server 8000 --directory .bin

clean:
	-rm -f $(DEV) $(TEST) $(shell find _build -name "*.o")

prune: tmp/pruned

# TODO: this doesn't work because the prunables are older than the tmp/pruned file
tmp/pruned: | $(PRUNABLES)
	@echo "Before pruning: $$(du -sh .bin)"
	@echo $^ | tee /dev/tty | xargs rm
	@echo "After pruning: $$(du -sh .bin)"
	@touch $@

flecs:
	curl https://raw.githubusercontent.com/SanderMertens/flecs/v4.0.1/flecs.c > src/lita/flecs.c
	curl https://raw.githubusercontent.com/SanderMertens/flecs/v4.0.1/flecs.h > src/lita/flecs.h

pcg:
	curl https://raw.githubusercontent.com/imneme/pcg-c-basic/master/pcg_basic.c > src/lita/pcg_basic.c
	curl https://raw.githubusercontent.com/imneme/pcg-c-basic/master/pcg_basic.h > src/lita/pcg_basic.h

xxhash:
	curl https://raw.githubusercontent.com/Cyan4973/xxHash/refs/tags/v0.8.2/xxhash.h > src/lita/xxhash.h
	curl https://raw.githubusercontent.com/Cyan4973/xxHash/refs/tags/v0.8.2/xxhash.c > src/lita/xxhash.c

.PHONY: default all clean test db db/test lib prune
.PRECIOUS: $(TARGET) %.c %.o
.SUFFIXES: # disable crazy built-in rules that append .c
