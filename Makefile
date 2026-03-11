# Makefile used to build Tori

# For now this only supports Linux, I will add building for Windows later

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
	@# Two running methods are provided - one with Valgrind,
	@# for leak checks and debugging, and one without it,
	@# which is the "real" version. To use one or the other,
	@# simply uncomment the line.

	@# "@" symbols are used to prevent these comments from
	@# appearing in the Makefile output.

	@#valgrind --leak-check=yes --track-origins=yes build/tori test/test.tori
	build/tori tests/test.tori