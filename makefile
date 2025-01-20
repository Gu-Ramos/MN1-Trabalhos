# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra

# Source files
SRCS = src/main.cpp src/metodos.cpp

# Header files
HEADERS = src/metodos.hpp

# Output executable
TARGET = bin/main

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean