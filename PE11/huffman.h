#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include "list_tree.h"

#define ASCII_COUNT 256

// functions below should be defined (written) by students

tnode *Build_huffman_tree(FILE *infptr);

void Post_order_print(tnode *root, FILE *outfptr);

// functions declared and defined by instructors

tnode *__Build_huffman_tree(FILE *infptr);

void __Post_order_print(tnode *root, FILE *outfptr);

#endif
