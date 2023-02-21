CXX = g++
FRONTEND_BUILD_FLAGS = -o build/frontend.out
SRCS = src/unity.cpp

.PHONY: all build clean

all: build_program

build_program: build $(SRCS)
	$(CXX) $(SRCS) $(FRONTEND_BUILD_FLAGS)

build:
	mkdir -p build

clean:
	$(RM) build/*