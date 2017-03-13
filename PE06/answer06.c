#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"

/* Determine the dimensions of the maze contain in file. */
/* The maze will always of the correct format */
/* the number of rows is stored at location pointed to by nrow */ 
/* the number of ncol is stored at location pointed to by ncol */

void Find_maze_dimensions(FILE *fptr, int *nrow, int *ncol)
{
   *nrow = 0;
   *ncol = 0;
   int ch;

   fseek(fptr, 0, SEEK_SET);
   while ((ch = fgetc(fptr)) != EOF){
     if (ch == '\n'){
       ++*nrow;
     }
     if (*nrow == 0 && ch != '\n'){
       ++*ncol;
     }
   }
   return;
}

/* Determine the column location of the top opening */

int Find_opening_location(FILE *fptr)
{
   int opening = 0;
   int ch;
   fseek(fptr, 0, SEEK_SET);
   while ((ch = fgetc(fptr)) != '\n'){
     if (ch != ' '){
       opening++;
     }else{
       break;
     }
   }
   return opening;
}

/* Count the number of locations with grass */
/* A location has grass if it is a space, ' ', or GRASS */

int Count_grass_locations(FILE *fptr)
{
   int numGrass = 0;
   int ch;

   fseek(fptr, 0, SEEK_SET);
   while ((ch = fgetc(fptr)) != EOF){
     if (ch == ' '){
       numGrass++;
     }
   }
   return numGrass;
}

/* Return the type of location: CORN or GRASS, i.e. 'X' or ' ' */
/* In other words, return the character in the file for that location */ 
/* The location is specified by its row-column coordinates. */
/* The coordinates are specified by row and col */
/* These coordinates will always be valid for the given maze */
/* You do not have to worry about the coordinates being out of range */

char Get_location_type(FILE *fptr, int row, int col) 
{
   char type = 'X';
   int nrow = 0;
   int ncol = 0;
   int ch;

   fseek(fptr, 0, SEEK_SET);
   Find_maze_dimensions(fptr, &nrow, &ncol);
   int offset = row * (ncol+ 1) + col;
   fseek(fptr, offset, SEEK_SET);
   if ((ch = fgetc(fptr)) == ' '){
     type = ' ';
   }     


   return type;   
}
 
/* Given a filename, re-represent the maze in the file pointer fptr */
/* in a single line */
/* The return value should be the number of characters written into the */
/* the new file */
/* if the writing to a file fails, you should return -1 */ 

int Represent_maze_in_one_line(char *filename, FILE *fptr)
{
   int ch;
   int ct = 0;
   FILE *fptr2 = fopen(filename,"w");

   fseek(fptr, 0, SEEK_SET);
   if (fptr2 == NULL){
     return -1;
   }
   while ((ch = fgetc(fptr)) != EOF){
     if (ch != '\n'){
       fputc(ch, fptr2);
       ct++;
     }
   }
   fclose(fptr2);
   return ct;
}
