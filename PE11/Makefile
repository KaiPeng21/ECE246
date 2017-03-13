##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pe11 is build since it
## is the label of the first rule

pe11: pe11.o huffman.o list_tree.o
	$(CC) $(CFLAGS) pe11.o huffman.o list_tree.o -o pe11

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pe11.o huffman.o list_tree.o pe11

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

