CC = gcc
CFLAGS = -Wall -Wextra -std=c17 `pkg-config --cflags sdl2 SDL2_gfx`
LDFLAGS = `pkg-config --libs sdl2 SDL2_gfx`

SRC = random-walk.c utils.c
OBJ = $(SRC:.c=.o)
OUT = app

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

%.o: %.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all clean
