CC = gcc
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
CFLAGS = -std=c89
OBJECTS = paddle.o constants.o main.o

Pong: $(OBJECTS)
	$(CC) $(OBJECTS) $(LINKER_FLAGS) $(CFLAGS) -o pong

main.o: paddle.o constants.o main.c
	$(CC) $(CFLAGS) -c paddle.o constants.o main.c

paddle.o: paddle.c constants.o
constants.o: constants.c

clean:
	rm *.o
