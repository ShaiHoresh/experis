CC = gcc
CFLAGS = -ansi -pedantic -Wall
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: testVector testSorts

testVector: testvector.o vector.o
	$(CC) $^ -o $@

testSorts: Sorts.o testSorts.o vector.o
	$(CC) $^ -o $@

testvector.o: testvector.c

vector.o: vector.c vector.h

Sorts.o: Sorts.c Sorts.h

testSorts.o: testSorts.c

sorts:
	./testSorts

vector:
	./testVector

clean:
	rm -f *.o testVector testSorts
