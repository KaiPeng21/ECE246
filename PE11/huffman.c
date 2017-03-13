#include <stdio.h>
#include <stdlib.h>

#include "list_tree.h"
#include "huffman.h"


void postorder(tnode *curr, int *code, FILE *outfptr);
void putcode(int code, FILE *outfptr);
int calcDigit(int number);
int sameFileSize(FILE *fptr, unsigned int fileSize);
//int pow(int a, int n);
int checkNumChar(FILE * fptr, tnode *huffman);
int getNextBit(int ch, int bit_pos);

int getNextBit(int ch, int bit_pos){
  return ((ch & (1 << bit_pos)) >> bit_pos);
}


// return NULL if the tree cannot be constructed
// return the constructed huffman tree
// if you want to check for corruption of input file
// check whether you have fully exhausted all bytes in
// the header section to build the tree
//

tnode *Build_huffman_tree(FILE *infptr)
{
   // you have to use to fseek to get to the right location of the file
   // to build the Huffman coding tree
   // First unsigned int in the file is the file size
   // second unsigned int is the header size
   // third unsigned int is the number of characters in the original file
   fseek(infptr, 0, SEEK_SET);
   unsigned int fileSize;
   unsigned int headerSize;
   unsigned int numCharOrigin;
   int n = fread( &fileSize, sizeof(unsigned int), 1, infptr); 
   n = fread( &headerSize, sizeof(unsigned int), 1, infptr);
   n = fread( &numCharOrigin, sizeof(unsigned int), 1, infptr);

   int check = sameFileSize(infptr, fileSize);
   if (check == 0){fprintf(stderr, "first 4 bytes did not indicate the actual filesize\n"); return NULL;}

   // initialize the stack, here, we have a dummy called stack
   // the code in list_tree.c assumes the presence of a dummy
   // the size of the stack is 0

   lnode stack;
   stack.next = NULL;
   set_stack_size(&stack, 0);

   int token;  // token to be read from the infptr

   // while we are in the header region
   // break from the loop when you cannot continue to build a tree
   // e.g. encountering EOF, asked to build a tree from two trees
   // on the stack, but the stack contains 0 or 1 tree.



   tnode *tree;
   lnode *list;
   int ctBytesRead = 0;

   token = fgetc(infptr);
   fseek(infptr, -1, SEEK_CUR);
   while (token == '1' || token == '0') { // replace if necessary the correct condition
      token = fgetc(infptr); // get a character from the infptr

      ctBytesRead += sizeof(char);
      if (token == '1') {
	// what follows should be a character
        // read the character
        // build a tree that has a single tree node for that character
        // construct a list node with that tree node
        // push the list node onto the stack
        
        int c = fgetc(infptr);
        if (c == EOF){break;}
        ctBytesRead += sizeof(char);
        tnode *left = NULL;
        tnode *right = NULL;
        tree = tree_construct(c, left, right);
        list = node_construct(tree);
        push(&stack, list);
      
      } else if (token == '0' && stack_size(&stack) > 1) {  
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

   // check for the conditions that says that you have successfully
   // constructed a huffman coding tree:
   // you have exhausted all bytes in the header region of the file
   // you have exactly 1 item on the stack
   // in that case, the constructed huffman is contained in the 
   // only list node on the stack, get it, and return the constructed tree
   // otherwise, return NULL
   // always clean up memory to avoid memory leak
   


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

   check = checkNumChar(infptr, ret_tree);
   if (check == 0){
     fprintf(stderr, "number of character given is not the actual number of characters\n"); return NULL;
   }

   return ret_tree;
}

// suggest that you write a recursive function which is called
// by this function to print the huffman codes of the ascii characters
// that appear in the tree in postorder fashion
//
void Post_order_print(tnode *root, FILE *outfptr)
{
   fseek(outfptr, 0, SEEK_SET);
   int code = 2;
   postorder(root, &code, outfptr);

   return;
}

void postorder(tnode *curr, int *code, FILE *outfptr){
  if (curr == NULL){
    return;
  }
  if (curr->left != NULL){
    *code = *code * 10 + 0;
    postorder(curr->left, code, outfptr);
  }
  if (curr->right != NULL){
    *code = *code * 10 + 1;
    postorder(curr->right, code, outfptr);
  }
  if (curr->left == NULL && curr->right == NULL){
    fputc(curr->value, outfptr);
    fputc(':', outfptr);
    putcode(*code, outfptr);
    fputc('\n', outfptr);
  }
  *code /= 10;
}

void putcode(int code, FILE *outfptr){
  int digit = calcDigit(code);
  fseek(outfptr, digit-2, SEEK_CUR);
  while (code > 10){
    int c = code % 10;
    if (c == 1){ fputc('1', outfptr);}
    if (c == 0){ fputc('0', outfptr);}
    fseek(outfptr, -2, SEEK_CUR);
    code = code / 10;
  }
  fseek(outfptr, digit, SEEK_CUR);
}

int calcDigit(int number){
  int digit = 0;
  while (number > 0){
    digit++;
    number = number / 10;
  }
  return digit;
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


int checkNumChar(FILE * fptr, tnode *huffman){
  unsigned int original_pos = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  unsigned int fileSize, headerSize, numChar;
  int n = fread(&fileSize, sizeof(unsigned int), 1, fptr);
  n = fread(&headerSize, sizeof(unsigned int), 1, fptr);
  n = fread(&numChar, sizeof(unsigned int), 1, fptr);

  unsigned int ct = numChar;
  tnode * curr = huffman;
  int bit_pos = -1;

  int ch;
  while (ct > 0){
    if (is_leaf_node(curr)){
      curr = huffman;
      ct--;
    }else{
      if (bit_pos == -1){
        ch = fgetc(fptr);
        if (ch == EOF){break;}
        bit_pos = 7;
      }
      int next_bit = getNextBit(ch, bit_pos);
      if (next_bit == 1){curr = curr->right;}
      else{curr = curr->left;}
      bit_pos--;
    }
  } 
  fseek(fptr, original_pos, SEEK_SET);
  if (ct != 0){return 0;}
  return 1;
}
