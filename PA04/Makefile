##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pa04 is build since it
## is the label of the first rule

pa04: pa04.o bmp.o
	$(CC) $(CFLAGS) pa04.o bmp.o -o pa04

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pa04.o bmp.o pa04

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

