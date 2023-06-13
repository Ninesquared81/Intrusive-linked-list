CC = gcc

CFLAGS = -I../src/ -g -Werror

test.exe: ../bin/list.o test.c
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) ../bin/list.o test.c

../bin/list.o: ../src/list.c
	$(MAKE) -C .. ./bin/list.o
