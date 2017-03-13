#include <errno.h>
#include <ctype.h>
#include <limits.h>

#include "answer03.h"
#define IVY_SYMBOL 36
int char_to_int(char c);
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
//    "922337203685477580710304" in base 10 should return LONG_MAX, and errno 
//    should be set to ERANGE.
//    "-922337203685477580710304" in base 10 should return LONG_MIN, and errno 
//    should be set to ERANGE.
//    "garbage" should be 0 in base 10, 0 in base 16, and 35479055534 in base 36
//
long int str_to_long_int(const char *nptr, int base)
{
   long int ret_value = 0;  // return value
                            // if no conversion happens, return 0
   int i = 0;            //counter
   int intValue;     // converted integer value
   int positive = 1; // check if number is positive
   int signUsed = 0; // check if sign is used

   // if invalid base, set errno and return immediately
   if (base < 2 || base > 36)
   {
     errno = EINVAL;
   }
   else
   {
   // valid base, skip over white space
     while (nptr[i] != '\0' && (isspace(nptr[i]) || ((nptr[i] == '+' || nptr[i] == '-') && isxdigit(nptr[i + 1])) || ((isdigit(nptr[i]) || islower(nptr[i]) || isupper(nptr[i])) && char_to_int(nptr[i]) < base && signUsed <= 1)))
     {
       if (isspace(nptr[i]))
       {
         i++;
       }
   // if encounter a sign, expect a number after that 
   // if a negative sign is encountered, the conversion must
   // produce a negative number
       if (nptr[i] == '+')
       {
         signUsed++;
         positive = 1;
         i++;
       }
       if (nptr[i] == '-')
       {
         signUsed++;
         positive = 0;
         i++;
       }
   // now, convert the string to number
   // the conversion has to account for the +/- sign
   // need to check whether you have out-of-range ret_value
       if (isxdigit(nptr[i]) && char_to_int(nptr[i]) < base && signUsed <= 1)
       {
         intValue = char_to_int(nptr[i]);
         if (positive == 1)
         {
           if (LONG_MAX / base < ret_value || LONG_MAX - intValue < ret_value * base)
           {
             errno = ERANGE;
             ret_value = LONG_MAX;
             break;
           }
           else
           {
             ret_value = ret_value * base + intValue;
           }
         }
         else if (positive == 0)
         {
           if (LONG_MIN / base > ret_value || LONG_MIN + intValue > ret_value * base)
           {
             errno = ERANGE;
             ret_value = LONG_MIN;
             break;
           }
           else
           {
             ret_value = ret_value * base - intValue;
           }
         }
       }
       i++;
     }
   }
   // clean up before returning
   // need to set errno and ret_value correctly if the converted number 
   // is out of range
   return ret_value;
}

int char_to_int(char c)
{
  if (isdigit(c))
  {
    return (int) c - 48;
  }
  else if (islower(c))
  {
    return (int) c - 87;
  }
  else if (isupper(c))
  {
    return (int) c - 55;
  }
  else
  {
    return IVY_SYMBOL;
  }
}
