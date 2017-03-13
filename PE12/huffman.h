#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include "list_tree.h"

#define ASCII_COUNT 256

// functions below should be defined (written) by students

tnode *Build_huffman_tree(FILE *infptr);

int Huffman_decoding(tnode *huffman, FILE *infptr, FILE *outfptr);

// functions declared and defined by instructors

tnode *__Build_huffman_tree(FILE *infptr);

int __Huffman_decoding(tnode *huffman, FILE *infptr, FILE *outfptr);

#endif
