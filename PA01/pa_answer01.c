#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include "pa_answer01.h"

// you should try to re-use a majority of the algorithms in PE02 and PE03
// for this programming assignment.
// However, you have to take care of endptr, base 0, and base 16
// these are the three additional things you have to deal with in
// this assignment, as compared to the str_to_long_int function
// that you wrote for PE02 and PE03.
//
// it is really IMPORTANT that you extensively try out the function
// strtol on your own.
//
int char_to_int(char c);

int char_to_int(char c)
{
  int ret;
  if(isdigit(c)){
    ret = (int) c - 48;
  }
  else if(isupper(c)){
    ret = (int) c - 55;
  }
  else if(islower(c)){
    ret = (int) c - 87;
  }
  else{
    ret = 36;
  }
  return ret;
}


long int my_strtol(const char *nptr, char **endptr, int base)
{
   long int ret_value = 0;  // return value
   int i = 0;               // counter
   int positive = 1;        // indicate if the number is positive
   int intValue;            // converted integer value from character
   int digitUsed = 0;       // check if any digit is used

   // if invalid base, set errno and return immediately
   if (base != 0 && (base < 2 || base > 36)){
     errno = EINVAL;
   }
   else{
   // valid base, skip over white space
     while(isspace(nptr[i])){
       i++;
     }

   // if encounter a sign, expect a number after that 
   // if a negative sign is encountered, change the sign
     if(nptr[i] == '+'){
       positive = 1;
       i++;
     }
     if(nptr[i] == '-'){
       positive = 0;
       i++;
     }
   
   // the exact algorithm is not given, but these are 
   // the tasks the function has to perform:  
   //
   // determine the actual base if the base is 0
   // if it starts with '0', it is octal
   // if '0' is followed by 'x' or 'X' it is hexadecimal or base 16
   // otherwise, it is decimal
   // therefore you have to determine the actual base and the starting
   // location to perform conversion
   //
   // for bases 2 to 15, perform conversion as in PE02
   //
   // for base 16, you have to decide when the conversion should
   // start: after the optional "0x" or "0X" or immediately
   // question: if you have "0xG", what should be converted?
   //
   // for bases 17 to 36, perform conversion as in PE02
   // 
   // after you have determine the real base, and where to start,
   // perform the conversion
     if (isxdigit(nptr[i])){
       if (base == 0 && nptr[i] == '0' && (nptr[i + 1] == 'x' || nptr[i + 1] == 'X')){
         base = 16;
       }
       else if (base == 0 && nptr[i] == '0'){
         base = 8;
       }
       else if (base == 0){
         base = 10;
       }
     }

     while(char_to_int(nptr[i]) < base){
       digitUsed++;
       if (base == 16 && nptr[i] == '0' && (nptr[i + 1] == 'x' || nptr[i + 1] == 'X') && char_to_int(nptr[i + 2]) < base){
         i = i + 2;
       }
       intValue = char_to_int(nptr[i]);
       if (positive == 1){
         if (LONG_MAX / base < ret_value || LONG_MAX - intValue < ret_value * base){
           errno = ERANGE;
           ret_value = LONG_MAX;
         }
         else{
           ret_value = ret_value * base + intValue;
         }
       }
       else if (positive == 0){
         if (LONG_MIN / base > ret_value || LONG_MIN + intValue > ret_value * base){
           errno = ERANGE;
           ret_value = LONG_MIN;
         }
         else{
           ret_value = ret_value * base - intValue;
         }
       }
       i++; 
     }   
   }
   // clean up, set ret_value properly if the conversion went out of range
   // set errno if necessary
   // set *endptr properly if the endptr is not NULL
   
   *endptr = (char *)&nptr[i];
     // if base is invalid, set endptr to NULL
   if (errno == EINVAL){
     *endptr = NULL;
   }
   else if (digitUsed == 0){
     *endptr = (char *)nptr;
   }
   

   return ret_value;
}
