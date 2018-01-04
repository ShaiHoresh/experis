CC = gcc
CFLAGS = -pedantic -Wall -Wconversion -std=gnu99


all: sender reciever

sender: sender.o MessageQ.o
	$(CC) $^ -o sender

reciever: reciever.o MessageQ.o
	$(CC) $^ -o reciever

sender.o: sender.c MessageQ.h

reciever.o: reciever.c MessageQ.h

MessageQ.o: MessageQ.c MessageQ.h

clean:
	rm -f *.o reciever sender

runs:
	./sender

runr:
	./reciever
