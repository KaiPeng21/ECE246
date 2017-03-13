#ifndef PE06_H
#define PE06_H 

#define CORN 'X'
#define GRASS ' '

#include <stdio.h>

/* Determine the dimensions of the maze contain in file. */
/* The maze will always of the correct format */
/* the number of rows is stored at location pointed to by nrow */ 
/* the number of ncol is stored at location pointed to by ncol */

void Find_maze_dimensions(FILE *fptr, int *nrow, int *ncol)
			__attribute__((nonnull));

/* Determine the column location of the top opening */

int Find_opening_location(FILE *fptr)
			__attribute__((nonnull (1)));

/* Count the number of locations with grass */
/* A location has grass if it is a space, ' ', or GRASS */

int Count_grass_locations(FILE *fptr)
			__attribute__((nonnull (1)));

/* Return the type of location: CORN or GRASS, i.e. 'X' or ' ' */
/* In other words, return the character in the file for that location */ 
/* The location is specified by its row-column coordinates. */
/* The coordinates are specified by row and col */
/* These coordinates will always be valid for the given maze */
/* You do not have to worry about the coordinates being out of range */

char Get_location_type(FILE *fptr, int row, int col)
			__attribute__((nonnull (1)));
 
/* Given a filename, re-represent the maze in the file pointer fptr */
/* in a single line */
/* The return value should be the number of characters written into the */
/* the new file */
/* if the writing to a file fails, you should return -1 */ 

int Represent_maze_in_one_line(char *filename, FILE *fptr)
			__attribute__((nonnull));

#endif
