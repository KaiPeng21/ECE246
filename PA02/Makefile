##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pa02 is build since it
## is the label of the first rule

pa02: pa02.o pa_answer02.o
	$(CC) $(CFLAGS) pa02.o pa_answer02.o -o pa02

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pa02.o pa_answer02.o pa02

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

