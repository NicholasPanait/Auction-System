# copied from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET_EXEC ?= build/frontend.exe

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(wildcard $(SRC_DIRS)/*.cpp) $(wildcard $(SRC_DIRS)/**/*.cpp)

INC_DIRS := $(sort $(dir $(wildcard $(SRC_DIRS)/*/)))
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

CXX = g++

all:
	$(CXX) $(INC_FLAGS) $(SRCS) -o $(TARGET_EXEC)
.PHONY: all build clean

clean:
	$(RM) $(BUILD_DIR)/*

ifeq ($(OS),Windows_NT)
    RM = del /F /Q 
    RMDIR = -RMDIR /S /Q
    MKDIR = -mkdir
    ERRIGNORE = 2>NUL || true
    SEP=\\
else
    RM = rm -rf 
    RMDIR = rm -rf
    MKDIR = mkdir -p
    ERRIGNORE = 2>/dev/null
    SEP=/
endif