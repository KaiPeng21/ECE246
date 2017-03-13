#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "list_tree.h"


int main(int argc, char *argv[]){
  if (argc < 3){
    fprintf(stderr, "Insufficient argument\n");
    return EXIT_FAILURE;
  }
  FILE * infptr = fopen(argv[1], "r");
  if (infptr == NULL){
    fprintf(stderr, "Error reading input file\n");
    return EXIT_FAILURE;
  }
  FILE * outfptr = fopen(argv[2], "w");
  if (outfptr == NULL){
    fprintf(stderr, "Error writing output file\n");
    fclose(infptr);
    return EXIT_FAILURE;
  }
 
  tnode * huffman = Build_huffman_tree(infptr);
  if (huffman == NULL){
    fprintf(stderr, "Error building huffman tree\n");
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }

  int check = Huffman_decoding(huffman, infptr, outfptr);
  if (check == 0){
    fprintf(stderr, "Error decoding uffman tree\n");
    tree_destruct(huffman);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_FAILURE;
  }

  tree_destruct(huffman); 
  fclose(infptr);
  fclose(outfptr);
  return EXIT_SUCCESS;
}
