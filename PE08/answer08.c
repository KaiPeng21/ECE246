#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* read a matrix from a file, return the matrix */
/* store the size of the matrix in *size        */
/* if the read fails, return NULL, and *size should be 0 */

double **Read_matrix_from_file(char *filename, int *size){
  *size = 0;
  // open the file for reading
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL){
    fprintf(stderr, "failed to open file.\n");
    *size = 0;
    return NULL;
  }

  // get the size
  int n_read;
  n_read = fread(size, sizeof(int), 1, fptr);

  // allocate matrix
  double **matrix;
  matrix = malloc(sizeof(double *) * (*size));
  if (matrix == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    fclose(fptr);
    return NULL;
  }

  matrix[0] = malloc(sizeof(double) * (*size) * (*size));
  if (matrix[0] == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    free(matrix);
    fclose(fptr);
    return NULL;
  }
  int i, j;
  for (i = 1; i < *size; i++){
    matrix[i] = &(matrix[i-1][*size]);
  }

  // read matrix from file

  n_read = 0;  
  for (i = 0; i < *size; i++){
    for (j = 0; j < *size; j++){
      n_read = n_read + fread(&(matrix[i][j]), sizeof(double), 1, fptr);
    }
  }

 // printf("\nn_read: %d\n", n_read);

  fclose(fptr);
//  if (n_read != (*size) * (*size)){
//    return NULL;
//  }

  return matrix;
}


/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */
/* if the multiplication fails because of memory allocation failure */
/* return NULL */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size){
  double **product;
  product = malloc(sizeof(double *) * size);
  if (product == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    return NULL;
  }
  


  product[0] = malloc(sizeof(double) * size * size);
  if (product[0] == NULL){
    fprintf(stderr,"memory allocation failed.\n");
    free(product);
    return NULL;
  }
  int i, j, k;
  for (i = 1; i < size; i++){
    product[i] = &(product[i-1][size]);
  }
  
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

/* return the sum of the absolute differences between the */
/* corresponding entries of two given matrices of the same size */

double Matrix_matrix_difference(double **matrixa, double **matrixb, int size){
  double sum = 0;
  double diff;
  int i, j;
  
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      diff = fabs(matrixa[i][j] - matrixb[i][j]);
 //     if (diff < 0){
 //       diff = -diff;
 //     }
      sum = sum + diff;
    }
  }

  return sum;
}

/* write a matrix of a given size to a file, return 1 if the write is */
/* successful, otherwise, 0 */

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

