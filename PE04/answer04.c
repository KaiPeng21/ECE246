#include <stdlib.h>
#include <errno.h>
#include "utility.h"
#include "answer04.h"

// do not modify before this line

char int_to_char(long int num);

// recursive implementation of the conversion of
// the magnitude of a given number to a string
// the sign is taken care of by the long_int_to_string function
// 

void rec_magnitude_long_int_to_string(long int number, int base, char *intstring, int *stringlen);


char int_to_char(long int num)
{
  if (num >= 0 && num <= 9){
    return (char) (num + 48);
  }
  else{
    return (char) (num + 55);
  }
}

void rec_magnitude_long_int_to_string(long int number, int base,
                                      char *intstring, int *stringlen)
{
   // increment the counter for counting the number of recursive calls
   // do not remove this line

   Increment_counter(&number);

   // put your code here
   long int n = number;
   int ct = 0;
   long int intVal;


   if (n == 0){
     ct = 1;
   } 
   else{
     while (n != 0){
       n /= base;
       ct++;
     }
   }
 
   if (number < 0)
   {
     intVal = - (number % base);
   }else{
     intVal = number % base;
   }
   
   ++*stringlen;
   if (intstring[0] == '-'){
     intstring[ct] = int_to_char(intVal);
   }
   else{
     intstring[ct - 1] = int_to_char(intVal);
   }

   number /= base;

   if (number != 0){
     rec_magnitude_long_int_to_string(number, base, intstring, stringlen);    
   } 
   
   // decrement the counter after all recursive calls and before
   // you exit from this function

   Decrement_counter();
}

char *long_int_to_string(long int number, int base)
{
   // the real function for long_int_to_string

   char intstring[65];  // 65 because the largest length needed is 
                        // for base 2, 1 byte for the negative sign,
                        // 63 bytes for the magnitude, and 1 byte for null char
   int stringlen = 0;

   if ((base < 2) || (base > 36)) {
      errno = EINVAL;
      return NULL;
   }
   if (number < 0) {
      intstring[0] = '-';

      // place the number at location 1 of intstring
      stringlen = 1;
   }
   rec_magnitude_long_int_to_string(number, base, intstring, &stringlen);

   // allocate enough space for null character
   char *ret_string = (char *)malloc(sizeof(char) * (stringlen + 1));

   // copy from intstring to ret_string and append '\0'
   int i;
   for (i = 0; i < stringlen; i++) {
      ret_string[i] = intstring[i];
   }
   ret_string[i] = '\0';
   return ret_string;
}
