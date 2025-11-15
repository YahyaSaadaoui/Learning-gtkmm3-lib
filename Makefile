UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CXX = g++
    TARGETS = demo1 demo2
    CLEAN_CMD = rm -f
endif

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    TARGETS = demo1 demo2
    CLEAN_CMD = rm -f
endif

ifeq ($(OS),Windows_NT)
    CXX = g++
    TARGETS = demo1.exe demo2.exe
    CLEAN_CMD = del
else
    TARGETS = demo1 demo2
    CLEAN_CMD = rm -f
endif

CXXFLAGS = -std=c++17 -Wall -O2 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`
OBJS = domino.o

all: $(TARGETS)

demo1: demo1.cpp
	$(CXX) $(CXXFLAGS) demo1.cpp -o demo1 $(LDFLAGS)

demo2: demo2.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) demo2.cpp domino.o -o demo2 $(LDFLAGS)

demo1.exe: demo1.cpp
	$(CXX) $(CXXFLAGS) demo1.cpp -o demo1.exe $(LDFLAGS)

demo2.exe: demo2.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) demo2.cpp domino.o -o demo2.exe $(LDFLAGS)

domino.o: domino.cpp domino.h
	$(CXX) $(CXXFLAGS) -c domino.cpp

clean:
	$(CLEAN_CMD) $(TARGETS) *.o

.PHONY: all clean
