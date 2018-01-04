CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wconversion -std=gnu99 -c
INC_DIR = ../inc

all: comm.o

comm.o: comm.c $(INC_DIR)/comm.h
	$(CC) $(CFLAGS) comm.c -I$(INC_DIR) 

clean:	
	rm -f comm.o

