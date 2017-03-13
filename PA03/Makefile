##
## Makefile
##

## Define compiler

CC      = gcc

## Define flags

CFLAGS  = -Wall -Wshadow -Werror -g

## Build rule to build executable, by default, pa03 is build since it
## is the label of the first rule

pa03: pa03.o pa_answer03.o
	$(CC) $(CFLAGS) pa03.o pa_answer03.o -o pa03

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -f pa03.o pa_answer03.o pa03

## rule to compile .c to .o

%.o:    %.c
	$(CC) $(CFLAGS) -c $<

