# Makefile used to build Tori

CC=gcc

SRC=$(wildcard src/*.c)
OBJS=$(patsubst %.c,%.o,$(SRC))

INCLUDE=-Isrc/
CFLAGS=-Wall -g

TARGET=tori

# Check for Windows
ifeq ($(OS),Windows_NT)
	EXE=.exe
	MKDIR=mkdir
	RM=del /Q
	RMDIR=rmdir /S /Q

# Unix systems
else
	EXE=
	MKDIR=mkdir -p
	RM=rm -f
	RMDIR=rm -rf
endif

BUILD_TARGET=build/$(TARGET)$(EXE)

all: $(BUILD_TARGET)

$(BUILD_TARGET): $(OBJS)
	$(MKDIR) build
	$(CC) $(OBJS) $(INCLUDE) $(CFLAGS) -o $(BUILD_TARGET)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RMDIR) build
	$(RM) $(OBJS)

test: $(BUILD_TARGET)
	$(BUILD_TARGET) tests/test.tori

valtest: $(BUILD_TARGET)
	valgrind --leak-check=yes --track-origins=yes $(BUILD_TARGET) tests/test.tori