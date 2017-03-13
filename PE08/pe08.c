#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"

int main(int argc, char * argv[]){

  if (argc < 2){
    fprintf(stderr, "Insufficient argments.\n");
    return EXIT_FAILURE;
  }
  if (argv[1][0] == '-' && argv[1][1] == 'm' && argv[1][2] == '\0'){
    if (argc < 5){
      fprintf(stderr, "Insufficient arguments.\n");
      return EXIT_FAILURE;
    }
    double **matrixa;
    double **matrixb;
    double **product;
    int sizea = 0;
    int sizeb = 0;
    // read matrixa and matrixb from files
    matrixa = Read_matrix_from_file(argv[2], &sizea);
    if (matrixa == NULL){
      return EXIT_FAILURE;
    }
    matrixb = Read_matrix_from_file(argv[3], &sizeb);
    if (matrixb == NULL){
      Deallocate_matrix_space(matrixa, sizea);
      return EXIT_FAILURE;
    }
    if (sizea != sizeb){
      fprintf(stderr, "Multiplication cannot be carried out because the two given matrices have differnt dimensions.\n");
      Deallocate_matrix_space(matrixa, sizea);
      Deallocate_matrix_space(matrixb, sizeb);
      return EXIT_FAILURE;
    }
    // perform matrix multiplication and write the product to file
    product = Matrix_matrix_multiply(matrixa, matrixb, sizea);
    if (product == NULL){
      Deallocate_matrix_space(matrixa, sizea);
      Deallocate_matrix_space(matrixb, sizeb);
      return EXIT_FAILURE;
    }
    int write_success = Write_matrix_to_file(argv[4], product, sizea);
    if (write_success == 0){
      Deallocate_matrix_space(matrixa, sizea);
      Deallocate_matrix_space(matrixb, sizeb);
      Deallocate_matrix_space(product, sizea);
      return EXIT_FAILURE;
    }
  


    // deallocate matrices
    Deallocate_matrix_space(matrixa, sizea);
    Deallocate_matrix_space(matrixb, sizeb);
    Deallocate_matrix_space(product, sizea);
  }
  else if (argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == '\0'){
    if (argc < 4){
      fprintf(stderr, "Insufficient arguments.\n");
      return EXIT_FAILURE;
    }
    double **matrixa;
    double **matrixb;
    int sizea = 0;
    int sizeb = 0;
    // read matrixa and matrixb from files
    matrixa = Read_matrix_from_file(argv[2], &sizea);
    if (matrixa == NULL){
      return EXIT_FAILURE;
    }
    matrixb = Read_matrix_from_file(argv[3], &sizeb);
    if (matrixb == NULL){
      Deallocate_matrix_space(matrixa, sizea);
      return EXIT_FAILURE;
    }
    if (sizea != sizeb){
      fprintf(stderr, "Absolute difference sum cannot be carried out because the two given matrices have differnt dimensions.\n");
      Deallocate_matrix_space(matrixa, sizea);
      Deallocate_matrix_space(matrixb, sizeb);
      return EXIT_FAILURE;
    }
    // perform absolute difference sum and print the result to stdout
    printf("%e\n", Matrix_matrix_difference(matrixa, matrixb, sizea));
    // deallocate matrices
    Deallocate_matrix_space(matrixa, sizea);
    Deallocate_matrix_space(matrixb, sizeb);
  }
  else{
    fprintf(stderr, "Invalid argument.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
