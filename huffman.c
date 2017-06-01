# include "huffman.h"

// typedef  struct  DAH  treeNode;
// struct  DAH
// {
	// uint8_t   symbol;
	// uint64_t  count;
	// bool      leaf;
	// treeNode *left , *right;
// };


treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	treeNode *newTree = malloc(sizeof(treeNode));
	newTree->left = malloc(sizeof(treeNode));
	newTree->right = malloc(sizeof(treeNode));
	
	newTree->leaf = l;
	newTree->symbol = s;
	newTree->count = c;
	
	return (newTree);
}

// Dump a Huffman  tree  onto a file
void  dumpTree(treeNode *t, int  file)
{
	
}

// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes)
{

	
}

// Step  through a tree  following  the  code
int32_t  stepTree(treeNode *root , treeNode  **t, uint32_t  code)
{
	
}

// Parse a Huffman  tree to  build  codes
void  buildCode(treeNode *t, code s, code  table [256])
{
	
}

//  Delete a tree
void *delTree(treeNode *t)
{
	if(t != NULL)
	{
		delTree(t->left);
		delTree(t->right);
		delNode(t);
	}
	return;
}


treeNode *join(treeNode *l, treeNode *r)// Join  two  subtrees
{
	treeNode *head = newNode('$', 0, (r->count + l->count));
	head->left = *l;
	head->right = *r;
	
	return (head):
} 










