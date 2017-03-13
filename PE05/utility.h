#ifndef UTILITY_H
#define UTILITY_H 

/* initialize the counter to 0 */
void Initialize_counter();

/* increment the counter by 1 */
void Increment_counter(void *reference_parameter);

/* return the current value of counter */
int Get_counter();

/* decrement counter */
void Decrement_counter();

/* print counter stistics */
void Counter_statistics();

#endif
