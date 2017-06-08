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
void  dumpTree(treeNode *t, int file)
{
	if (t && t->leaf)
	{	
		if(file == -1)		//writes to standard output
		{
			write(1, "L", 1);
			if(write(1, &t->symbol, 1) != 1)
			{
				printf("error copying tree into file\n");
				return;
			}
		}
		else		//writes to file
		{
			write(file, "L", 1);
			if(write(file, &t->symbol, 1) != 1)
			{
				printf("error copying tree into file\n");
				return;
			}
		}
	}
	else if (t)
	{
		if(file == -1)		//writes to standard output
		{
			
			dumpTree(t->left, file);
			dumpTree(t->right, file);
			write(1, "I", 1);
		}
		else		//writes to file
		{
			
			dumpTree(t->left, file);
			dumpTree(t->right, file);
			write(file, "I", 1);
		}
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
void  buildCode(treeNode *t, code s, code table[256], uint16_t *leafCount)
{
	if (t && t->leaf)
	{
		(*leafCount)++;		//increments how many leaves
		//printf("symbol: %c, code: %u, length: %u\n", t->symbol, s.bits[0], s.l);
		table[t->symbol] = s;
		
		//so you only get correct codes if you print in reverse
		//printf("symbol %c: %x, length: %u\n", t->symbol, s.bits[0], s.l);
	}
	else if (t)
	{
		pushCode(&s, 0);
		buildCode(t->left, s, table, leafCount);				//left side
		uint32_t pop = 2;
		popCode(&s, &pop);
		pushCode(&s, 1);
		buildCode(t->right, s, table, leafCount);				//right side
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






