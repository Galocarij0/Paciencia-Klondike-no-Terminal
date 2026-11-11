SHELL = /bin/sh
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/ucrt64/include/pdcurses
LDFLAGS = -lpdcurses

SRC = src/main.c src/game.c
OBJ = $(SRC:.c=.o)
TARGET = solitaire.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)