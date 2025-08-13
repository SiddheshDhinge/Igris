# Compiler and flags
CC = g++
CFLAGS = -g -Wall -O0 -std=c++11

# Directories
SRC_DIR = src
BUILD_DIR = build

# Find all .cpp files recursively in src/
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Replace src/ with build/ and .cpp with .o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output binary
TARGET = app

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile each .cpp to corresponding .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build and output
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
