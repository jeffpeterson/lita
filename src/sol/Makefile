TARGET := .bin/sol
TEST := $(TARGET)-test
NAME := $(notdir $(CURDIR))
OUT := $(BUILD)/$(NAME)

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

clean:
	-rm -f $(TARGET) $(TEST)
