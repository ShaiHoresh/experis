CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC
INC_PATH = ../../inc/
LIB_PATH = ../../lib/
CC = gcc

testStack: linkedlist testStack.o $(LIB_PATH)libStack.so.1.0  $(INC_PATH)Stack.h
	$(CC) -o testStack testStack.o $(LIB_PATH)libStack.so.1.0 $(LIB_PATH)libLinkedList.so.1.0

$(LIB_PATH)libStack.so.1.0: Stack.o
	$(CC) -shared -Wl,-soname,libStack.so.1 -o libStack.so.1.0 Stack.o
	ln -sf libStack.so.1.0 $(LIB_PATH)libStack.so.1
	ln -sf libStack.so.1.0 $(LIB_PATH)libStack.so
	mv libStack.so.1.0 $(LIB_PATH)

testStack.o: testStack.c
	$(CC) $(CFLAGS) testStack.c -c

Stack.o: Stack.c $(INC_PATH)Stack.h
	$(CC) $(CFLAGS) Stack.c -c

linkedlist: 
	make -C ../DoubleLL

clean:
	make -C ../DoubleLL clean
	rm -f testStack Stack.o testStack.o $(LIB_PATH)libStack.so.1.0
	rm -f $(LIB_PATH)libStack.so.1 $(LIB_PATH)libStack.so

run:
	./testStack
