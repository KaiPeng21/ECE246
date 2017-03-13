#include <stdio.h>
#include <stdlib.h>
#include "answer07.h"


int main(int argc, char *argv[])
{
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL){
    fprintf(stderr, "failed to open the file.\n");
    return EXIT_FAILURE;
  }
  int i, j;
  int m = 7;
  int n = 9;

  if (argc != 3){
    return EXIT_FAILURE;
  }

  fseek(fptr, -3, SEEK_END);

  // Test Function 1 - allocate the maze
  char **maze;
  maze = Allocate_maze_space(m, n);
  if (maze == NULL){
    return EXIT_FAILURE;
  } 
  for (i = 0; i < m; i++){
    for (j = 0; j < n; j++){
      maze[i][j] = 'X';
    }
  } 
 

  // Test Function 3 - 
  char **mazeRead;
  mazeRead = Read_maze_from_2Dfile(fptr, &m, &n);
  if (mazeRead == NULL){
    return EXIT_FAILURE;
  }
  printf("\nTest Function 3:\n");
  for (i = 0; i < m; i++){
    for (j = 0; j < n; j++){
      printf("%c", mazeRead[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  // Test Function 4 -
  int numWC;
  numWC = Write_maze_to_2Dfile(argv[2], mazeRead, m, n);
  if (numWC == -1){
    fprintf(stderr, "failed to open the file for writing");
    return EXIT_FAILURE;
  }
  printf("\nTest Function 4:\n");
  printf("\nWord Count: %d\n", numWC); 


  // Test Functino 5 -
  int rm = 0;
  int rn = 0;
  char **mazeExpRow;
  mazeExpRow = Expand_maze_row(mazeRead, m, n, &rm, &rn);
  if (mazeExpRow == NULL){
    return EXIT_FAILURE;
  }
  printf("\nTest Function 5:\n");
  printf("Expanded row: %d Expanded col: %d\n", rm, rn);
  for (i = 0; i < 2*m-1; i++){
    for (j = 0; j < n; j++){
      printf("%c", mazeExpRow[i][j]);
    }
    printf("\n");
  }
  printf("\n");


  // Test Function 6 -
  int cm = 0;
  int cn = 0;
  char **mazeExpCol;
  mazeExpCol = Expand_maze_column(mazeRead, m, n, &cm, &cn);
  if (mazeExpCol == NULL){
    return EXIT_FAILURE;
  }
  printf("\nTest Function 6:\n");
  printf("Expanded row: %d Expanded col: %d\n", cm, cn);
  for (i = 0; i < m; i++){
    for (j = 0; j < 2*n-1; j++){
      printf("%c", mazeExpCol[i][j]);
    }
    printf("\n");
  }
  printf("\n");



  // Test Function 2 - deallocate the maze
  Deallocate_maze_space(maze, m);
  Deallocate_maze_space(mazeRead, m);
  Deallocate_maze_space(mazeExpRow, 2*m-1);
  Deallocate_maze_space(mazeExpCol, m);

  fclose(fptr);  
  return EXIT_SUCCESS;
}
