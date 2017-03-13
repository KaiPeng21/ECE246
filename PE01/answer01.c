#include <stdlib.h>
#include "answer01.h"

/* Return the largest partial sum of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the ith partial sum is the sum from array[0] through array[i] */
/* the partial sums are 1, 5, 4, 10, 5, 9 */
/* the largest partial sum of the array is 10 */
/* if the len is 0, the largest partial sum is 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may also assume that none of the partial sums will cause an overflow */

int largest_partial_sum(int * array, int len)
{
  // modify the function
  int partialSum[len];  // array of partial sum
  int i;                // counter
  int largest;          // largest partial sum

  if (len == 0)
  {
    largest = 0; // if the lenis 0, the largest partial sum is 0
  }
  else
  {
    partialSum[0] = array[0];  // the first element of the partial sum array is the same as the input array
    largest = partialSum[0];   // set the first element of the partial sum array as the largest partial sum
    for(i = 1; i < len; i++)
    {
      partialSum[i] = partialSum[i - 1] + array[i]; // calculate partial sum
      if (partialSum[i] > largest)                  // update the largest if the new partial sum is larger
      {
        largest = partialSum[i];
      }
    }
  }
  return largest;
}

/* Return the largest difference of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the largest difference is 6 - (-5) = 11 */
/* if the len is 0, the largest difference is 0 */
/* if the len is 1, the largest difference is also 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may assume that the largest difference will not cause an overflow */

int largest_difference(int * array, int len)
{
  // modify the function
  int i;        // counter
  int largest;  // largest element
  int smallest; // smallerst element
  int difference; // largest difference
        
  if (len == 0 || len == 1)
  {
    difference = 0; // if the len is 0 or 1, the largest difference is 0
  }
  else
  {
    largest = array[0];   // initialized the first element as the largest/ smallest element
    smallest = array[0];
    for (i = 1; i < len; i++)
    {
      if(array[i] > largest)  
      {
        largest = array[i]; // update the largest element
      }
      if(array[i] < smallest)
      {
        smallest = array[i];
      }
    }
    difference = largest - smallest; // calculate the largest difference
  }
  return difference;
}
