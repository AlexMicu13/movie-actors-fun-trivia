CC = gcc
CC_FLAGS = -Wall -std=c99 -g

build: main.c
	$(CC) $(CC_FLAGS) main.c -o movies

clean:
	rm -f movies