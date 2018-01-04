CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wpadded -Wconversion -g -lm 
INC_PATH = ../../inc/
LIB_PATH = ../../lib/

all: testHash

testHash: linkedlist testHash.o $(LIB_PATH)libHash.so.1.0
	$(CC) -o testHash testHash.o $(LIB_PATH)libHash.so.1.0  $(LIB_PATH)libLinkedList.so.1.0

$(LIB_PATH)libHash.so.1.0: Hash.o
	$(CC) -shared -Wl,-soname,libHash.so.1 -o libHash.so.1.0 Hash.o
	ln -sf libHash.so.1.0 $(LIB_PATH)libHash.so.1
	ln -sf libHash.so.1.0 $(LIB_PATH)libHash.so
	mv libHash.so.1.0 $(LIB_PATH)

testHash.o: testHash.c $(INC_PATH)HashMap.h
	$(CC) $(CFLAGS) testHash.c -c

Hash.o: Hash.c $(INC_PATH)HashMap.h
	$(CC) $(CFLAGS) Hash.c -c

linkedlist: 
	make -C ../DoubleLL

clean:
	make -C ../DoubleLL clean
	rm -f testHash $(LIB_PATH)libHash.so.1.0 $(LIB_PATH)libHash.so.1 $(LIB_PATH)libHash.so testHash.o Hash.o

run: all
	./testHash
