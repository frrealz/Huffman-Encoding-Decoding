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
	inputFile = open("/Users/nat/Desktop/secret.zzZ", O_RDONLY);
	//inputFile = open("/afs/cats.ucsc.edu/users/g/darrell/secret.zzZ", O_RDONLY);
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
    printf("File size = %llu bytes\n", fileSize);  						// <<<<<<< %llu

    
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
    //printTree(mamaNode, 1);

    // // Begin 
   	// treeNode *mamaNode = popT(decStk);
   

    // printf("Mama:	Right = %c Left = %c\n", mamaNode->right->symbol, mamaNode->left->symbol);
    // treeNode *tempR1 = mamaNode->right;
    // treeNode *tempL1 = mamaNode->left;
    // printf("R1:	Right = %c Left = %c\n", tempR1->right->symbol, tempR1->left->symbol);
    // printf("L1:	Right = %c Left = %c\n", tempL1->right->symbol, tempL1->left->symbol);

    // printTree(mamaNode, 20);


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

	return 0;
}


/*
LeLhLsIILlLdILnILaLpL,ILjLBIL_LXL*L?IL?LL^IL?L?IIIILQIIL+IIL7ILCIIL[
L]IIL?L8ILSILxIL3L"ILMLDIL-IIIILwIIIIILiLoILfLkLPLWIL(IL)L2IIILvIILmL
LcILGL6L?LOIIILAIL'LHIL:IL5LqILULzILJL!LKL?L?IL?L?IIL?L?IL?L?IIIIIL&
LYILZIIIIL?IIIILbILuIILrL.L;LFLEIL9LVL?IIL4IIILTL1IL0LNILRLLIILIIIII
LyLgIIIIL III
*/

// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes)
{
	stack *decStack = newStack();

	for (uint16_t i = 0; i < treeBytes; i++)  
	{  	
		if(strncmp((char *)&savedTree[i],"L", 1) == 0)
		{
			i++;
			treeNode *node = newNode(savedTree[i], 1, 0);
			printf("L%c ", node->symbol);
			push(decStack, node);

		}
		else if (strncmp((char *)&savedTree[i],"I", 1) == 0)
		{
			printf("-->I ");
			treeNode *right = pop(decStack);
			printf("R%c ", right->symbol);
			treeNode *left = pop(decStack);
			printf("L%c ", left->symbol);
			treeNode *nodeI = join(left, right);
			printf("I Right %c Left %c\n", nodeI->right->symbol, nodeI->left->symbol);
			push(decStack, nodeI);
		}
		//printf("Stack top = %d\n", decStack->top);
    }
	
	return pop(decStack);
}













/*
    //Prepare input file
    FILE *inputFile;
    if(in == NULL)
    {
    	printf("Failure to open file\n");
    	return 0;
    }
    inputFile = fopen(in, "r");

    //Prepare output file
    FILE *outputFile;
    if(out == NULL)
    {
    	printf("Failure to open file\n");
    	return 0;
    }
    outputFile = fopen(out, "r");

    int c;
	FILE *file;
	file = fopen("/afs/cats.ucsc.edu/users/g/darrell/secret.zzZ", "r");
	if (file) 
	{
	    while ((c = getc(file)) != EOF)
	    putchar(c);
	    fclose(file);
	}
	else
	{
		printf("File is null\n");
	}


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


