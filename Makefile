CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -pedantic

bin/list.o: src/list.c | bin
	$(COMPILE.c) $(OUTPUT_OPTION) src/list.c

bin:
	mkdir bin
