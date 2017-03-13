#include <stdio.h>
#include <stdlib.h>

#include "list_tree.h"
#include "huffman.h"


int getNextBit(int ch, int bit_pos);
int sameFileSize(FILE *fptr, unsigned int fileSize);

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



// return NULL if the tree cannot be constructed
// return the constructed huffman tree
//
// in general, the algorithm is the same as in PE11 and PE12, 
// except that you have character '0' or '1' to represent building
// a tree from two subtrees or building a tree for an ASCII character
// are now bit 0 or bit 1.  Consequently, as in the case of decoding,
// you have to process the header information using bits instead of
// bytes.  Note that when you have to build a tree for an ASCII character,
// the character may straddle two bytes.  Therefore, you have to combine
// some bits from two bytes to form an ASCII character.  Again, as in
// the case of decoding, we process the bits from a byte from the most
// significant position to the least significant position.
//
tnode *Build_huffman_tree(FILE *infptr)
{
   // you have to use to fseek to get to the right location of the file
   // to build the Huffman coding tree
   // First unsigned int in the file is the file size
   // second unsigned int is the header size
   // third unsigned int is the number of characters in the original file
   fseek(infptr, 0, SEEK_SET);
   unsigned int fileSize, headerSize, numChar;
   int n = fread(&fileSize, sizeof(unsigned int), 1, infptr);
   n = fread(&headerSize, sizeof(unsigned int), 1, infptr);
   n = fread(&numChar, sizeof(unsigned int), 1, infptr);

//   printf("%d\n", headerSize);

   int check = sameFileSize(infptr, fileSize);
   if (check == 0){fprintf(stderr, "first 4 bytes did not indicate the actual filesize\n"); return NULL;}
   

   // initialize the stack, here, we have a dummy called stack
   // the code in list_tree.c assumes the presence of a dummy
   // the size of the stack is 0

   lnode stack;
   stack.next = NULL;
   set_stack_size(&stack, 0);
   
   int token = 0;  // token to be read from the infptr
   int bytesRead = 0;   
   
   // while we are in the header region
   // break from the loop when you cannot continue to build a tree
   // e.g. encountering EOF, asked to build a tree from two trees
   // on the stack, but the stack contains 0 or 1 tree.
   int ch;
   int ascii;
   int bit_pos = -1;
   int i;
   tnode *tree;
   lnode *list;

   while (token == 0 || token == 1) { // replace if necessary the correct condition
      if (bit_pos == -1){
        ch = fgetc(infptr);
        bytesRead += sizeof(char);
        bit_pos = 7;
        if (ch == EOF){break;}
      }
      token = getNextBit(ch, bit_pos);
      bit_pos--;

      if (token == 1) {
	// what follows should be a character
        // read the character
        // build a tree that has a single tree node for that character
        // construct a list node with that tree node
        // push the list node onto the stack
        ascii = 0;
        for (i = 0; i < 8; i++){
          if (bit_pos == -1){
            ch = fgetc(infptr);
            bytesRead += sizeof(char);
            bit_pos = 7;
            if(ch == EOF){break;}
          }
          ascii = (ascii << 1) + getNextBit(ch, bit_pos);
          bit_pos--;
        }
        tnode *left = NULL;
        tnode *right = NULL;
        tree = tree_construct(ascii, left, right);
        list = node_construct(tree);
        push(&stack, list);
        


      
      } else if (token == 0 && stack_size(&stack) > 1) {  
         // You have to build a bigger tree from two trees in the list nodes
         // popped from the stack
         // After that, you have to push a list node containing the bigger
         // tree onto the stack
         // Beware of:  (1) You can do the construction if there are 
         // 2 or more items in the stack 
         // (2) which of the two trees popped from the stack
         // is left and which is right of the bigger tree
         // (3) cleaning up so that you do not leak memory
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
   if (bytesRead != headerSize){ /*check if I have exhausted all bytes in the header region of the file*/
     stack_flush(&stack);
     fprintf(stderr, "not all bytes are exhausted\n");
     return NULL;
   }
   lnode *tmp = pop(&stack);
   tnode *huffman = tmp->tree;
   free(tmp);
   stack_flush(&stack);


   // check for the conditions that says that you have successfully
   // constructed a huffman coding tree:
   // you have exhausted all bytes in the header region of the file
   // you have exactly 1 item on the stack
   // in that case, the constructed huffman is contained in the 
   // only list node on the stack, get it, and return the constructed tree
   // otherwise, return NULL
   // always clean up memory to avoid memory leak

   return huffman;
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
   unsigned int fileSize, headerSize, numChar;
   int n = fread(&fileSize, sizeof(unsigned int), 1, infptr);
   n = fread(&headerSize, sizeof(unsigned int), 1, infptr);
   n = fread(&numChar, sizeof(unsigned int), 1, infptr);

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

