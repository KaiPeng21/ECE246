#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pa_answer03.h"

// Do not change this function
// otherwise, your matrices may not match what we are expecting

int Is_zero(double value)
{
   if (value < 0) {
      value = -value;
   }
   if (value < TOL) {
      return 1;
   } else {
      return 0;
   }
}

// Write your functions below this line

// OTHER USEFUL FUNCTIONS

double **Get_iden_matrix(int size){
  double **iden;
  int i, j;

  iden = Allocate_matrix_space(size);
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      if (i == j) {iden[i][j] = 1;}
      else {iden[i][j] = 0;}
    }
  }

  /***START***
    printf("\nOriginal\n");
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
        printf(" %.0lf ", iden[i][j]);
      }
      printf("\n");
    }
  ****END****/

  return iden;
}

double **Allocate_matrix_space(int size){
  double **matrix;
  matrix = malloc(sizeof(double *) * size);
  if (matrix == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    return NULL;
  }

  matrix[0] = malloc(sizeof(double) * size * size);
  if (matrix[0] == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    free(matrix);
    return NULL;
  }
  int i;
  for (i = 1; i < size; i++){
    matrix[i] = &(matrix[i-1][size]);
  }

  return matrix;
}



// REQUIRED FUNCTION

double **Invert_matrix(double **matrix, int size){
  int r, c; // row and columns index
  int rswap; // the row we want to swap with r
  int i;
  double divFactor = 1;
  double multiFactor = 1;
  double **invert;
  invert = Get_iden_matrix(size);


  /***START****
  int j;
    printf("\nOriginal\n");
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
        printf(" %.0lf ", invert[i][j]);
      }
      printf(" | ");
      for (j = 0; j < size; j++){
        printf(" %.0lf ", matrix[i][j]);
      }
      printf("\n");
    }
  ****END****/
  
  for (c = 0; c < size; c++){
    for (r = c; r < size; r++){

      if (r == c){
        int rp;
        rswap = r;
        double max = fabs(matrix[r][c]);
        for (rp = r; rp < size; rp++){
          if(fabs(matrix[rp][c]) > max){
            rswap = rp;
            max = matrix[rp][c];
          }
        }
        if (Is_zero(matrix[rswap][c])){
          Deallocate_matrix_space(invert, size);
          return NULL;
        }
        if (r != rswap){
          double **tmp = Allocate_matrix_space(size);
          for (i = 0; i < size; i++){
            tmp[0][i] = matrix[rswap][i];
            matrix[rswap][i] = matrix[r][i];
            matrix[r][i] = tmp[0][i];
            tmp[1][i] = invert[rswap][i];
            invert[rswap][i] = invert[r][i];
            invert[r][i] = tmp[1][i];
          }
          Deallocate_matrix_space(tmp, size);
        }
      } 

      // make leading ones by dividing rows with a division factor
      if (r == c && !Is_zero(matrix[r][c]) && matrix[r][c] != 1){
        divFactor = matrix[r][c];
        for (i = 0; i < size; i++){
          matrix[r][i] = matrix[r][i] / divFactor;
          invert[r][i] = invert[r][i] / divFactor;
        }
      
        /***START***
        printf("\nMake leading ones\n");
        for (i = 0; i < size; i++){
          for (j = 0; j < size; j++){
            printf(" %.0lf ", invert[i][j]);
          }
          printf(" | ");
          for (j = 0; j < size; j++){
            printf(" %.0lf ", matrix[i][j]);
          }
          printf("\n");
        }
        ****END****/
     }

      // subtract non-leading-one rows by (num * leading-one row)
      if (r != c && !Is_zero(matrix[r][c])){
        multiFactor = matrix[r][c];
        for (i = 0; i < size; i++){
          matrix[r][i] = matrix[r][i] - multiFactor * matrix[c][i];
          invert[r][i] = invert[r][i] - multiFactor * invert[c][i];
        }
      
        /***START***
        printf("\ncancelling factors\n");
        for (i = 0; i < size; i++){
          for (j = 0; j < size; j++){
            printf(" %.0lf ", invert[i][j]);
          }
          printf(" | ");
          for (j = 0; j < size; j++){
            printf(" %.0lf ", matrix[i][j]);
          }
          printf("\n");
        }
        ****END****/
      }     
    }
  }

  
  for (c = 0; c < size; c++){
    for (r = c; r >= 0; r--){
      if (r != c){
        if (!Is_zero(matrix[r][c])){
          multiFactor = matrix[r][c];
          for (i = 0; i < size; i++){
            matrix[r][i] = matrix[r][i] - multiFactor * matrix[c][i];
            invert[r][i] = invert[r][i] - multiFactor * invert[c][i];
          }
        }
        /***START***
        printf("\ncancelling factors\n");
        for (i = 0; i < size; i++){
          for (j = 0; j < size; j++){
            printf(" %.5lf ", invert[i][j]);
          }
          printf(" | ");
          for (j = 0; j < size; j++){
            printf(" %.5lf ", matrix[i][j]);
          }
          printf("\n");
        }
        ****END****/
      }
    }
  }
    
  return invert;
}

double **Read_matrix_from_file(char *filename, int *size){
  *size = 0;
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL){
    fprintf(stderr, "failed to open file.\n");
    *size = 0;
    return NULL;
  }

  int n_read;
  n_read = fread(size, sizeof(int), 1, fptr);

  double **matrix;
  matrix = Allocate_matrix_space(*size);
  if (matrix == NULL){
    fclose(fptr);
    return NULL;
  }

  int i, j;
  n_read = 0;
  for (i = 0; i < *size; i++){
    for (j = 0; j < *size; j++){
      n_read = n_read + fread(&(matrix[i][j]), sizeof(double), 1, fptr);
    }
  }

  fclose(fptr);
  return matrix;
}

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size){
  double **product;
  product = Allocate_matrix_space(size);
  if (product == NULL){
    return NULL;
  }

  int i, j, k;
  double dot;
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      dot = 0;
      for(k = 0; k < size; k++){
        dot = dot + matrixa[i][k] * matrixb[k][j];
      }
      product[i][j] = dot;
    }
  }

  return product;
}

double Deviation_from_identity(double **matrix, int size){
  double deviation = 0;
  double **iden;
  iden = Get_iden_matrix(size);

  int i, j;
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      deviation = deviation + fabs(matrix[i][j] - iden[i][j]);
    }
  }

  Deallocate_matrix_space(iden, size);
  return deviation;
}

int Write_matrix_to_file(char *filename, double **matrix, int size){
  FILE * fptr = fopen(filename, "w");
  if (fptr == NULL){
    fprintf(stderr, "failed to open file.\n");
    return 0;
  }
  int n_write;
  int i, j;

  n_write = fwrite(&size, sizeof(int), 1, fptr);

  n_write = 0;
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      n_write = n_write + fwrite(&(matrix[i][j]), sizeof(double), 1, fptr);
    }
  }

  fclose(fptr);

  return 1;
}

void Deallocate_matrix_space(double **matrix, int size){

  free(matrix[0]);
  free(matrix);

  return;
}

