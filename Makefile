CC = clang
CFLAGS = -Wall
TARGET = ls

.PHONY: all clean check format

all: $(TARGET)
$(TARGET) : ls.c

clean :
	rm -f $(TARGET) test
check : $(TARGET) test
	./test
format :
	clang-format -i *.c
