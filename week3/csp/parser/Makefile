CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: test_parser

test_parser: test_parser.c csp_parser.c csp_parser.h
	$(CC) $(CFLAGS) -o $@ test_parser.c csp_parser.c

test: test_parser
	./test_parser

clean:
	rm -f test_parser

.PHONY: all test clean
