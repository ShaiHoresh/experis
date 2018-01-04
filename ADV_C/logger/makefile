CFLAGS = -ansi -Wall -Wconversion -g
LDFLAGS = 

INC = -I../../inc

CC = gcc

.PHONY = clean

test_logger.out: logger.o config.o test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_logger.out logger.o config.o test.c

logger.o: logger.c  ../../inc/Logger.h
	$(CC) $(CFLAGS) -c logger.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

test.c: ../../inc/Logger.h
	$(CC) $(CFLAGS) test.c
	
clean:
	rm -f *.o test_logger.out

run:
	./test_logger.out
