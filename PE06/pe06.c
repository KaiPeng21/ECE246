#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"

int main(int argc, char *argv[])
{
   printf("Welcome to ECE264, we are working on PE06.\n\n");

   if (argc < 3) {
      fprintf(stderr, "need two filenames\n");
      return EXIT_FAILURE;
   }
   FILE *fptr = fopen(argv[1], "r+");
   if (fptr == NULL){
      fprintf(stderr, "failed to open the file\n");
      return EXIT_FAILURE;
   }

   fseek(fptr, 0, SEEK_END);
   // Test Function 1
   int nrow = 0;
   int ncol = 0;
   Find_maze_dimensions(fptr, &nrow, &ncol);   
   printf("\nTest Function 1:\nWe have %d rows and %d columnns\n", nrow, ncol);

   // Test Function 2
   int openLoc = Find_opening_location(fptr);
   printf("\nTest Function 2:\nThe opening is at column %d\n", openLoc);

   // Test Function 3
   int grassNum =  Count_grass_locations(fptr);
   printf("\nTest Function 3:\nThere are %d locations with grass\n", grassNum);

   // Test Function 4
   int row = 2;
   int col = 4;
   char type =  Get_location_type(fptr, row, col);
   printf("\nTest Function 4:\nAt location (%d, %d), we have", row, col);
   if (type == ' '){ printf(" grass\n");}
   else if (type == 'X'){ printf(" corn\n");}
   else{ printf(" TEST FAILED\n");};
   printf("char type: %c.\n", type);
   
   // Test Function 5
   int num = Represent_maze_in_one_line(argv[2], fptr);
   printf("\nTest Function 5:\nThere are %d characters in the re-representation file\n\n", num);

   fclose(fptr);
   return EXIT_SUCCESS;
}

