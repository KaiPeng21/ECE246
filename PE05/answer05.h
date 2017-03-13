#ifndef PE04_H
#define PE04_H 

/* this is the recursive logarithmic Fibonacci function */
/* n has to be an even number */
/* *fn1 should store the nth Fibonacci number */
/* *fn2 should store the (n-1)st Fibonacci number */

void logFibonacci(int n, unsigned long *fn1, unsigned long *fn2);

/* this is a function that calls recursive logarithmic Fibonacci function */
/* if n is even, call logFibonacci with n, and return *fn1 */
/* if n is odd, call logFibonacci with n+1 or n-1, post-process *fn1 and *fn2 */
 
unsigned long Fibonacci(int n);

#endif


