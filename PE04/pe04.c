#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "utility.h"
#include "answer04.h"

// an incomplete test function to call 
//
void test_long_int_to_string(long int number)
{
    int base; 

    // test for a range of base, including an invalid base 37
    // should also test whether the string has been changed

    for (base = 2; base < 38; base++) {

       // before you call the function 
       // initialize counter
       // set errno to zero

       Initialize_counter();

       errno = 0;
       char *converted_string = long_int_to_string(number, base);
       printf("  base %d: ", base);
       printf("errno: %d\n", errno);
       if (converted_string == NULL) {
          printf("Not converted\n");
       } else {
          printf("  Converted String: %s, strtol: %ld\n",
                  converted_string, strtol(converted_string, NULL, base));
          if (strtol(converted_string, NULL, base) == number) {
             printf("Successful conversion.\n");
          } else {
             printf("Unsuccessful conversion.\n");
          }
          free(converted_string);
       }
       // print errno
       Counter_statistics();
    }
}

int main(int argc, char * * argv)
{
    printf("Welcome to ECE264, we are working on PE04.\n\n");

    // some test cases for the long_int_to_string function

    // an array for the conversion from long int to string

    long int array[] = {0, 10, -10, CHAR_MAX, CHAR_MIN, 
                        SHRT_MAX, SHRT_MIN, INT_MAX, LONG_MAX,
                        LONG_MIN};

    // size of array

    int nelem = sizeof(array)/sizeof(long int);
    int i;

    // test out all of long int in the array

    for (i = 0; i < nelem; i++) {
      printf("\nConverting %ld:\n", array[i]);
      test_long_int_to_string(array[i]);
      printf("\n\n");
    }

    return EXIT_SUCCESS;
}
