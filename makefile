FRONTEND_BUILD_FLAGS = -o build/frontend.exe
SRCS = src/frontend.cpp

all: build

build:
	$(CXX) $(SRCS) $(FRONTEND_BUILD_FLAGS)

clean:
	$(RM) -r ./build/*