CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC
INC_PATH = ../../inc/
LIB_PATH = ../../lib/
CC = gcc

testHeap: vector testHeap.o $(LIB_PATH)libHeap.so.1.0 $(LIB_PATH)libVector.so.1.0
	$(CC) -o testHeap testHeap.o $(LIB_PATH)libDS.so

$(LIB_PATH)libHeap.so.1.0: Heap.o
	$(CC) -shared -Wl,-soname,libHeap.so.1 -o libHeap.so.1.0 Heap.o
	ln -sf libHeap.so.1.0 $(LIB_PATH)libHeap.so.1
	ln -sf libHeap.so.1.0 $(LIB_PATH)libHeap.so
	mv libHeap.so.1.0 $(LIB_PATH)

testHeap.o: testHeap.c $(INC_PATH)Heap.h
	$(CC) $(CFLAGS) testHeap.c -c

Heap.o: Heap.c $(INC_PATH)Heap.h
	$(CC) $(CFLAGS) Heap.c -c

vector: 
	make -C ../vector

clean:
	make -C ../vector clean
	rm -f testHeap *.o $(LIB_PATH)libHeap.so.1.0 $(LIB_PATH)libHeap.so.1 $(LIB_PATH)libHeap.so $(LIB_PATH)libHeap.a

run:
	./testHeap
