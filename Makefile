CC = gcc

# Directories
SRCDIR = ./src
OBJDIR = ./obj

# Compiler Options
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
INCDIRS = -Iinclude
CFLAGS = -std=c89 $(INCDIRS) $(LINKER_FLAGS)

# Files
CFILES=$(addprefix $(SRCDIR)/,main.c constants.c paddle.c)
OBJS=constants.o paddle.o main.o

all: pong

pong: $(OBJS)
	$(CC) -o pong $(CFLAGS) $^

%.o:%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm *.o
