CC       = gcc
TARGET   = bouncingBalls
SRCDIR   = src
INCDIR   = include
BUILDDIR = build

SRCS     = $(wildcard $(SRCDIR)/*.c)
OBJS     = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

CFLAGS   = -Wall -Wextra -std=c11 -I$(INCDIR) \
           $(shell sdl2-config --cflags) -lm
LDFLAGS  = $(shell sdl2-config --libs) -lSDL2_gfx -lm

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)
