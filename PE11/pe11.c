#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "list_tree.h"

int main(int argc, char *argv[])
{
  if (argc < 3){
    fprintf(stderr, "Insufficient argument\n");
    return EXIT_FAILURE;
  }
  FILE * infptr = fopen(argv[1], "r");
  if (infptr == NULL){
    fprintf(stderr, "Error reading input file\n");
    return EXIT_FAILURE;
  }
  FILE * outfptr = NULL;
  outfptr = fopen(argv[2], "w");
  if (outfptr == NULL){
    fprintf(stderr, "Error writing to output file\n");
    fclose(infptr);
    return EXIT_FAILURE;
  }

  tnode *tree = Build_huffman_tree(infptr);
  if (tree == NULL){
    fprintf(stderr, "Error constructing hufman tree\n");
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }
  Post_order_print(tree, outfptr); 

  tree_destruct(tree);
  fclose(infptr);
  fclose(outfptr);  
  return EXIT_SUCCESS;
}
