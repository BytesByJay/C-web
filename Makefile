# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = 

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

# Files
TARGET = $(BIN_DIR)/cweb
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Create directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the server
run: $(TARGET)
	@echo "Starting server..."
	@$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)
	@echo "Clean complete"

# Phony targets
.PHONY: all run clean
