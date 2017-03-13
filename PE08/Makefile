##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pe08 is build since it
## is the label of the first rule

pe08: pe08.o answer08.o
	$(CC) $(CFLAGS) pe08.o answer08.o -o pe08

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pe08.o answer08.o pe08

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

