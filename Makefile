# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23 -O2

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE_DIR := include

# Find all .cpp and corresponding .o files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Executable name
TARGET := $(BIN_DIR)/MyProject

# Default rule
all: $(TARGET)

# Ensure bin and build directories exist before linking
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for compiling .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean compiled files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the program
run:
	./$(TARGET)
