# Global definitions
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wconversion

#TARGET: server client

server.o: server.c

client.o: client.c

comm6.o: comm6.c comm6.h

comm.o: comm.c comm.h

ser: comm.o server.o
	$(CC) $(CFLAGS)  $^ -o ser
	
ser6: comm6.o server.o
	$(CC) $(CFLAGS)  $^ -o ser6

cli: comm.o client.o
	$(CC) $(CFLAGS)  $^ -o cli
	
cli6: comm6.o client.o
	$(CC) $(CFLAGS)  $^ -o cli6

runS:
	./server 2048
	
runC:
	./client 2048 127.0.0.1
	
gdb: all
	gdb ./test

