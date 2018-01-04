CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wconversion -g -fPIC
SFLAGS = -shared -Wl,-soname,
LDFLAGS = -g
INC_DIR = ../../inc/
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../lib/
LDFLAGS += -L$(LIB_DIR)

LIB_NAME = libLinkedList.so

# all contents of current directory
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET = $(LIB_PATH)libLinkedList.so

all: $(LIB_PATH)libLinkedList.so.1.0

$(LIB_PATH)libLinkedList.so.1.0: $(OBJS)
	$(CC) $(SFLAGS)libLinkedList.so.1 -o libLinkedList.so.1.0 $(OBJS)
	ln -sf libLinkedList.so.1.0 $(LIB_DIR)libLinkedList.so.1
	ln -sf libLinkedList.so.1.0 $(LIB_DIR)libLinkedList.so
	mv libLinkedList.so.1.0 $(LIB_DIR)

# Dependencies


#all: $(TARGET)
 
$(TARGET): $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.c) > depends

clean:
	rm -f $(OBJS) $(LIB_PATH)libLinkedList.so.1.0 $(LIB_PATH)libLinkedList.so.1 $(LIB_PATH)libLinkedList.so
