#include <stdio.h>
#include <stdlib.h>
#include "pa_answer03.h"

int main(int argc, char * argv[]){

  if (argc < 2){
    fprintf(stderr, "Insufficient arguments.\n");
  }

  // Testing Invert Function
  if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0'){
    if (argc < 4){
      fprintf(stderr, "Insufficient arguments. Expected 2 files following -i\n");
      return EXIT_FAILURE;
    }
    int size = 0;
    
    double **inputMat = Read_matrix_from_file(argv[2], &size);
    if (inputMat == NULL){
      fprintf(stderr, "Failed to read matrix from file\n");
      return EXIT_FAILURE;
    }

    /***START***
    int i, j;
    printf("\nInput matrix (to be invert):\n");
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
        printf(" %.0lf ", inputMat[i][j]);
      }
      printf("\n");
    }    
    ****END****/
 
    double **outputMat = Invert_matrix(inputMat, size);
    if (outputMat == NULL){
      fprintf(stderr, "Failed to invert matrix\n");
      Deallocate_matrix_space(inputMat, size);
      return EXIT_FAILURE;
    }

    /***START***
    printf("\nOutput matrix (inverted):\n");
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
        printf(" %.4lf ", outputMat[i][j]);
      }
      printf("\n");
    }
    ****END****/

    int w_success = Write_matrix_to_file(argv[3], outputMat, size);
    if (w_success == 0){
      fprintf(stderr, "Failed to write matrix to file\n");
      Deallocate_matrix_space(inputMat, size);
      Deallocate_matrix_space(outputMat, size);
      return EXIT_FAILURE;
    }

    Deallocate_matrix_space(inputMat, size);
    Deallocate_matrix_space(outputMat, size);
  }
  // Testing Muliplication Fuction
  else if (argv[1][0] == '-' && argv[1][1] == 'm' && argv[1][2] == '\0'){
    if (argc < 5){
      fprintf(stderr, "Insufficient arguments. Expected 3 files following -m\n");
      return EXIT_FAILURE;
    }
    int sizea = 0;
    int sizeb = 0;

    double **mata = Read_matrix_from_file(argv[2], &sizea);
    if (mata == NULL){
      fprintf(stderr, "Failed to read matrix from file\n");
      return EXIT_FAILURE;
    }
    double **matb = Read_matrix_from_file(argv[3], &sizeb);
    if (matb == NULL){
      fprintf(stderr, "Failed to read matrix from file\n");
      Deallocate_matrix_space(mata, sizea);
      return EXIT_FAILURE;
    }

    if (sizea != sizeb){
      fprintf(stderr, "Multiplication of matrices cannot be carried out because the given two inputs have different dimensions\n");
      Deallocate_matrix_space(mata, sizea);
      Deallocate_matrix_space(matb, sizeb);
      return EXIT_FAILURE;
    }
    double **matp = Matrix_matrix_multiply(mata, matb, sizea);
    if (matp == NULL){
      fprintf(stderr, "Multiplication of matrices failed\n");
      Deallocate_matrix_space(mata, sizea);
      Deallocate_matrix_space(matb, sizeb);
      return EXIT_FAILURE;
    }

    /***START***
    int i, j;
    printf("\nMatrix A:\n");
    for (i = 0; i < sizea; i++){
      for (j = 0; j < sizea; j++){
        printf(" %.0lf ", mata[i][j]);
      }
      printf("\n");
    }
    printf("\nMatrix B:\n");
    for (i = 0; i < sizeb; i++){
      for (j = 0; j < sizeb; j++){
        printf(" %.0lf ", matb[i][j]);
      }
      printf("\n");
    }
    printf("\nProduct: \n");
    for (i = 0; i < sizea; i++){
      for (j = 0; j < sizea; j++){
        printf(" %.0lf ", matp[i][j]);
      }
      printf("\n");
    }
    ****END****/

    int w_success = Write_matrix_to_file(argv[4], matp, sizea);
    if (w_success == 0){
      fprintf(stderr, "Failed to write matrix to file\n");
      Deallocate_matrix_space(mata, sizea);
      Deallocate_matrix_space(matb, sizeb);
      Deallocate_matrix_space(matp, sizea);
      return EXIT_FAILURE;
    }

      Deallocate_matrix_space(mata, sizea);
      Deallocate_matrix_space(matb, sizeb);
      Deallocate_matrix_space(matp, sizea);
  }
  // Testing Deviation Function
  else if (argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == '\0'){
    if (argc < 2){
      fprintf(stderr, "Insufficient arguments. Expected 1 file following -d\n");
      return EXIT_FAILURE;
    }
    int size = 0;

    double **mat = Read_matrix_from_file(argv[2], &size);
    if (mat == NULL){
      fprintf(stderr, "Failed to read matrix from file\n");
      return EXIT_FAILURE;
    }    

    printf("%e\n", Deviation_from_identity(mat, size));

    Deallocate_matrix_space(mat, size);
  }
  else{
    fprintf(stderr, "Invalid argument.\n");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
