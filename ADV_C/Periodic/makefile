CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC -std=gnu99
INC_PATH = ../../inc/
LIB_PATH = ../../lib/
CC = gcc

testSCH: Heap testSCH.o $(LIB_PATH)libScheduler.so.1.0 $(LIB_PATH)libHeap.so.1.0
	$(CC) -o testSCH testSCH.c $(CFLAGS) $(LIB_PATH)libScheduler.so $(LIB_PATH)libHeap.so $(LIB_PATH)libVector.so

$(LIB_PATH)libScheduler.so.1.0: scheduler.o Task.o scTime.o 
	$(CC) -shared -Wl,-soname,libScheduler.so.1 -o libScheduler.so.1.0 scheduler.o Task.o scTime.o $(LIB_PATH)libHeap.so
	ln -sf libScheduler.so.1.0 $(LIB_PATH)libScheduler.so.1
	ln -sf libScheduler.so.1.0 $(LIB_PATH)libScheduler.so
	mv libScheduler.so.1.0 $(LIB_PATH)

testSCH.o: testSCH.c
	$(CC) $(CFLAGS) testSCH.c -c

scheduler.o:
	$(CC) $(CFLAGS) scheduler.c -c

Task.o:
	$(CC) $(CFLAGS) Task.c -c

scTime.o:
	$(CC) $(CFLAGS) scTime.c -c

Heap:
	make -C ../Heap

run:
	./testSCH

clean:
	rm -f testSCH $(LIB_PATH)libScheduler.so.1.0
	rm -f $(LIB_PATH)libScheduler.so.1 $(LIB_PATH)libScheduler.so
	rm -f testSCH.o scheduler.o Task.o scTime.o
