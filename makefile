# copied from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET_EXEC ?= frontend.exe

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(wildcard $(SRC_DIRS)/*.cpp) $(wildcard $(SRC_DIRS)/**/*.cpp)

INC_DIRS := $(sort $(dir $(wildcard $(SRC_DIRS)/*/)))
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC):
	$(CXX) $(INC_FLAGS) $(SRCS) -o $@
.PHONY: clean

clean:
	$(RMDIR) "$(BUILD_DIR)"
	$(MKDIR) "$(BUILD_DIR)"


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

