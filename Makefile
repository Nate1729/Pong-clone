COMPILER = gcc
SRC = main.c
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
COMPILER_OPTS = -std=c89

Pong: main.c
	$(COMPILER) $(SRC) $(LINKER_FLAGS) $(COMPILER_OPTS) -o pong
