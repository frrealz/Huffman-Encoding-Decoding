# ifndef  _HUFFMAN_H
# define  _HUFFMAN_H
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <ctype.h>

# include "stack.h"

# ifndef  NIL
# define  NIL (void *) 0
# endif

typedef  struct  treeNode  treeNode;
struct  treeNode
{
	uint8_t   symbol;
	uint64_t  count;
	bool      leaf;
	treeNode *left , *right;
};

// New node , with  symbols , leaf or not , a count  associated  with it
treeNode *newNode(uint8_t s, bool l, uint64_t c);

// Dump a Huffman  tree  onto a file
void  dumpTree(treeNode *t, int  file);

// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes);

// Step  through a tree  following  the  code
int32_t  stepTree(treeNode *root , treeNode  **t, uint32_t  code);

// Parse a Huffman  tree to  build  codes
void  buildCode(treeNode *t, stack *s, uint32_t  table [256]);

//  Delete a tree
void *delTree(treeNode *t);

static  inline  void  delNode(treeNode *h) { free(h); return; }

static  inline  int8_t  compare(treeNode *l, treeNode *r)
{
	return l->count - r->count; // l < r if negative , l = r if 0, ...
}

treeNode *join(treeNode *l, treeNode *r); // Join  two  subtrees

//from Darrell
static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

void printTree(treeNode *t, int depth);
# endif
