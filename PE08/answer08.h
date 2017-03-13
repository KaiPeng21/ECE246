#ifndef ANSWER08_H
#define ANSWER08_H

// if you want to declare more functions, insert after this line
// the function name should not start with two underscores "__" to avoid
// clashing with functions declared and defined by instructors for
// grading



//
// functions declared for PE08
//

/* free the memory used to store the matrix of a given size */

void Deallocate_matrix_space(double **matrix, int size);

/* read a matrix from a file, return the matrix */
/* store the size of the matrix in *size        */
/* if the read fails, return NULL, and *size should be 0 */

double **Read_matrix_from_file(char *filename, int *size);

/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */
/* if the multiplication fails because of memory allocation failure */
/* return NULL */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size);

/* return the sum of the absolute differences between the */
/* corresponding entries of two given matrices of the same size */

double Matrix_matrix_difference(double **matrixa, double **matrixb, int size);

/* write a matrix of a given size to a file, return 1 if the write is */
/* successful, otherwise, 0 */

int Write_matrix_to_file(char *filename, double **matrix, int size);

//
// functions declared for grading, all names started with two underscores "__"
// they will be defined by the instructors
//
void __Deallocate_matrix_space(double **matrix, int size);

double **__Read_matrix_from_file(char *filename, int *size);

double **__Matrix_matrix_multiply(double **matrixa, double **matrixb, int size);

double __Matrix_matrix_difference(double **matrixa, double **matrixb, int size);

int __Write_matrix_to_file(char *filename, double **matrix, int size);

#endif
