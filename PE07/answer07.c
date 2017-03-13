#include <stdio.h>
#include <stdlib.h>
#include "answer07.h"

// if you want to declare and define new functions, put them here
// or at the end of the file


// do not remove #ifndef and #endif in this file, otherwise the evaluation
// would fail and you would definitely get 0
// any new functions you want to create and use in this file 
// should appear above these comments or at the end of this file

#ifndef NTEST_MEM

// allocate space for nrow x ncol maze, if allocation fails, return NULL
// if allocation fails, you are also responsible for freeing the memory
// allocated before the failure
// may assume that nrow and ncol are > 0

char **Allocate_maze_space(int nrow, int ncol)
{
   char **maze;
   int i;

   maze = malloc(sizeof(char *) * nrow);
   if (maze == NULL){
     fprintf(stderr, "memory allocation failed.(maze == NULL)\n");
     return NULL;
   }
 
   maze[0] = malloc(sizeof(int) * nrow * ncol);
   if (maze[0] == NULL){
     fprintf(stderr, "memory allocation failed (maze[0] == NULL)\n");
     free(maze);
     return NULL; 
   }
   for (i = 1; i < nrow; i++){
     maze[i] = &(maze[i-1][ncol]);
   }

   return maze;
}

// free the memory used for the maze
// you may assume that maze is not NULL, and all memory addresses are valid

void Deallocate_maze_space(char **maze, int nrow) 
{
   free(maze[0]);
   free(maze);

   return;
}

#endif /* NTEST_MEM */

#ifndef NTEST_READ

/* Read maze in a multi-line file into a 2D array of characters */
/* you may assume that the maze has odd row and column counts */

char **Read_maze_from_2Dfile(FILE *fptr, int *nrow, int *ncol)
{
   int ch;
   char **maze;

   fseek(fptr, 0, SEEK_SET);
   
   maze = Allocate_maze_space(*nrow, *ncol);
   if (maze == NULL){
     return NULL;
   }

   *nrow = *ncol = 0;
   while ((ch = fgetc(fptr)) != EOF){
     if (ch != '\n'){
       maze[*nrow][*ncol] = (char)ch;
       ++*ncol;
     }else{
       ++*nrow;
       *ncol = 0;
     }
   }

   *ncol = 0;
   fseek(fptr, 0, SEEK_SET);
   while((ch = fgetc(fptr)) != '\n'){
     ++*ncol;
   }

   return maze;
}

#endif /* NTEST_READ */

#ifndef NTEST_WRITE

/* Write maze in a 2D array of characters into a multi-line file */
/* you may assume that the maze has odd row and column counts */

int Write_maze_to_2Dfile(char *filename, char **maze, int nrow, int ncol) 
{
   int ct = 0;
   int i, j;
   FILE * fptr2 = fopen(filename, "w");
   if (fptr2 == NULL){
     return -1;
   }
   fseek(fptr2, 0, SEEK_SET);
   
   for (i = 0; i < nrow; i++){
     for (j = 0; j < ncol; j++){
       fputc(maze[i][j], fptr2);
       ct++;
     }
     fputc('\n', fptr2);
     ct++;
   }

   fclose(fptr2);
   return ct;
}

#endif /* NTEST_WRITE */

#ifndef NTEST_ROW

/* Expand the maze from nrow x ncol to (2nrow - 1) x ncol */
/* the top half of the maze is the same as the original maze */
/* the bottom half of the maze is a reflection of the original maze */
/* *nrow and *rcol have to be updated with the new row and column counts */
/* You have to create a new maze */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned, and both *nrow and *rcol set to 0 */
/* the original maze has to stay intact */
/* you may assume that the original maze has odd row and column counts */

char **Expand_maze_row(char **maze, int nrow, int ncol, int *rrow, int *rcol)
{
   *rrow = *rcol = 0;
   char **expMazeRow;
   expMazeRow = Allocate_maze_space((2 * nrow - 1), ncol);
   if (expMazeRow == NULL){
     *rrow = *rcol = 0;
     return NULL;
   }
   
   for (*rrow = 0; *rrow < nrow; ++*rrow){
     for (*rcol = 0; *rcol < ncol; ++*rcol){
       expMazeRow[*rrow][*rcol] = maze[*rrow][*rcol];
     }
   }
   for (*rrow = nrow; *rrow < (2 * nrow - 1); ++*rrow){
     for (*rcol = 0; *rcol < ncol; ++*rcol){
       expMazeRow[*rrow][*rcol] = maze[2*(nrow-1) - *rrow][*rcol];
     }
   }
     
   return expMazeRow;
}

#endif /* NTEST_ROW */

#ifndef NTEST_COL 

/* Expand the maze from nrow x ncol to nrow x 2ncol - 1 */
/* the left half of the maze is the same as the original maze */
/* the right half of the maze is a reflection of the original maze */
/* moreover, you have to create an opening between the left and right halves */
/* the opening should be at the middle row of the maze */
/* the opening must also be accessible from one of the grass-paths in the */
/* new maze */
/* to do that, you have to convert some locations with corns to grass */
/* starting from the new opening to the left and to the right until you reach */
/* a location that is adjacent to a location that has grass */
/*                                                                       */
/* *crow and *ccol have to be updated with the new row and column counts */
/* You have to create a new maze */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned, and both *crow and *ccol set to 0 */
/* the original maze has to stay intact */
/* you may assume that the original maze has odd row and column counts */

char **Expand_maze_column(char **maze, int nrow, int ncol, int *crow, int *ccol)
{
   *crow = *ccol = 0;
   char **expMazeCol;
   expMazeCol = Allocate_maze_space(nrow, (2 * ncol - 1));
   if (expMazeCol == NULL){
     *crow = *ccol = 0;
     return NULL;
   }
   for (*crow = 0; *crow < nrow; ++*crow){
     for (*ccol = 0; *ccol < ncol; ++*ccol){
       expMazeCol[*crow][*ccol] = maze[*crow][*ccol];
     }
     for (*ccol = ncol; *ccol < (2 * ncol - 1); ++*ccol){
       expMazeCol[*crow][*ccol] = maze[*crow][2*(ncol-1) - *ccol];
     }
   }

   expMazeCol[nrow / 2][ncol - 1] = ' ';
   
   int k = 0;
   while (expMazeCol[nrow / 2 + 1][ncol - 1 - k] == 'X' && expMazeCol[nrow / 2 - 1][ncol - 1 - k] == 'X' && expMazeCol[nrow / 2][ncol - 1 - k - 1] == 'X'){
     expMazeCol[nrow / 2][ncol - 1 - k - 1] = ' ';
     expMazeCol[nrow / 2][ncol - 1 - k + 1] = ' ';
     k++;
   }
   
   
   return expMazeCol;
}

#endif /* NTEST_COL */

// if you want to declare and define new functions, put them here
// or at the beginning of the file
