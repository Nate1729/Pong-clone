CC = gcc
SRC = main.c
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
INCDIRS = -Iinclude
CFLAGS = -std=c89 $(INCDIRS) $(LINKER_FLAGS)

CFILES=$(wilcard src/*.c)
OBJS=main.o constants.o paddle.o

BINARY=pong

all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:src/%.c
