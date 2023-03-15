CXX = g++ -std=c++17
CPPFLAGS = -g -Wall
TARGET_EXEC ?= main


SRCS := $(wildcard *.cpp)

all: 
	$(CXX) $(CPPFLAGS) $(SRCS) -o $(TARGET_EXEC)

clean:
	$(RM) *.o *.gch main
	