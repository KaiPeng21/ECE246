#ifndef PE01_H
#define PE01_H

/* Return the largest partial sum of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the ith partial sum is the sum from array[0] through array[i] */
/* the partial sums are 1, 5, 4, 10, 5, 9 */
/* the largest partial sum of the array is 10 */
/* if the len is 0, the largest partial sum is 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may also assume that none of the partial sums will cause an overflow */

int largest_partial_sum(int * array, int len);

/* Return the largest difference of the array */
/* int array[] = { 1, 4, -1, 6, -5, 4} */
/* the largest difference is 6 - (-5) = 11 */
/* if the len is 0, the largest difference is 0 */
/* if the len is 1, the largest difference is also 0 */
/* you may assume that array is NULL when len is 0 */
/* but is non-NULL and correct when len is > 0 */
/* you may assume that the largest difference will not cause an overflow */

int largest_difference(int * array, int len);

#endif
