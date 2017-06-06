# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

# include "queue.h"
# include "huffman.h"
# include "stack.h"

treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes);


// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes)
{
	stack *decStack = newStack();
	printf("\n\nNode Format: symbol(leaf, count) Left symbol Right symbol\n");

	for (uint16_t i = 0; i < treeBytes; i++)  
	{  	
		// If L, push the next char node to the stack
		if(strncmp((char *)&savedTree[i],"L", 1) == 0)
		{
			i++;
			treeNode *node = newNode(savedTree[i], 1, 1);
			node->right = NULL;
			node->left = NULL;
			printf("Push %c(1, %llu)\n", node->symbol, node->count);
			push(decStack, node);

		}
		// If I, pop the top two nodes, join them, and push their root to the stack
		else if (strncmp((char *)&savedTree[i],"I", 1) == 0)
		{
			treeNode *right = pop(decStack);
			printf("Pop %c(%d, %llu)\n", right->symbol, right->leaf, right->count);
			treeNode *left = pop(decStack);
			printf("Pop %c(%d, %llu)\n", left->symbol, left->leaf, left->count);
			
			treeNode *nodeI = join(left, right);
			printTree(nodeI, 1);
			printf("Push %c(%d, %llu) Right %c(%llu) Left %c(%llu)\n", nodeI->symbol, nodeI->leaf, nodeI->count, nodeI->right->symbol, nodeI->right->count, nodeI->left->symbol, nodeI->left->count);
			push(decStack, nodeI);
		}
		
		//printf("Stack top = %d\n", decStack->top);
    }
	//printTree(&decStack->entries[dec->top], 1);
	return pop(decStack);
}



int main()	//int argc, char const *argv[])
{
	/*
	//char *in = NULL;
	int inputFile;
	char *out = NULL;

	int get;
	while ((get = getopt(argc, (char *const *)argv, "i:o:")) != -1)
	{
		switch (get)
      	{
      		case 'i': 								
				//in = optarg;     			
      			inputFile = open("optarg", O_RDONLY);
        	break;
      		case 'o':       		 								
				out = optarg;
        	break;
        	default: 
        		printf("DEFAULT CASE\n");
        	break;
        }
    } 
    */
    int inputFile = 0;
	inputFile = open("/Users/nat/Desktop/testCoded.txt", O_RDONLY);
	//inputFile = open("/afs/cats.ucsc.edu/users/g/narking/CS12B/narking/assignment4/testCoded.txt", O_RDONLY);
	if(inputFile == 0)
	{
		printf("INPUT FILE IS NULL\n");
	}

	/*
	int outFile = 0;
	outFile = open("/Users/nat/Desktop/out.txt", O_CREAT, S_IRWXG);
	if(outFile == 0)
	{
		printf("OUTPUT FILE IS NULL\n");
	}
	*/

    //Check magic number (first 4 bytes)
    uint32_t magicNum = 0xdeadd00d;
    uint32_t numCheck;
    read(inputFile, &numCheck, 4);

    if((magicNum & numCheck) != magicNum)
    {
    	printf("Error: Magic number not present\n");
    	return 0;
    }
    else
    {
    	printf("Success!! Valid magic number\n");
    }

    
    // Get file size (next 8 bytes)
    uint64_t fileSize;
    read(inputFile, &fileSize, 8);
    printf("File size = %llu bytes\n", fileSize);  						// <<<<<<< %lllu

    
    // Get tree size (next 2 bytes)
	uint16_t treeSize;
    read(inputFile, &treeSize, 2);
    printf("Tree size = %d bytes\n", treeSize);

    
    // Allocate and fill savedTree array (next [treeSize] bytes)
    uint8_t *savedTree = malloc(sizeof(uint8_t) * treeSize);
    if (savedTree == NULL)
		{
			printf("Error in savedTree malloc\n");
			return 0;
		}
    int count = read(inputFile, savedTree, treeSize);
    printf("Bytes = %d\n", count);
	
	
	// Load tree
    treeNode *mamaNode = loadTree(savedTree, treeSize);
    printf("mamaNode S = %c\n", mamaNode->symbol);
    printf("mamaNode C = %llu\n", mamaNode->count);
    //printTree(mamaNode, 1);

    printf("Root %c(%llu)\n", mamaNode->symbol, mamaNode->count);
    printf("L%c(%llu) R%c(%llu)\n", mamaNode->left->symbol, mamaNode->left->count, mamaNode->right->symbol, mamaNode->right->count);
    printf("LL%c(%llu) LR%c(%llu) ", mamaNode->left->left->symbol, mamaNode->left->left->count, mamaNode->left->right->symbol, mamaNode->left->right->count);
    printf("RL%c(%llu) RR%c(%llu)\n", mamaNode->right->left->symbol, mamaNode->right->left->count, mamaNode->right->right->symbol, mamaNode->right->right->count);
     //printf("LLL%c(%llu) LLR%c(%llu) ", mamaNode->left->left->left->symbol, mamaNode->left->left->left->count, mamaNode->left->right->symbol, mamaNode->left->left->right->count);
    printf("RRL%c(%llu) RRR%c(%llu)\n", mamaNode->right->right->left->symbol, mamaNode->right->right->left->count, mamaNode->right->right->right->symbol, mamaNode->right->right->right->count);
    printf("RRRL%c(%llu) RRRR%c(%llu)\n", mamaNode->right->right->right->left->symbol, mamaNode->right->right->right->left->count, mamaNode->right->right->right->symbol, mamaNode->right->right->right->count);
    

    

	return 0;
}


	

    // // Begin 
   	// treeNode *mamaNode = popT(decStk);


    /*
   
    uint8_t byteCheck = 0;
    uint64_t bytesRead = 0;
    treeNode * nodePtr = mamaNode;
    int saveIndex = 0;
    
    printf("Outside while\n");
    while(bytesRead < 20)
    {
    	printf("\n\n >>>>>>>>>>>While(%llu)\n", bytesRead);
    	read(inputFile, &byteCheck, 1);

	    for(int i = 0; i < 8; i++)
	    {
	    	if(saveIndex == 0)
	    	{
	    		printf("Reset\n");
	    		nodePtr = mamaNode;
	    		saveIndex = 1;
	    	}

	    	printf("Byte %d\n", i);
	    	printf("byteCheck = %d\n", byteCheck);
	    	uint8_t bitVal = byteCheck & (128 >> i);
	    	printf("bitVal = %d\n", bitVal);
	
	    	if (bitVal == 0)
	    	{
	    		printf("Move Left\n");
	    		nodePtr = nodePtr->left;

	    		if(nodePtr->leaf == 1)
	    		{
	    			printf("Leaf ");
	    			write(outFile, &nodePtr->symbol, 1);
	    			saveIndex = 0;
	    			printf("L = %hhu", nodePtr->symbol);
	    		}
	    		else
	    		{
	    			printf("I Node\n");
	    		}
	    	}
	    	else
	    	{
	    		printf("Move Right\n");
	    		nodePtr = nodePtr->right;

	    		if(nodePtr->leaf == 1)
	    		{
	    			printf("Leaf ");
	    			write(outFile, &nodePtr->symbol, 1);
	    			saveIndex = 0;
	    			printf("R = %hhu", nodePtr->symbol);
	    		}
	    		else
	    		{
	    			printf("I Node\n");
	    		}
	    	}
	    	printf("\n");
	    }
	    bytesRead++;
	}
	*/















/*

	// Print contents of a file
	int c = 0;
		FILE *file;
		file = fopen("/Users/nat/Desktop/secret.zzZ", "r");
		if (file) 
		{
			printf("File not null\n");
		    while ((c = getc(file)) != EOF)
	        	putchar(c);
		    fclose(file);
		}
		else
		{
			printf("File is null\n");
		}
*/


