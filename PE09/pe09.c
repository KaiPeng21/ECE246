#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bmp.h"

int main(int argc, char * argv[]){
  int left_x = INT_MIN; 
  int right_x = INT_MAX;
  int top_y = INT_MAX;
  int bottom_y = INT_MIN;

  if (argc < 3){
    fprintf(stderr, "Wrong number of arguments expected\n");
    return EXIT_FAILURE;
  }

  int i = 1;
  while (i < argc && argv[i][0] == '-' && argv[i][2] == '\0'){
    if (argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '\0'){
      if (i+1 >= argc){
        fprintf(stderr, "A number expected\n");
        return EXIT_FAILURE;
      }
      left_x = atoi(argv[i+1]);      
    }
    else if (argv[i][0] == '-' && argv[i][1] == 'r' && argv[i][2] == '\0'){
      if (i+1 >= argc){
        fprintf(stderr, "A number expected\n");
        return EXIT_FAILURE;
      }
      right_x = atoi(argv[i+1]);
    }
    else if (argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '\0'){
      if (i+1 >= argc){
        fprintf(stderr, "A number expected\n");
        return EXIT_FAILURE;
      }
      top_y = atoi(argv[i+1]);    
    }
    else if (argv[i][0] == '-' && argv[i][1] == 'b' && argv[i][2] == '\0'){
      if (i+1 >= argc){
        fprintf(stderr, "A number expected\n");
        return EXIT_FAILURE;
      }
      bottom_y = atoi(argv[i+1]);     
    }
    else{
      fprintf(stderr, "Invalid option\n");
      return EXIT_FAILURE;
    }
    i = i + 2;  
  }

  if (i > argc - 2){
    fprintf(stderr, "Wrong number of arguments expected\n");
    return EXIT_FAILURE;
  }

  FILE *infptr;
  FILE *outfptr;
  infptr = fopen(argv[i], "r");
  if (infptr == NULL){
    fprintf(stderr, "Can't open input file\n");
    return EXIT_FAILURE;
  }
  i++;
  outfptr = fopen(argv[i], "w");
  if (outfptr == NULL){
    fclose(infptr);
    fprintf(stderr, "Can't open output file\n");
    return EXIT_FAILURE;
  }

  BMP_Image * inputImage;

  inputImage = Read_BMP_Image(infptr);
  if (inputImage == NULL){
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }


  BMP_Image * cropImage;
  cropImage = Crop_BMP_Image(inputImage, left_x, right_x, bottom_y, top_y);
  if (cropImage == NULL){
    Free_BMP_Image(inputImage);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }


  int check;
  check = Write_BMP_Image(outfptr, cropImage);
  if (check == FALSE){
    Free_BMP_Image(inputImage);
    Free_BMP_Image(cropImage);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }

  Free_BMP_Image(inputImage);
  Free_BMP_Image(cropImage);
  fclose(infptr);
  fclose(outfptr);
  return EXIT_SUCCESS;
}
