#ifndef PE03_H
#define PE03_H 

// the argument nptr is expected to be non-NULL 
// nptr stores an address pointing to a constant char
// in other words, you should not change the string
// the string may have leading white space, followed by
// an optional +/- sign, and then valid characters
// for the base.  The conversion terminates whenever
// an invalid character is encountered or when we 
// reach the end of the string.
//
// base 2 to base 36
//
// the argument nptr is expected to be non-NULL 
//
long int str_to_long_int(const char *nptr, int base)
                   __attribute__((nonnull (1)));

#endif
