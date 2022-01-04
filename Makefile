CC = clang
CFLAGS = -Wall
TARGET = ls

.PHONY: all clean check format

all: $(TARGET)
$(TARGET) : ls.o file.o util.o

clean :
	rm -f $(TARGET) test *.o
check : $(TARGET) test
	./test
format :
	clang-format -i *.c
