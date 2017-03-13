#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "answer05.h"

int main(int argc, char *argv[])
{
   printf("Welcome to ECE264, we are working on PE05.\n\n");

   if (argc != 2) {
      return EXIT_FAILURE;
   }
   int n = atoi(argv[1]);
   if (n < 0) {
      return EXIT_FAILURE;
   }
   Initialize_counter();
   unsigned long ans = Fibonacci(n);
   printf("%lu\n", ans);
   Counter_statistics();
   
   return EXIT_SUCCESS;
}
