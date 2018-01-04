# Global definitions
#CC = g++
#SFLAGS = -g -shared -Wl,-soname,
CXXFLAGS = -c -g -Wall -ansi -pedantic -Wconversion -fPIC
#SFLAGS = -shared -pthread

# Directory structure
INC_DIR = ../
CXXFLAGS += -I$(INC_DIR)
CPP_INC_DIR = ../../cpp_inc
CXXFLAGS += -I$(CPP_INC_DIR)

# all contents of current directory
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = $(OBJS:.o=.so)

#all: $(TARGET)

#(TARGET): $(OBJS)
#	$(CC) $(SFLAGS) $(OBJS) -o $(TARGET)
#	cp $(TARGET) ../

all: $(TARGET)

$(TARGET): $(OBJS)

$(OBJS): $(SRCS)
	g++ $(CXXFLAGS) SmokeDet.cpp -o SmokeDet.o
	g++ $(CXXFLAGS) Sprinkler.cpp -o Sprinkler.o
	g++ -shared SmokeDet.o -o SmokeDet.so -pthread
	g++ -shared Sprinkler.o -o Sprinkler.so -pthread
	cp *.so ../SOs



clean:
	-rm -f *.o *.so
	-rm -f ../SOs/*.so



#-o Agents.so -pthread

