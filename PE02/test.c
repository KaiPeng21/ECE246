#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>


int charToInt(char c);

int main (void)
{
  char const *ntpr = '2';
  
  printf("%d", charToInt(ntpr));
  return 0;
}

int charToInt(char c)
{
  int retVal = -1;
  if (isdigit(c))
  {
    retVal = c - 48;
  }
  else if (isupper(c))
  {
    retVal = c - 55;
  }
  else if (islower(c))
  {
    retVal = c - 87;
  }
  return retVal;
}
