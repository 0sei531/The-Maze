# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g -I/usr/include/SDL2 -I./headers
LDFLAGS = -L/path/to/custom/lib -lm -lSDL2

# Source files and target
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = maze

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

