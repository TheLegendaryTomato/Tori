# Makefile to build the lexer/parser using flex and bison

# == Variables =================================================
# As a user, the following variables may be changed by you.
# Anything past this section should not be modified, unless you
# know what you are doing.

CC = gcc
CFLAGS = -Wall -g -MMD -MP

OBJS = syntax.tab.o syntax-no-main.tab.o lex.yy.o
TARGET = tparse

# == Targets ===================================================
all: $(TARGET)

syntax.tab.c syntax.tab.h: syntax.y
	bison -d syntax.y

syntax-no-main.tab.c syntax-no-main.tab.h: syntax-no-main.y
	bison -d syntax-no-main.y

lex.yy.c: tokens.l
	flex tokens.l

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) syntax.tab.o lex.yy.o -o $(TARGET) -lfl

clean:
	rm -fr *.c
	rm -fr *.h
	rm -fr *.o
	rm -fr *.d
	rm -fr tparse

-include $(DEPS)
