CC=clang
CFLAGS=-O2 -Wall
DEPS = coord_map.h
OBJ = coord_map.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ main.c $(CFLAGS)

test: main
	./main

.PHONY: main test
