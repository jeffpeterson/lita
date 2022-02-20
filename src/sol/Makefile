TARGET := .bin/sol
TEST := $(TARGET)-test
NAME := $(notdir $(CURDIR))
OUT := $(BUILD)/$(NAME)

SOL_SRC := $(shell find ./lib -name "*.sol")
SOL_C   := $(SOL_SRC:.sol=.sol.c)
SOURCES := $(shell find . -name "*.c")
HEADERS := $(shell find . -name "*.h")
OBJECTS := $(patsubst ./%.c,$(OUT)/%.o, $(SOURCES))
TARG_O  := $(filter-out %_test.o,$(OBJECTS))
TEST_O  := $(filter-out %/main.o,$(OBJECTS))

.PHONY: default all clean
.PRECIOUS: $(TARGET)

default: $(TARGET) $(TEST)
all: default

$(TARGET): $(TARG_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

$(TEST): $(TEST_O)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

%.sol.c: %.sol
	sol -c $<

clean:
	-rm -f $(TARGET) $(TEST)
