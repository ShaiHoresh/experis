CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC
INC_PATH = ../../inc/
LIB_PATH = ../../lib/
CC = gcc

testVector: testVector.o $(LIB_PATH)libVector.so.1.0
	$(CC) -o testVector testVector.o $(LIB_PATH)libVector.so.1.0
	
$(LIB_PATH)libVector.so.1.0: vector.o
	$(CC) -shared -Wl,-soname,libVector.so.1 -o libVector.so.1.0 vector.o
	ln -sf libVector.so.1.0 $(LIB_PATH)libVector.so.1
	ln -sf libVector.so.1.0 $(LIB_PATH)libVector.so
	mv libVector.so.1.0 $(LIB_PATH)

testVector.o: testVector.c $(INC_PATH)vector.h $(INC_PATH)ADTDefs.h
	$(CC) $(CFLAGS) testVector.c -c

vector.o: vector.c $(INC_PATH)vector.h $(INC_PATH)ADTDefs.h
	$(CC) $(CFLAGS) vector.c -c

clean:
	rm -f vector.o testVector testVector.o $(LIB_PATH)libVector.so.1.0
	rm -f $(LIB_PATH)libVector.so.1 $(LIB_PATH)libVector.so

run:
	./testVector
