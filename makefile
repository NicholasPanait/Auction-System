FRONTEND_BUILD_FLAGS = -o build/frontend.exe
SRCS = src/unity.cpp

all: build_program


build_program: build
	$(CXX) $(SRCS) $(FRONTEND_BUILD_FLAGS)

build:
	mkdir build

clean:
	$(RM) build/*