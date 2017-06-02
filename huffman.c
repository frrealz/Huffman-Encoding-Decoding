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
	//just to test
	if(file)
	{
		
	}
	if(t)
	{
		
	}
	return;
}

// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes)
{
	//just to test
	treeNode *test = newNode(1, 0, 3);
	if(savedTree)
	{
		
	}
	if(treeBytes)
	{
		
	}
	return test;
	
}

// Step  through a tree  following  the  code
int32_t  stepTree(treeNode *root , treeNode  **t, uint32_t  code)
{
	//just to test
	if(root)
	{
		
	}
	if(t && code)
	{
		
	}
	return 3;
}

// Parse a Huffman  tree to  build  codes
void  buildCode(treeNode *t, uint32_t s, uint32_t table [256])
{
	//just to test
	if(s)
	{
		
	}
	if(table && t)
	{
		
	}
	return;
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
	return 0;
}


treeNode *join(treeNode *l, treeNode *r)// Join  two  subtrees
{
	treeNode *head = newNode('$', 1, (r->count + l->count));
	head->left = l;
	head->right = r;
	
	return (head);
} 


//from Darrell


void printTree(treeNode *t, int depth)
{
        if (t && t->leaf)
        {
                if (isalnum(t->symbol))
                {
                        spaces(4 * depth); printf("%c (%lu)\n", t->symbol, t->count);
                }
                else
                {
                        spaces(4 * depth); printf("%X (%lu)\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                spaces(4 * depth); printf("$ (%lu)\n", t->count);
                printTree(t->left, depth + 1);
                printTree(t->right, depth + 1);
        }
        return;
}






