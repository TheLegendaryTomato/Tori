# Tori building Makefile

# WARNING - the build system for this project is quite messy.
# Once it's all set up, as long as noone touches it, it
# shouldn't fall apart, but I didn't really know what I was
# doing when I was making it. It (should) work though! Don't
# change **anything** you're not sure of :)

# == Variables =================================================
# As a user, the following variables may be changed by you.
# Anything past this section should not be modified, unless you
# know what you are doing.

CC=gcc

SRC = src/intrp/*.c

PARSER_OBJS = src/parse/syntax-no-main.tab.o src/parse/lex.yy.o
INTRP_OBJS = $(patsubst %.c,%.o,$(wildcard src/intrp/*.c))

OBJS = $(INTRP_OBJS) $(PARSER_OBJS)
DEPS = $(OBJS:.o=.d)

INCLUDE = -Isrc/parse -Isrc/intrp
CFLAGS = -Wall -g -MMD -MP -lfl

TARGET = tori

# == Targets ===================================================

# For now, these are Unix only. Once the project makes it
# further, automatic platform checking and Windows targets will
# be added.

# The parser Makefile (src/parse/Makefile) is in charge of
# building its own binary and output files. This Makefile takes
# that executable and copies it into the build directory. It
# also links the output files into the interpreter when building
# it.

all: $(TARGET)
test: $(TARGET) test-parse test-intrp

$(TARGET): $(OBJS)
	mkdir -p build
	$(CC) $(OBJS) $(INCLUDE) $(CFLAGS) -g -o src/intrp/tori
	cp src/parse/tparse build/tparse
	cp src/intrp/tori build/tori

$(INTRP_OBJS): $(PARSER_OBJS)

$(PARSER_OBJS):
	make -C src/parse

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo
	rm -fr build
	rm -fr $(OBJS) $(DEPS)
	make clean -C src/parse

test-parse:
	@echo
	@echo Parser test:
	build/tparse < tests/parse.tori

test-intrp:
	@echo
	@echo Interpreter test:
	build/tori tests/test.tori

-include $(DEPS)
