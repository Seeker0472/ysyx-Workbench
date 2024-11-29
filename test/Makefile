# Makefile for compiling getenv_example

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Target executable
TARGET = getenv_example

# Source files
SRC = test.c

# Build target
all: $(TARGET) run

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run:
	echo $(MAKEFLAGS)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

