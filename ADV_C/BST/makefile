CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC
INC_PATH = ../../inc/
LIB_PATH = ../../lib/
CC = gcc

testBST: testBST.o $(LIB_PATH)libBST.so.1.0
	$(CC) -o testBST testBST.o ../../lib/libBST.so.1.0

$(LIB_PATH)libBST.so.1.0: BST.o
#	ar -cvq libBST.a BST.o
#	mv libBST.a $(LIB_PATH)
#	
	$(CC) -shared -Wl,-soname,libBST.so.1 -o libBST.so.1.0 BST.o
	ln -sf libBST.so.1.0 $(LIB_PATH)libBST.so.1
	ln -sf libBST.so.1.0 $(LIB_PATH)libBST.so
	mv libBST.so.1.0 $(LIB_PATH)
	
BST.o: BST.c $(INC_PATH)binTree.h
	$(CC) $(FLAGS) BST.c -c

testBST.o: testBST.c $(INC_PATH)binTree.h
	$(CC) $(FLAGS) testBST.c -c

clean:
	rm -f testBST $(LIB_PATH)libBST.so.1.0 $(LIB_PATH)libBST.so.1 $(LIB_PATH)libBST.so BST.o testBST.o

run:
	./testBST
