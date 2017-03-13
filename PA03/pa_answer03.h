#ifndef PA_ANSWER03_H
#define PA_ANSWER03_H

#ifndef TOL
#define TOL 1e-10
#endif

// declare your functions here
// do not start your function names with a prefix of two underscores "__"

double **Allocate_matrix_space(int size);

double **Get_iden_matrix(int size);




// function that is declared and defined for you

int Is_zero(double value);

// functions that are declared and you have to define

// free the memory occupied by matrix of a given size

void Deallocate_matrix_space(double **matrix, int size);

// read from a file a matrix, which is returned
// the number of rows of the matrix should be stored in *size
// if the read fails, return NULL, and *size should be 0.

double **Read_matrix_from_file(char *filename, int *size);

// invert a matrix of a given size
// return the inverse of the matrix as double **
// if the inversion fails (because of memory allocation failure,
// or the given matrix is not invertible), return NULL

double **Invert_matrix(double **matrix, int size);

// multiply two given matrices of the same size
// return the product as double **
// if the multiplication fails (because of memory allocation failure), 
// return NULL

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size);

// calculate the sum of the absolute differences between all corresponding
// entries of two given matrices of the same size
// return the sum as double

double Deviation_from_identity(double **matrix, int size);

// write a given matrix of a given size to a file
// if the write is successful, return a 1
// otherwise, return a 0

int Write_matrix_to_file(char *filename, double **matrix, int size);

// functions declared and used by instructors
// each of the names has a prefix of two underscores "__"

int __Is_zero(double value);

void __Deallocate_matrix_space(double **matrix, int size);

double **__Read_matrix_from_file(char *filename, int *size);

double **__Invert_matrix(double **matrix, int size);

double **__Matrix_matrix_multiply(double **matrixa, double **matrixb, int size);

double __Deviation_from_identity(double **matrix, int size);

int __Write_matrix_to_file(char *filename, double **matrix, int size);

#endif
