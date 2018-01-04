PATH = ../ADV_C/

OBJECTSDIRS = $(PATH)vector/vector.o $(PATH)DoubleLL/doubleLL.o $(PATH)BST/BST.o $(PATH)Stack/Stack.o $(PATH)Heap/Heap.o $(PATH)Hash/Hash.o  


libDS.a: $(OBJECTSDIRS)  
	ar -cvq $(OBJECTSDIRS) libDS.a

$(PATH)vector/vector.o:
	cd $(PATH)vector/ && $(MAKE) vector.o
	
$(PATH)DoubleLL/doubleLL.o:
	cd $(PATH)list/ && $(MAKE) doubleLL.o
	
$(PATH)Stack/Stack.o:
	cd $(PATH)stack/ && $(MAKE) Stack.o
	
$(PATH)BST/BST.o:
	cd $(PATH)BST/ && $(MAKE) BST.o
	
$(PATH)Heap/Heap.o:
	cd $(PATH)Heap/ && $(MAKE) Heap.o

$(PATH)Hash/Hash.o:
	cd $(PATH)Hash/ && $(MAKE) Hash.o


#CC = gcc



#libDS.so.1.0: *.so
#	$(CC) -shared -Wl,-soname,libDS.so.1 -o libDS.so.1.0
#	ln -sf libDS.so.1.0 $(LIB_PATH)libDS.so.1
#	ln -sf libDS.so.1.0 $(LIB_PATH)libDS.so

#clean:
#	rm -f libDS.so.1.0 libDS.so.1 libDS.so
