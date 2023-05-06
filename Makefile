CC = gcc
CFLAGS=-Wall -Wextra -I./include
LDFLAGS = -lSDL2


SCR_FILES = $(wildcard ./src/*.c)
OBJ_FILES = $(SCR_FILES:.c=.o)

TARGET = chip8_emulator

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

./src/%.o: ./src/%.c
	$(CC) -c $(CFLAGS) $< -o $@ 


clean:
	rm -f $(OBJ_FILES) $(TARGET)