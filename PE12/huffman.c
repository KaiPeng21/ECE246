#include <stdio.h>
#include <stdlib.h>

#include "list_tree.h"
#include "huffman.h"

// return NULL if the tree cannot be constructed
// return the constructed huffman tree
//
// you should re-use the function written in PE11 if it is correct
//
int getNextBit(int ch, int bit_pos);
int sameFileSize(FILE *fptr, unsigned int fileSize);

tnode *Build_huffman_tree(FILE *infptr)
{
   fseek(infptr, 0, SEEK_SET);
   unsigned int fileSize;
   unsigned int headerSize;
   unsigned int numCharOrigin;
   int n = fread( &fileSize, sizeof(unsigned int), 1, infptr);
   n = fread( &headerSize, sizeof(unsigned int), 1, infptr);
   n = fread( &numCharOrigin, sizeof(unsigned int), 1, infptr);

   int check = sameFileSize(infptr, fileSize);
   if (check == 0){fprintf(stderr, "first 4 bytes did not indicate the actual filesize\n"); return NULL;}

   lnode stack;
   stack.next = NULL;
   set_stack_size(&stack, 0);

   int token;  // token to be read from the infptr

   tnode *tree;
   lnode *list;
   int ctBytesRead = 0;

   token = fgetc(infptr);
   fseek(infptr, -1, SEEK_CUR);
   while (token == '1' || token == '0') { // replace if necessary the correct condition
      token = fgetc(infptr); // get a character from the infptr

      ctBytesRead += sizeof(char);
      if (token == '1') {
        int c = fgetc(infptr);
        ctBytesRead += sizeof(char);
        tnode *left = NULL;
        tnode *right = NULL;
        tree = tree_construct(c, left, right);
        list = node_construct(tree);
        push(&stack, list);        
      } else if (token == '0' && stack_size(&stack) > 1) {
         lnode *poppedR = pop(&stack);
         if (poppedR == NULL){stack_flush(&stack); return NULL;}
         lnode *poppedL = pop(&stack);
         if (poppedL == NULL){free(poppedR); stack_flush(&stack); return NULL;}
         tnode *left_tree = poppedL->tree;
         tnode *right_tree = poppedR->tree;
         tree = tree_construct(0, left_tree, right_tree);
         list = node_construct(tree);
         push(&stack, list);
         free(poppedR);
         free(poppedL);
      } else {
         break;
      }
   }

   if (stack_size(&stack) != 1){  /*check if I have exactly 1 item on the stack*/
     stack_flush(&stack);
     fprintf(stderr, "more than 1 item in the stack\n");
     return NULL;
   }
   if (ctBytesRead != headerSize){ /*check if I have exhausted all bytes in the header region of the file*/
     stack_flush(&stack);
     fprintf(stderr, "not all bytes are exhausted\n");
     return NULL;
   }
   lnode *tmp = pop(&stack);
   tnode *ret_tree = tmp->tree;
   free(tmp);
   stack_flush(&stack);

   return ret_tree;
}

int sameFileSize(FILE *fptr, unsigned int fileSize){
  int ret;
  unsigned int pos = ftell(fptr);
  fseek(fptr, 0, SEEK_END);
  unsigned int size = ftell(fptr);
  if (size == fileSize){ret = 1;}
  else{ret = 0;}
  fseek(fptr, pos, SEEK_SET);
  return ret;
}


// if you successfully decode, return 1
// otherwise return 0
// The definition of success: the third unsigned integer specifies the 
// number of characters to be decoded.  If you decoded all characters as 
// specified and there are no more characters left in the encoded file
// for you to decode, it is a success.
//
// Even if decoding fails, whatever you have written into outfptr 
// should remain.  You just have to return 0.
//
int Huffman_decoding(tnode *huffman, FILE *infptr, FILE *outfptr)
{
   // first you should get the number of characters to be decoded
   // that number is the third unsigned int in the input file
   // you have to advance beyond the header section to access
   // the encoded data
   fseek(outfptr, 0, SEEK_SET);

   fseek(infptr, 0, SEEK_SET);
   unsigned int fileSize;
   unsigned int headerSize;
   unsigned int numChar;
   int n = fread(&fileSize, sizeof(unsigned int), 1, infptr);
   n = fread(&headerSize, sizeof(unsigned int), 1, infptr);
   n = fread(&numChar, sizeof(unsigned int), 1, infptr);

   int check = sameFileSize(infptr, fileSize);
   if (check == 0){fprintf(stderr, "first 4 bytes did not indicate the actual filesize\n"); return 0;}

   fseek(infptr, headerSize, SEEK_CUR);

   // you should have a tnode *curr that is first initialized 
   // to point to the root of the tree, i.e., huffman

   tnode *curr = huffman;   

   // now while the number of characters to be decoded 
   // is greater than 0, you iterate 
   
   int bit_pos = -1;
   int ch;
   while (numChar > 0) {  /* put in the right condition */
      // if curr is a leaf node
      // you have decoded one character
      // you should print that character, and decrement the number
      // of character to be decoded
      // reset curr to point to huffman
      if (is_leaf_node(curr)) {
         fputc(curr->value, outfptr);
         numChar--;
      
      
         curr = huffman; // restart
      } else {
         // decide on the next direction to go
         // get the next bit from the input file (from most significant 
         // position to the least significant in a byte) 
         // however, you can only read in byte-by-byte from a file
         // therefore, you probably need to have a variable to store
         // a byte read from the file and a variable to store the 
         // the position you are currently at in that byte
         // whenever you finish processing a bit, you should update
         // your position in the byte
         // you have to think of when you have to read in a new byte
         // and restart at the most significant position
         // of course, if you encounter end of file while the 
         // the number of characters to be decoded is still > 0, decoding
         // should fail
      
         if (bit_pos == -1){
           ch = fgetc(infptr);
           if (ch == EOF){break;}
           bit_pos = 7;
         }
            
      
      
         // if next bit is 0, go left, otherwise, go right
      
         int next_bit = getNextBit(ch, bit_pos); // you have to decide how to get the next bit
         bit_pos--;
         if (next_bit == 0) {
            curr = curr->left;
         } else {
            curr = curr->right;
         }
      }
   }
                                               

   // clean up at the end
   // have to decide whether you have successfully decoded 
   // all characters specified by the third unsigned int in the input file
   // decoded
   // 
   // if you want to check whether the input file has been corrupted
   // 1.  check that no more characters left in the input file to be decoded
   // 2.  all remaining bits in the char you are processing when you decoded
   // the last character are 0

   return 1;
}


int getNextBit(int ch, int bit_pos){
  return ((ch & (1 << bit_pos)) >> bit_pos);
}
