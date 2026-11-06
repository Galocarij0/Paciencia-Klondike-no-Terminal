CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -Iinclude

LDFLAGS = -lpdcurses

SRC = src/main.c src/game.c
OBJ = $(SRC:.c=.o)
TARGET = solitaire.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c %< -o %@

run: all
	./%(TARGET)

clean:
	rm -f src/*.o $(TARGET)