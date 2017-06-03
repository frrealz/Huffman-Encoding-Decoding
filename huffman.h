# include "huffman.h"

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
void  buildCode(treeNode *t, stack *s, uint32_t table [256])
{
	if (t && t->leaf)
	{
		uint32_t huffmanCharacterCode = 0;
		for(uint32_t i = 0 ; i < s->top; i++)
		{
			huffmanCharacterCode += (s->entries[i]) << i;	//creates character code
		}
		table[t->symbol] = huffmanCharacterCode;			//stores character code in appropriate place in array
	}
	else if (t)
	{
		push(s, 0);
		buildCode(t->left, s, table);				//left side
		
		pop(s);
		push(s, 1);
		buildCode(t->right, s, table);				//right side
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
	treeNode *head = newNode(0x24, 0, (r->count + l->count));
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






