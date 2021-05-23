#Makefile

CC=gcc
CFLAGS=-lncurses

%.o: %.c %.h
	$(CC) -c $<

build: game.c game.h
	$(CC) $(CFLAGS) game.c game.h -o game 

clean:
	-rm *.o game 
