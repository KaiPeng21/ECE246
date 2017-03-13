#include <stdio.h>
#include <stdlib.h>

char **Allocate_maze_space(int nrow, int ncol);
void Deallocate_maze_space(char **maze, int nrow);
char **Read_maze_from_2Dfile(FILE *fptr, int nrow, int ncol);
int Write_maze_to_2Dfile(char *filename, char **maze, int nrow, int ncol);
void Find_maze_dimensions(FILE *fptr, int *nrow, int *ncol);
int Find_opening_location(FILE *fptr);
int getNumOfGrass(char **maze, int nrow, int ncol);


void goEastEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr);
void goWestEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr);
void goSouthEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr);
void goNorthEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr);


// Useful functions from PE06 and PE07
int getNumOfGrass(char **maze, int nrow, int ncol){
  int numGrass = 0;
  int r, c;
  for (c = 0; c < ncol; c++){
    for (r = 0; r < nrow; r++){
      if(maze[r][c] == ' '){
        numGrass++;
      }
    }
  }

  return numGrass;
}


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

void Deallocate_maze_space(char **maze, int nrow)
{
   free(maze[0]);
   free(maze);

   return;
}

char **Read_maze_from_2Dfile(FILE *fptr, int nrow, int ncol)
{
   int ch;
   char **maze;

   fseek(fptr, 0, SEEK_SET);

   maze = Allocate_maze_space(nrow, ncol);
   if (maze == NULL){
     return NULL;
   }

   int m = 0;
   int n = 0;
   while ((ch = fgetc(fptr)) != EOF){
     if (ch != '\n'){
       maze[m][n] = (char)ch;
       ++n;
     }else{
       ++m;
       n = 0;
     }
   }

   fseek(fptr, 0, SEEK_SET);

   return maze;
}

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


// Recursion Functions

void goEastEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr){
  int ctE = 0;
  if (maze[*r][*c+1] == ' '){
    while (maze[*r][*c+1] == ' '){
      fputc('E', dirptr);
      ++*c;
      ++ctE;
      if(*r-1 >= 0 && maze[*r-1][*c] == ' '){goNorthEnd(maze, r, c, nrow, dirptr);}
      if(*r+1 < nrow && maze[*r+1][*c] == ' '){goSouthEnd(maze, r, c, nrow, dirptr);}
    }
    while(ctE != 0){
      fputc('W', dirptr);
      --*c;
      --ctE;
    }
  }
  return;
}
void goWestEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr){
  int ctW = 0;
  if (*c-1 >= 0 && maze[*r][*c-1] == ' '){
    while (maze[*r][*c-1] == ' '){
      fputc('W', dirptr);
      --*c;
      ++ctW;
      if(*r-1 >= 0 && maze[*r-1][*c] == ' '){goNorthEnd(maze, r, c, nrow, dirptr);}
      if(*r+1 < nrow && maze[*r+1][*c] == ' '){goSouthEnd(maze, r, c, nrow, dirptr);}
    }
    while(ctW != 0){
      fputc('E', dirptr);
      ++*c;
      --ctW;
    }
  }
  return;
}
void goSouthEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr){
  int ctS = 0;
  if (*r+1 < nrow && maze[*r+1][*c] == ' '){
    while (*r+1 < nrow && maze[*r+1][*c] == ' '){
      fputc('S', dirptr);
      ++*r;
      ++ctS;
      if(maze[*r][*c+1] == ' '){goEastEnd(maze, r, c, nrow, dirptr);}
      if(maze[*r][*c-1] == ' '){goWestEnd(maze, r, c, nrow, dirptr);}
    }
    while(ctS != 0){
      fputc('N', dirptr);
      --*r;
      --ctS;
    }
  }
  return;
}
void goNorthEnd(char **maze, int *r, int *c, int nrow, FILE *dirptr){
  int ctN = 0;
  if (*r-1 >=0 && maze[*r-1][*c] == ' '){
    while(*r-1 >= 0 && maze[*r-1][*c] == ' '){
      fputc('N', dirptr);
      --*r;
      ++ctN;
      if(maze[*r][*c+1] == ' '){goEastEnd(maze, r, c, nrow, dirptr);}
      if(maze[*r][*c-1] == ' '){goWestEnd(maze, r, c, nrow, dirptr);}
    }
    while(ctN != 0){
      fputc('S', dirptr);
      ++*r;
      --ctN;
    }
  }
  return;
}


// FUNCTION 1

void Get_mowing_directions(char *mazefile, char *directionfile){
  // Open files
  FILE * mazeptr = fopen(mazefile, "r");
  if (mazeptr == NULL){
    fprintf(stderr, "failed to open the file.\n");
    return;
  }
  FILE * dirptr = fopen(directionfile, "w+");
  if (dirptr == NULL){
    fprintf(stderr, "failed to open the file.\n");
    fclose(mazeptr);
    return;
  }

  // Determine the maze dimensions and opening location
  int nrow = 0;
  int ncol = 0;
  fseek(mazeptr, 0, SEEK_SET);
  Find_maze_dimensions(mazeptr, &nrow, &ncol);
  
  // Allocate an 2d array to store the maze in mazefile
  // Read the file into teh 2d array
  char **maze; 
  maze = Read_maze_from_2Dfile(mazeptr, nrow, ncol);

  // Algorithm
  int r = 0;
  int c = Find_opening_location(mazeptr);

  fseek(dirptr, 0, SEEK_SET);
  fputc('S', dirptr);
  ++r;
  goSouthEnd(maze, &r, &c, nrow, dirptr);
  goEastEnd(maze, &r, &c, nrow, dirptr);
  goWestEnd(maze, &r, &c, nrow, dirptr);
  
  fputc('N', dirptr);
  --r;

  // Deallocate the 2d array
  Deallocate_maze_space(maze, nrow);

  // Close files
  fclose(mazeptr);
  fclose(dirptr);  
  return;
}

// FUNCTION 2

int Simulate_mowing(char *mazefile, char *directionfile, char *mowedfile){
  int ctMowed = 0;

  // Open files
  FILE * mazeptr = fopen(mazefile, "r");
  if (mazeptr == NULL){
    fprintf(stderr, "failed to open the file.\n");
    return -1;
  }
  FILE * dirptr = fopen(directionfile, "r");
  if (dirptr == NULL){
    fprintf(stderr, "failed to open the file.\n");
    fclose(mazeptr);
    return -1;
  }
  fseek(mazeptr, 0, SEEK_SET);
  fseek(dirptr, 0, SEEK_SET);

  // Find maze dimensions and the opening  
  int nrow = 0;
  int ncol = 0;
  Find_maze_dimensions(mazeptr, &nrow, &ncol);
  int opening = Find_opening_location(mazeptr);
  
  
  // Allocate an 2d array to store the maze in mazefile
  // Read the file into teh 2d array
  char **maze;
  maze = Read_maze_from_2Dfile(mazeptr, nrow, ncol);

  int numGrass = getNumOfGrass(maze, nrow, ncol);
  // Algorithm
  int r = 0;
  int c = opening;
  int direct;
  int numChar;
  
  maze[r][c] = '.';
  ctMowed++;

  while((direct = fgetc(dirptr)) != EOF){
    if (direct == 'S'){
      ++r;
    }else if (direct == 'N'){
      --r;
    }else if (direct == 'E'){
      ++c;
    }else if (direct == 'W'){
      --c;
    }else{
      fprintf(stderr, "the direction character is invalid.\n");
      numChar = Write_maze_to_2Dfile(mowedfile, maze, nrow, ncol);
      Deallocate_maze_space(maze, nrow);
      fclose(mazeptr);
      fclose(dirptr);
      return -1;
    }
    
    if (r < 0 || r >= nrow || c < 0 || c >= ncol){
      fprintf(stderr, "the direction will take the ULM out of bound.\n");
      numChar = Write_maze_to_2Dfile(mowedfile, maze, nrow, ncol);
      Deallocate_maze_space(maze, nrow);
      fclose(mazeptr);
      fclose(dirptr);
      return -1;
    }
    if (maze[r][c] == 'X'){
      fprintf(stderr, "the direction will take the ULM to a location with corns.\n");
      numChar = Write_maze_to_2Dfile(mowedfile, maze, nrow, ncol);
      Deallocate_maze_space(maze, nrow);
      fclose(mazeptr);
      fclose(dirptr);
      return -1;
    }

    if (maze[r][c] == ' '){
      maze[r][c] = '.';
      ctMowed++;
    }
  }

// Output the mowed corn maze into the third file
  numChar = Write_maze_to_2Dfile(mowedfile, maze, nrow, ncol);

  if (r != 0 && c != opening){
    fprintf(stderr, "reach the end of the direction file, yet the ULM is not at the starting position.\n");
    Deallocate_maze_space(maze, nrow);
    fclose(mazeptr);
    fclose(dirptr);
    return -1;
  }

  int notMowed = numGrass - ctMowed;

  // Deallocate the 2d array
  Deallocate_maze_space(maze, nrow);
  
  // Close files
  fclose(mazeptr);
  fclose(dirptr);

  return notMowed;
}
