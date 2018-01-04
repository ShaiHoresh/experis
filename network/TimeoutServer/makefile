# Global definitions
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wconversion

#TARGET: server client

all: libList.a client ser

server.o: server.c comm.o

comm.o: comm.c comm.h

libList.a:
	make -C ./List
	
client:
	make -C ./Client
	
ser: comm.o server.o libList.a
	$(CC) $(CFLAGS)  $^ -o ser

clean:
	rm -f *.o ser

