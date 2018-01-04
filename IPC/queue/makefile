CC = gcc
CFLAGS = -ansi -pedantic -lrt -pthread -Wall -std=gnu99 -Wconversion -g
OBJ = queue.o producers.o consumers.o protectedQrun.o


all: $(OBJ) tester

tester: *.o
	$(CC) -o tester -pthread $(OBJ)

protectedQrun.o: protectedQrun.c queue.h consumers.h producers.h
	$(CC) $(CFLAGS) protectedQrun.c -c
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) queue.c -c
	
producers.o: producers.c queue.h producers.h
	$(CC) $(CFLAGS) producers.c -c
consumers.o: consumers.c queue.h consumers.h 
	$(CC) $(CFLAGS) consumers.c -c

clean:
	rm -f $(OBJ)
	
run:
	./tester
