CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wconversion -g -pthread -fPIC -std=gnu99 -lm
INC_DIR = ../../inc/
LIB_DIR = ../../lib/
LIST_PATH = ../../ADV_C/

all: $(LIB_DIR)libPHash.so.1.0 linkedlist 

#testHash: linkedlist testHash.o $(LIB_DIR)libPHash.so.1.0
#	$(CC) -o testHash testHash.o $(LIB_DIR)libPHash.so.1.0  $(LIB_DIR)libLinkedList.so.1.0

$(LIB_DIR)libPHash.so.1.0: Hash.o
	$(CC) -pthread -shared -Wl,-soname,libPHash.so.1 -o libPHash.so.1.0 Hash.o
	ln -sf libPHash.so.1.0 $(LIB_DIR)libPHash.so.1
	ln -sf libPHash.so.1.0 $(LIB_DIR)libPHash.so
	mv libPHash.so.1.0 $(LIB_DIR)

#testHash.o: testHash.c $(INC_DIR)HashMap.h
#	$(CC) $(CFLAGS) testHash.c -c

Hash.o: Hash.c $(INC_DIR)HashMap.h
	$(CC) $(CFLAGS) -I$(INC_DIR) Hash.c -c

linkedlist: 
	make -C $(LIST_PATH)DoubleLL

clean:
	make clean -C $(LIST_PATH)DoubleLL
	rm -f  $(LIB_DIR)libPHash.so.1.0 $(LIB_DIR)libPHash.so.1 $(LIB_DIR)libPHash.so Hash.o
#	rm -f testHash.o testHash

#run: all
#	./testHash
#
#gdb: all
#	gdb ./testHash
