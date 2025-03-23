# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# SFML libraries (Linux and Windows)
SFML_LIBS_LINUX = -lsfml-graphics -lsfml-window -lsfml-system
SFML_LIBS_WINDOWS = -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -LC:\mingw64\lib

# Source files and output
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/obj/%.o, $(SRC))

# Detect OS
OS := $(shell uname)

# Select the correct SFML library based on the OS
ifeq ($(OS), Linux)
    SFML_LIBS = $(SFML_LIBS_LINUX)
    TARGET = build/launcher
else
    SFML_LIBS = $(SFML_LIBS_WINDOWS)
    TARGET = build/launcher.exe
endif

# Default target
all: $(TARGET)

# Link the object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

# Compile source files to object files
build/obj/%.o: src/%.cpp
	@mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf build/obj $(TARGET)

.PHONY: all clean run