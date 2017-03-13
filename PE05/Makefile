##
## Makefile 
##

CC	= gcc

CFLAGS	= -Wall -Wshadow -Werror -g

## Build rule

pe05: pe05.o answer05.o 
	$(CC) $(CFLAGS) pe05.o answer05.o utility.o -o pe05

clean:	
	rm -f pe05.o answer05.o pe05

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

