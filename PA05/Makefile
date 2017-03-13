##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pa05 is build since it
## is the label of the first rule

pa05: pa05.o huffman.o list_tree.o
	$(CC) $(CFLAGS) pa05.o huffman.o list_tree.o -o pa05

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pa05.o huffman.o list_tree.o pa05

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

