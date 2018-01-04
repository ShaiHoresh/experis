CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wconversion -lrt -pthread -g -std=gnu99

all: server client

server: server.o MsgQ.o
	$(CC) $^ -o server -pthread
	
client: client.o MsgQ.o
	$(CC) $^ -o client -pthread

server.o: server.c MsgQ.h
MsgQ.o: MsgQ.c MsgQ.h
client.o: client.c MsgQ.h

clean:
	rm -f *.o server client
	
runs:
	./server

runc:
	./client
	
debugs:
	gdb ./server
    
debugc:
	gdb ./client
