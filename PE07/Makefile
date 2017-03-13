##
##Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pe06 is build since it
## is the label of the first rule

pe06: pe07.o answer07.o
	$(CC) $(CFLAGS) pe07.o answer07.o -o pe07

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pe07.o answer07.o pe07

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

