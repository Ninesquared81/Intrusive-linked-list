CC = gcc

CFLAGS = -g

bin/list.o: src/list.c | bin
	$(COMPILE.c) $(OUTPUT_OPTION) src/list.c

bin:
	mkdir bin
