CC = clang
CFLAGS = -Wall
.PHONY: clean check format

ls : ls.c

clean :
	rm -f ls test
format :
	clang-format -i *.c
check : ls test
	./test
