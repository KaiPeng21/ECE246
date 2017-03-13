#include <stdio.h>
#include <stdlib.h>
#include "pa_answer02.h"

int main(int argc, char *argv[])
{
  if (argc < 2){
    fprintf(stderr, "Insufficient arguments.\n");
    return EXIT_FAILURE;
  }

  if (argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == '\0'){
    if (argc < 5){
      fprintf(stderr, "Insufficient arguments. Expected 3 files followed by -s.\n");
      return EXIT_FAILURE;
    }
    int ret = Simulate_mowing(argv[2], argv[3], argv[4]);
    printf("%d\n", ret); 
  }
  else if (argv[1][0] == '-' && argv[1][1] == 'm' && argv[1][2] == '\0'){
    if (argc < 4){
      fprintf(stderr, "Insufficient arguments. Expect 2 files followed by -m.\n");
      return EXIT_FAILURE;
    }
    Get_mowing_directions(argv[2], argv[3]);
  }
  else{
    fprintf(stderr, "Invalid argv[1].\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
