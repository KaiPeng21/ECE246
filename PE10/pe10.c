#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[]){
  if (argc < 3){
    fprintf(stderr, "Wrong number of arguments\n");
    return EXIT_FAILURE;
  }
  FILE *infptr = fopen(argv[1], "r");
  if (infptr == NULL){
    fprintf(stderr, "Error reading input file\n");
    return EXIT_FAILURE;
  }
  BMP_Image *image = Read_BMP_Image(infptr);
  if (image == NULL){
    fclose(infptr);
    return EXIT_FAILURE;
  }

  BMP_Image *n_image;
  if (image->header.bits == 24){
    n_image = Convert_24_to_16_BMP_Image(image);
  }
  else if (image->header.bits == 16){
    n_image = Convert_16_to_24_BMP_Image(image);
  }
  else{
    fprintf(stderr, "Image not in 16 bit format or 24 bit format\n");
    Free_BMP_Image(image);
    fclose(infptr);
    return EXIT_FAILURE;
  }
  if (n_image == NULL){
    Free_BMP_Image(image);
    fclose(infptr);
    return EXIT_FAILURE;
  }


  FILE *outfptr = fopen(argv[2], "w");
  if (outfptr == NULL){
    fprintf(stderr, "Error writing to output file\n");
    Free_BMP_Image(image);
    Free_BMP_Image(n_image);
    fclose(infptr);
    return EXIT_FAILURE;
  }

  int check = Write_BMP_Image(outfptr, n_image);
  if (check == FALSE){
    Free_BMP_Image(image);
    Free_BMP_Image(n_image);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }

  Free_BMP_Image(image);
  Free_BMP_Image(n_image);
  fclose(infptr);
  fclose(outfptr);
  return EXIT_SUCCESS;
}

