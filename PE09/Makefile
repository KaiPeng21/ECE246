##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pe09 is build since it
## is the label of the first rule

pe09: pe09.o bmp.o
	$(CC) $(CFLAGS) pe09.o bmp.o -o pe09

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pe09.o bmp.o pe09

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

