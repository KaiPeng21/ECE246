#include "utility.h"
#include "answer05.h"

// do not remove #ifndef and #endif in this file, otherwise the evaluation
// would fail and you would definitely get 0

#ifndef NTEST_LOG

/* n is even */
/* *fn1 and *fn2 should store F(n) and F(n-1) */

void logFibonacci(int n, unsigned long *fn1, unsigned long *fn2)
{
  // increment the recursion counter 

  Increment_counter(&n);

  long tmp1, tmp2;
  // terminating condition
  if (n == 2){
    *fn1 = 1;
    *fn2 = 1;
  } 

  // recursion
  // you have to halve n, 
  // depending on whether n/2 is even or odd, recursively
  // call logFibonacci with appropriate parameters

  else if (n/2 % 2 == 0){
    logFibonacci(n / 2, fn1, fn2);
    tmp1 = *fn1;
    tmp2 = *fn2;
    *fn1 = 2 * tmp2 * tmp1 + tmp1 * tmp1;
    *fn2 = tmp2 * tmp2 + tmp1 * tmp1;
  }
  else if (n/2 % 2 == 1){
    logFibonacci(n / 2 - 1, fn1, fn2);
    tmp1 = *fn1 + *fn2;
    tmp2 = *fn1;
    *fn1 = 2 * tmp2 * tmp1 + tmp1 * tmp1;
    *fn2 = tmp2 * tmp2 + tmp1 * tmp1;
  }

   // decrement counter after all recursive calls
   // and before returning from the function.

   Decrement_counter();
}

#endif

#ifndef NTEST_FIB

/* n is can be odd or even */
/* n is assumed to be non-negative */
/* don't have to check for that */
unsigned long Fibonacci(int n)
{
   /* for storing the results when calling logFibonacci */

   unsigned long fn1 = 0; 
   unsigned long fn2 = 0;

   /* simple cases */
   if (n == 0){return 0;}
   if (n == 1){return 1;}

   /* if even n, call logFibonacci with n and return fn1 */
   /* if odd n, call with n-1 or n+1, combine fn1 and fn2 as F(n) */
   if (n % 2 == 0){
     logFibonacci(n, &fn1, &fn2);
     return fn1;
   }
   logFibonacci(n - 1, &fn1, &fn2);

   return fn1 + fn2;  // should change this, doing this so that compiler 
                      // would not complain.
}

#endif
