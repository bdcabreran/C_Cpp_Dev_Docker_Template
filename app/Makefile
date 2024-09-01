# Compiler to use
CC=gcc

# Compiler flags, e.g. -g for debug, -Wall enables all warnings
CFLAGS=-g -Wall -IInc

# Build directory
BUILD_DIR = build

# Auto-detect source and header files
SOURCES=$(wildcard Src/*.c)
OBJECTS=$(patsubst Src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS=$(wildcard Inc/*.h)

# Final binary to build
BIN=$(BUILD_DIR)/app

# Default target
all: $(BIN)

# Rule for building the final binary, $^ refers to all dependencies
$(BIN): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

# Rule for building object files, $@ refers to the target, $< refers to the first dependency
$(BUILD_DIR)/%.o: Src/%.c $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to execute the compiled binary
run: $(BIN)
	@echo Running the application...
	@./$(BIN)

# Phony target for cleaning the build
.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
