.PHONY: all clean
CFLAGS=-O3 -g -std=gnu99 -Werror -Wextra -Wpedantic
all: dummy
clean:
	rm -f dummy dummy.c
dummy.c: binson_parser.c binson_writer.c
	cat \
	binson_parser.c \
	binson_writer.c \
	utest/binson_parser_test.c \
	> dummy.c

dummy: dummy.c
	$(CC) $(CFLAGS) \
	-I. \
	-Iutest \
	dummy.c \
	-o dummy