# include "huffman.h"


// Create a new treeNode
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
		else		// Writes to file
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
		if(file == -1)		// Writes to standard output
		{
			
			dumpTree(t->left, file);
			dumpTree(t->right, file);
			write(1, "I", 1);
		}
		else		// Writes to file
		{
			
			dumpTree(t->left, file);
			dumpTree(t->right, file);
			write(file, "I", 1);
		}
	}
	return;
}



// Parse a Huffman  tree to  build  codes
void  buildCode(treeNode *t, code s, code table[256], uint16_t *leafCount)
{
	if (t && t->leaf)
	{
		(*leafCount)++;		// Increments how many leaves
		table[t->symbol] = s;
	}
	else if (t)
	{
		pushCode(&s, 0);
		buildCode(t->left, s, table, leafCount);				// Left side
		uint32_t pop = 2;
		popCode(&s, &pop);
		pushCode(&s, 1);
		buildCode(t->right, s, table, leafCount);				// Right side
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


// Join  two  subtrees
treeNode *join(treeNode *l, treeNode *r)
{
	treeNode *head = newNode(0x24, 0, (r->count + l->count));
	head->left = l;
	head->right = r;
	
	return (head);
} 


// From Darrell
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



