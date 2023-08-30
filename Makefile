CC=gcc
CFLAGS=-Wall
EXECUTABLE=parser
xmlreader: linkedlist.o xmlreader.c
	$(CC) $(CFLAGS) linkedlist.o xmlreader.c -o $(EXECUTABLE)
linkedlist.o: linkedlist.h 