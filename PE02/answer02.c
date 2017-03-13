#include <errno.h>
#include <ctype.h>
#include <limits.h>


#include "answer02.h"

// Given a char c, return a numeric value
// '0'..'9' --> 0..9
// 'a'..'z' --> 10..35
// 'A'..'Z' --> 10..35
// for other characters, return INV_SYMBOL (see answer02.h);
//
int char_to_int(char c)
{
   // what if c is '0'--'9'
   if (isdigit(c))
   {
     return (int) c - 48;
   } 

   // what if c is 'a'--'z'
   else if (islower(c))
   {
     return (int) c - 87;
   }

   // what if c is 'A'--'Z'
   else if (isupper(c))
   {
     return (int) c - 55;
   }

   // otherwise
   else
   {
     return INV_SYMBOL;
   }
}

// you are not allowed to change the contents at the location whose address in 
// stored in nptr (the way to interpret the type of nptr is that it is an address
// pointing to a constant char.)
//
// you have to check for whether the base in the valid range 2 through 36
// if not, set errno to EINVAL
// 
// This is a suggestion on how you should process the string
// (1)  skip over all white space
// (2)  if a +/- sign is encountered, set the polarity of the number accordingly
//      By default, the number is assumed to be positive if no sign is given.
// (3)  Convert the string until you encounter an invalid symbol for that 
//      base or when you reach the end of the string.
//
// examples (not exhaustive, of course):
//    "10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "   -10a:" in base 10 is -10, in base 16 is -266, and in base 36 is -1306 
//    " +10a:" in base 10 is 10, in base 16 is 266, in base 36 is 1306
//    "garbage" should be 0 in base 10, 0 in base 16, and 35479055534 in base 36
//
// you don't have to worry about the converted number being too big or too small
//
long int str_to_long_int(const char *nptr, int base)
{
   long int ret_value = 0;  // return value
                            // if no conversion happens, return 0
   int i = 0;               // counter
   int intValue;            // integer value converted from a character
   int positive = 1;        // check if the value is positive
   int signUsed = 0;        // counter for +/1 sign used

   // if invalid base, set errno and return immediately
   if (base < 2 || base > 36)
   {
     errno = EINVAL;
   }
   else
   { 
     while (isspace(nptr[i]) || ((nptr[i] == '+' || nptr[i] == '-') && (isdigit(nptr[i + 1])|| islower(nptr[i + 1]) || isupper(nptr[i + 1]))) || ((isdigit(nptr[i]) || islower(nptr[i]) || isupper(nptr[i])) && char_to_int(nptr[i]) < base && signUsed <= 1))
     {
   // valid base, skip over white space, white space includes tabs,
   // carriage return, etc (see function isspace).
       if (isspace(nptr[i]))
       {
         i++;
       }

   // if encounter a sign, expect a number after that 
   // if a negative sign is encountered, the conversion must
   // produce a negative number
       if (nptr[i] == '+' && (isdigit(nptr[i + 1]) || islower(nptr[i + 1]) || isupper(nptr[i + 1])))
       {
         signUsed++;
         i++;
       }
       if (nptr[i] == '-' && (isdigit(nptr[i + 1]) || islower(nptr[i + 1]) || isupper(nptr[i + 1])))
       {
         signUsed++;
         positive = 0;
         i++;
       }
     
   // now, convert the string to number
   // the conversion has to account for the +/- sign
       if ((isdigit(nptr[i]) || islower(nptr[i]) || isupper(nptr[i])) && char_to_int(nptr[i]) < base && signUsed <= 1)
       {
         intValue = char_to_int(nptr[i]);
         if (positive == 1)
         {
           ret_value = ret_value * base + intValue;
         }
         else if (positive == 0)
         {
           ret_value = ret_value * base - intValue; 
         }
       }
       i++;
     }   
   }

   return ret_value;
}
