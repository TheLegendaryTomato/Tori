# Makefile used to build Tori

# For now this only supports Linux, I will add building for Windoze later

CC=gcc

SRC=$(wildcard src/*.c)
OBJS=$(patsubst %.c,%.o,$(SRC))

INCLUDE=-Isrc/
CFLAGS=-Wall -g

TARGET=tori

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p build
	$(CC) $(OBJS) $(INCLUDE) $(CFLAGS) -o build/$(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -fr build
	rm -fr $(OBJS)

test: $(TARGET)
	build/tori tests/test.tori

valtest: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes build/tori test/test.tori