# Compiler settings
# CXX = g++
CXX = clang++
CXXFLAGS = -O2 -march=native -Wall -Wextra -std=c++2c -MMD -MP -MF $(@:%.o=%.d) -Iinclude
# CXXFLAGS = -g -march=native -Wall -Wextra -std=c++2c -MMD -MP -MF $(@:%.o=%.d) -Iinclude

# Target executable
TARGET = grstr

# Source files
SRC_DIR = src
CPP_SRC = $(SRC_DIR)/main.cpp \
	 $(SRC_DIR)/gr/utf_sequence.cpp \
	 $(SRC_DIR)/gr/utf_string.cpp


# Build directory
BUILD_DIR = build_out
# OBJ = $(BUILD_DIR)/main.o
OBJECTS = $(CPP_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dependency files
DEP_DIR = $(BUILD_DIR)/.deps

# Detect operating system
UNAME_S := $(shell uname -s)
MSYSTEM := $(shell echo $$MSYSTEM 2>/dev/null)

# Set linker flags based on operating system
ifeq ($(UNAME_S), Linux)
    LDFLAGS = $(shell pkg-config --libs re2) -liconv
else
    LDFLAGS = $(shell pkg-config --libs re2) -liconv
endif

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/gr

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET): $(OBJECTS)
	@echo linking...
	@$(CXX) $^ -o $@ $(LDFLAGS)


# 包含依赖文件
-include $(wildcard $(BUILD_DIR)/*.d)
-include $(wildcard $(BUILD_DIR)/**/*.d)

# 清理
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

# 运行
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
