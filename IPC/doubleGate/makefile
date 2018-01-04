CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wconversion -std=gnu99 -g -c

all: tester yaodav

tester: barrier.o counter.o
	$(CC) $^ -o tester -pthread

yaodav: barrier.o main.o
	$(CC) $^ -o yaodav -pthread

barrier.o: barrier.c barrier.h

counter.o: counter.c barrier.h

run:
	./tester

runy:
	./yaodav
	
clean:
	rm -f *.o tester
