#include <stdio.h>
#include <stdlib.h>

#include "list_tree.h"

// implement a stack with list
// list would always have a dummy header
// tree in dummy type-casted to store the size of stack (not counting the dummy)
//
void push(lnode *head, lnode *node) 
{
   node->next = head->next;
   head->next = node;
   set_stack_size(head, stack_size(head)+1);
}

// pop the first lnode in the stack
// decrement the size of stack
// if the stack is empty, return NULL;
//
lnode *pop(lnode *head)
{
   lnode *node = head->next;
   if (node != NULL) { // there is something in the stack
      head->next = node->next;
      node->next = NULL;
      set_stack_size(head, stack_size(head)-1);
   }
   return node;
}

// return the number of lnodes in the stack
//
int stack_size(lnode *head)
{
   int size = (unsigned long)(head->tree);
   return size;
}

// set the size of a stack, to be used only in push, pop, and flush, and
// to initialize the dummy at the beginning
//
void set_stack_size(lnode *head, int size)
{
   head->tree = (tnode *)((unsigned long)size);
}

// construct an lnode with tree, lnode->next should be NULL
//
lnode *node_construct(tnode *tree)
{
   lnode *node = (lnode *)malloc(sizeof(lnode));
   if (node == NULL) {
      return NULL;
   }
   node->tree = tree;
   node->next = NULL;
   return node;
}

// destroy a node, have to destroy the tree, then the node
//
void node_destruct(lnode *node)
{
   if (node != NULL) {
      tree_destruct(node->tree);
      free(node);
   }
}

// empty out the stack (except the dummy)
//
void stack_flush(lnode *head)
{
   lnode *curr = head->next;
   while (curr != NULL) {
      lnode *tmp = curr->next;
      node_destruct(curr);
      curr = tmp;
   }
   head->next = NULL;
   set_stack_size(head, 0);
}

// build a tnode with the left and right subtrees
//
tnode *tree_construct(int key, tnode *left, tnode *right)
{
   tnode *node = (tnode *)malloc(sizeof(tnode));
   if (node == NULL) {
      return NULL;
   }
   node->value = key;
   node->left = left;
   node->right = right;
   return node;
}

// destroy a tree, have to recursively destroy the left and right subtrees
//
void tree_destruct(tnode *node)
{
   if (node == NULL) {
      return;
   }
   tree_destruct(node->left);
   tree_destruct(node->right);
   free(node);
}

// check whether a tnode is a leaf node
//
int is_leaf_node(tnode *node)
{
   if (node != NULL) {
      if ((node->left == NULL) && (node->right == NULL)) {
         return 1;
      }
   }
   return 0;
}
