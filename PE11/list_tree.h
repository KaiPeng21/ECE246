#ifndef _LIST_TREE_H_
#define _LIST_TREE_H_

typedef struct _tnode {
   int value;
   struct _tnode *left;
   struct _tnode *right;
} tnode;

typedef struct _lnode {
   tnode *tree; 
   struct _lnode *next; 
} lnode;

// implement a stack with list
// list would always have a dummy header
// tree in dummy forced to store the size of stack

// push an lnode onto the stack
//
void push(lnode *head, lnode *node);

// pop the topmost lnode from the stack
// NULL if stack is empty
//
lnode *pop(lnode *head);

// get the size of a stack, i.e., the number of lnodes, not counting dummy
//
int stack_size(lnode *head);

// set the size of a stack, to be used only in push, pop, and flush, and
// to initialize the dummy at the beginning
//
void set_stack_size(lnode *head, int size);

// construct an lnode with tnode tree
//
lnode *node_construct(tnode *tree);

// destroy an lnode, including the tree stored in the lnode 
//
void node_destruct(lnode *node);

// called only if something went wrong to empty all items in stack
//
void stack_flush(lnode *head);

// functions related to tree
//
// construct a tnode with left and right subtrees
//
tnode *tree_construct(int key, tnode *left, tnode *right);

// destroy the tnode
// 
void tree_destruct(tnode *node);

// check whether a given tnode is a leaf node
//
int is_leaf_node(tnode *node);

#endif
