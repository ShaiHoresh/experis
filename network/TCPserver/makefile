# Global definitions
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wconversion

#TARGET: server client

all: ser

server.o: server.c comm.o

comm.o: comm.c comm.h

List:
	make -C ./List
	
ser: comm.o server.o libList.a
	$(CC) $(CFLAGS)  $^ -o ser

clean:
	rm -f *.o ser

