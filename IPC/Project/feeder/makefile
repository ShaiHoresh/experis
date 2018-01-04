# Global definitions
CC = gcc
SFLAGS = -g -shared -Wl,-soname,
CFLAGS = -g -Wall -ansi -pedantic -fPIC -std=gnu99
LDFLAGS = -g
# Directory structure
INC_DIR = ../../../inc/
INC_UP = ../inc/
CFLAGS += -I$(INC_DIR) -I$(INC_UP)
#LIB_DIR = ../../../lib
#LDFLAGS += -L$(LIB_DIR)

LIB_NAME = libfeeder.so
#LDLIBS =-lPHash -lLinkedList

# all contents of current directory
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Target and sources
TARGET = feeder

# in case you have to use sources from another directory
LIB_SRCS = ../communication/comm.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Dependencies
all: $(TARGET)
 
$(TARGET): $(OBJS) $(LIB_OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -I$(INC_UP) $(OBJS:.o=.c) > depends

commit: $(LIB_FILE).1.0

#$(LIB_FILE): $(LIB_OBJS)
#	$(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
#	ln -sf $(LIB_NAME).1.0 $(LIB_FILE).1
#	ln -sf $(LIB_NAME).1.0 $(LIB_FILE)
#	mv $(LIB_NAME).1.0 $(LIB_DIR)/

comm:
	make -C ../communication

clean:
	-rm -f *.o
	-rm -f feeder
	-rm -f depends
#	-rm -f $(LIB_FILE) $(LIB_FILE).1 $(LIB_FILE).1.0

run: all
	./feeder
	
gdb: all
	gdb ./feeder

