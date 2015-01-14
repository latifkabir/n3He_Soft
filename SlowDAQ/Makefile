#Auther: Latiful Kabir
#Makefile for Flux Gate Driver
#Date:09.08.14

CXX=g++
CFLAGS=-c 
LDFLAGS= -lncurses
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mag
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	       $(CXX)  $(OBJECTS) $(LDFLAGS) -o $@
%.o:%.cpp
	$(CXX) $(CFLAGS)  $< $(LDFLAGS) -o $@

clear:
	rm -f src/*.o

clean:
	rm -f src/*.o $(EXECUTABLE)

