#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"


int getPad(uint16_t bits, int32_t width);
int getPad(uint16_t bits, int32_t width){
  int pad = 0;
  if(bits == 24){
    pad = width % 4;
  }
  else if (bits == 16){
    if (width % 2 == 1){pad = 2;}
    else if (width % 2 == 0){pad = 0;}
  }

  return pad;
}

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  // only for this assignment
  if (header->bits != 24 && header->bits != 16) {
    return FALSE;
  }

  // fill in extra to check for file size, image size
  // based on bits, width, and height

  
  fseek(fptr, 0, SEEK_END);
  int filesize = ftell(fptr);
  if (header->size != filesize){
    return FALSE;
  }
  fseek(fptr, 54, SEEK_SET);
  

  int pad = getPad(header->bits, header->width);
  if (header->imagesize != header->height * (header->width * (header->bits / 8) + pad)){
    return FALSE;
  }
  if (header->size != header->imagesize + 54){
    return FALSE;
  }


  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {

  // go to the beginning of the file

   BMP_Image *bmp_image = NULL;

  //Allocate memory for BMP_Image*;
   fseek(fptr, 0, SEEK_SET);   
   bmp_image = (BMP_Image *)malloc(sizeof(BMP_Image));
   if (bmp_image == NULL){
     fprintf(stderr, "Error allocating memory\n");
   }

  //Read the first 54 bytes of the source into the header
   int n_read;
   n_read = fread(&(bmp_image->header.type), sizeof(uint16_t), 1,fptr);
   n_read = fread(&(bmp_image->header.size), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.reserved1), sizeof(uint16_t), 1,fptr);
   n_read = fread(&(bmp_image->header.reserved2), sizeof(uint16_t), 1,fptr);
   n_read = fread(&(bmp_image->header.offset), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.DIB_header_size), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.width), sizeof(int32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.height), sizeof(int32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.planes), sizeof(uint16_t), 1,fptr);
   n_read = fread(&(bmp_image->header.bits), sizeof(uint16_t), 1,fptr);
   n_read = fread(&(bmp_image->header.compression), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.imagesize), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.xresolution), sizeof(int32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.yresolution), sizeof(int32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.ncolours), sizeof(uint32_t), 1,fptr);
   n_read = fread(&(bmp_image->header.importantcolours), sizeof(uint32_t), 1,fptr);

   /*  
   printf("\nRead:\n");
   printf("Size: %d\n", bmp_image->header.size);
   printf("Image Size: %d\n", bmp_image->header.imagesize);
   printf("Width: %d\n", bmp_image->header.width);
   printf("Heiht: %d\n", bmp_image->header.height);
   printf("Bits: %d\n", bmp_image->header.bits);
   printf("\n");
   */ 

  // if read successful, check validity of header
   if (Is_BMP_Header_Valid(&(bmp_image->header), fptr) == FALSE){
     free(bmp_image);
     fprintf(stderr, "Input file not in expected format\n");
     return NULL;
   }
   fseek(fptr, 54, SEEK_SET);

  // Allocate memory for image data
   uint32_t size = (bmp_image->header).size;
   int32_t width = (bmp_image->header).width;
   int32_t height = (bmp_image->header).height;
   uint16_t bits = (bmp_image->header).bits;
   bmp_image->data = malloc(size - 54);
   if (bmp_image->data == NULL){
     free(bmp_image);
     fprintf(stderr, "Error allocating memory\n");
     return NULL;
   }

   int pad = getPad(bits, width);
   int i, j;
   unsigned char (*addr)[width * bits/8 + pad];
   addr = (unsigned char (*) [width * bits/8 + pad])&(bmp_image->data[0]);


   for (i = 0; i < height; i++){
     for (j = 0; j < width * bits/8 + pad; j++){
       n_read = fread(&(addr[i][j]), 1, 1, fptr);
     }
   }


  // read in the image data

  return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
   // go to the beginning of the file
   fseek(fptr, 0, SEEK_SET);

   // write header
   int n_write;
   n_write = fwrite(&(image->header.type), sizeof(uint16_t), 1,fptr);
   n_write = fwrite(&(image->header.size), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.reserved1), sizeof(uint16_t), 1,fptr);
   n_write = fwrite(&(image->header.reserved2), sizeof(uint16_t), 1,fptr);
   n_write = fwrite(&(image->header.offset), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.DIB_header_size), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.width), sizeof(int32_t), 1,fptr);
   n_write = fwrite(&(image->header.height), sizeof(int32_t), 1,fptr);
   n_write = fwrite(&(image->header.planes), sizeof(uint16_t), 1,fptr);
   n_write = fwrite(&(image->header.bits), sizeof(uint16_t), 1,fptr);
   n_write = fwrite(&(image->header.compression), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.imagesize), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.xresolution), sizeof(int32_t), 1,fptr);
   n_write = fwrite(&(image->header.yresolution), sizeof(int32_t), 1,fptr);
   n_write = fwrite(&(image->header.ncolours), sizeof(uint32_t), 1,fptr);
   n_write = fwrite(&(image->header.importantcolours), sizeof(uint32_t), 1,fptr);

   /*  
   printf("\nWrite:\n");
   printf("Size: %d\n", image->header.size);
   printf("Image Size: %d\n", image->header.imagesize);
   printf("Width: %d\n", image->header.width);
   printf("Heiht: %d\n", image->header.height);
   printf("Bits: %d\n", image->header.bits);
   printf("\n");
   */
      
   // write image data
   int32_t width = (image->header).width;
   int32_t height = (image->header).height;
   uint16_t bits = (image->header).bits;
   int pad = getPad(bits, width);

   int i, j;
   unsigned char (*addr)[width * bits/8 + pad];
   addr = (unsigned char (*) [width * bits/8 + pad])&(image->data[0]);


   int wct = 0;
   for (i = 0; i < height; i++){
     for (j = 0; j < width * bits/8 + pad; j++){
       n_write = fwrite(&(addr[i][j]), 1, 1, fptr);
       if(n_write == 1){wct++;}
     }
   }

   if (wct != height * (width * bits/8 + pad)){
     fprintf(stderr, "Error writing to output file\n");
     return FALSE;
   }   

   return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {

  free(image->data);
  free(image);

}

// Given a valid BMP_Image, create a new image that retains the image in the
// box specified by left_x, right_x, bottom_y, top_y
//
BMP_Image *Crop_BMP_Image(BMP_Image *image, int left_x, 
                          int right_x, int bottom_y, 
                          int top_y)
{
   // getting the box coordinates to stay within range
   int32_t width = (image->header).width;
   int32_t height = (image->header).height;
   uint16_t bits = (image->header).bits;

   if (left_x < 0){left_x = 0;}
   if (right_x > width - 1){right_x = width - 1;}
   if (top_y > height - 1){top_y = height - 1;}
   if (bottom_y < 0){bottom_y = 0;}

   // proceed only if left_x <= right_x and bottom_y <= top_y
   if (left_x > right_x || bottom_y > top_y){
     fprintf(stderr, "Can't crop the image\n");
     return NULL;
   }

   // create a new image cropped from the given image
   /***Casting image to 2d array***/
   int pad = getPad(bits, width);
   unsigned char (*addr)[width * bits/8 + pad];
   addr = (unsigned char (*) [width * bits/8 + pad])&(image->data[0]);

   /***Allocate cropped image, t_image***/
   BMP_Image *t_image = NULL;
   int32_t tWidth = right_x - left_x + 1;
   int32_t tHeight = top_y - bottom_y + 1;
   uint16_t tBits = bits;
   int tpad = getPad(tBits, tWidth);
   t_image = malloc(sizeof(BMP_Image));
   if (t_image == NULL){
     fprintf(stderr, "Error allocating memoy\n");
     return NULL;
   }
   t_image->data = malloc(tHeight * (tWidth * tBits/8 + tpad));
   if (t_image->data == NULL){
     free(t_image);
     fprintf(stderr, "Error alocating memory\n");
     return NULL;
   }

   /***Casting t_image to 2d array***/
   unsigned char (* ptr)[tWidth * tBits/8 + tpad];
   ptr = (unsigned char (*) [tWidth * tBits/8 + tpad])&(t_image->data[0]);

   /***Assigning data from image to t_imagessigning data from image to t_image***/
   int i, j, m;
   for (i = 0; i < tHeight; i++){
     for (j = 0; j < tWidth * tBits/8; j++){
       ptr[i][j] = addr[bottom_y + i][left_x * bits/8 + j];
     }
     for (m = j; m < j+tpad; m++){
       ptr[i][m] = 0;
     }
   }

   /***assign and update the headers***/  
   t_image->header = image->header;
   (t_image->header).width = tWidth;
   (t_image->header).height = tHeight;
   (t_image->header).bits = tBits;
   (t_image->header).size = tHeight * (tWidth * tBits/8 + tpad) + 54;
   (t_image->header).imagesize = tHeight * (tWidth * tBits/8 + tpad);

   return t_image;
}
