# Compiler
CC = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Find all .cpp files recursively in src/
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Replace src/ with build/ and .cpp with .o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output binary
TARGET = app

# Default mode (debug)
MODE ?= debug

# Flags per mode
CFLAGS_debug = -g -Wall -O0 -fno-omit-frame-pointer -std=c++11
CFLAGS_prod  = -Wall -O2 -std=c++11

# Select flags
CFLAGS = $(CFLAGS_$(MODE))

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

# Convenience targets
debug:
	$(MAKE) MODE=debug

prod:
	$(MAKE) MODE=prod
