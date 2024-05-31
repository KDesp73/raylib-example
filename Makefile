CC = cc
CFLAGS = -Wall -Iinclude -I./raylib/raylib-5.0_linux_amd64/include -ggdb -DDEBUG
LDFLAGS = -L./raylib/raylib-5.0_linux_amd64/lib -lm -lpthread -ldl -l:libraylib.a

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
RAYLIB_DIR = raylib/src

# List all the source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Generate the corresponding object file names
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target: the final executable
TARGET = raylib_example

# Default target, build the executable
all: $(BUILD_DIR) $(TARGET)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the executable
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Generate compile_commands.json using bear
compile_commands.json: $(SRC_FILES)
	bear -- make

# Phony target to avoid conflicts with file names
.PHONY: all clean

