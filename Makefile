CFLAGS = -Wall
.PHONY: clean check format

ls : ls.c

clean :
	rm -f ls
format :
	clang-format -i *.c
check : ls
	./test.sh
