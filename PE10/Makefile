##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pe10 is build since it
## is the label of the first rule

pe10: pe10.o bmp.o
	$(CC) $(CFLAGS) pe10.o bmp.o -o pe10

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pe10.o bmp.o pe10

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

