# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>

# include "huffman.h"
# include "stack.h"


treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes);


int main(int argc, char const *argv[])
{
	char *in = NULL;
	char *out = NULL;

	int verbose = 0;
	int print = 0;
	int get;
	while ((get = getopt(argc, (char *const *)argv, "i:o::vp")) != -1)
	{
		switch (get)
      	{
      		case 'i': 								    			
      			in = optarg;
        	break;
      		case 'o':       		 								
			out = optarg;
        	break;
        	case 'v':       		 								
			verbose = 1;
        	break;
        	case 'p':       		 								
			print = 1;
        	break;
        	default: 
      
        	break;
        }
    } 
    

    // Prepare the input and output files
    int inputFile = 0;
	inputFile = open(in, O_RDONLY);
	if(inputFile == -1)
	{
		perror(in);
		exit(errno);
	}
	
	int outFile = 0;
	int oFlag = 0;
	if(out)
	{
		oFlag = 1;
		if(access(out, 0) != -1)
		{
			printf("./decode: %s:\n", out);
			printf("Failure: that file already exists\n"); 
			return 0;
		}
		else
		{
			printf("./decode: %s:\n", out);
			outFile = open(out, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if(outFile == -1)
			{
				printf("File creation error\n");
				return 0;
			}

		}
	}
	

    //Check magic number (first 4 bytes)
    uint32_t magicNum = 0xdeadd00d;
    uint32_t numCheck;
    read(inputFile, &numCheck, 4);

    if((magicNum & numCheck) != magicNum)
    {
    	printf("Error: Magic number not present\n");
    	return 0;
    }

    
    // Get file size (next 8 bytes)
    uint64_t fileSize;
    read(inputFile, &fileSize, 8);

    
    // Get tree size (next 2 bytes)
	uint16_t treeSize;
    read(inputFile, &treeSize, 2);

    
    // Allocate and fill savedTree array (next [treeSize] bytes)
    uint8_t *savedTree = malloc(sizeof(uint8_t) * treeSize);
    if (savedTree == NULL)
		{
			printf("Error in savedTree malloc\n");
			return 0;
		}
    read(inputFile, savedTree, treeSize);


    // Print verbose facts
    if(verbose == 1)
    {
    	printf("Original %lu bits: tree(%d)\n", (fileSize * 8), treeSize);
    }

	
	// Load tree
    treeNode *mamaNode = loadTree(savedTree, treeSize);

 

    // Decode the bits
	treeNode * nodePtr = mamaNode;
    uint8_t currentByte = 0;
    uint64_t bytesRead = 0;
    int saveIndex = 0;   

    uint32_t readCheck = 1;
    while(readCheck > 0)
    {
    readCheck = read(inputFile, &currentByte, 1);
	    
	    for(int i = 0; i < 8; i++)
	    {
	    	// Go back to the root if index not saved
	    	if(saveIndex == 0)
	    	{
	    		nodePtr = mamaNode;
	    		saveIndex = 1;
	    	}
			

	    	uint8_t bitVal = currentByte & (1 << i);
	    	if(bitVal != 0)
	    	{
	    		bitVal = 1;
	    	}
			
			// Once you print all the expected file characters...
			if(bytesRead >= fileSize)
	    	{
	    		// ...don't print the last dead bits
	    	}
	    	// If the bit is a 0, print the left
	    	else if (bitVal == 0)
	    	{
	    		nodePtr = nodePtr->left;

	    		if(nodePtr->leaf == 1)
	    		{
	    			if(oFlag == 1)
	    			{
	    				write(outFile, &(nodePtr->symbol), 1);
	    			}
	    			else
	    			{
	    				printf("%c", nodePtr->symbol);
	    			}
	    			bytesRead++;
	    			saveIndex = 0;
	    		}
	    	}
	    	// If the bit is a 1, print the right
	    	else
	    	{
	    		nodePtr = nodePtr->right;

	    		if(nodePtr->leaf == 1)
	    		{
	    			if(oFlag == 1)
	    			{
	    				write(outFile, &(nodePtr->symbol), 1);
	    			}
	    			else
	    			{
	    				printf("%c", nodePtr->symbol);
	    			}
	    			bytesRead++;
	    			saveIndex = 0;
	    		}
	    	}
	    }
	}


	if(oFlag)
	{
		printf("Success\n");
		close(outFile);
	}
	else
	{
		printf("\n");
	}
	close(inputFile);


	// Print tree (-p)
	if(print)
	{
		printTree(mamaNode, 1);
	}


	// Delete the tree
	delTree(mamaNode);

	return 0;
}


// Build a tree  from  the  saved  tree
treeNode *loadTree(uint8_t  savedTree [], uint16_t  treeBytes)
{
	stack *decStack = newStack();
	uint16_t i = 0;
	while(i < treeBytes)  
	{  	
		// If L, push the next char node to the stack
		if(strncmp((char *)&savedTree[i],"L", 1) == 0)										
		{
			i++;
			treeNode *node = newNode(savedTree[i], 1, 1);
			push(decStack, node);
			i++;

		}
		// If I, pop the top two nodes, join them, and push their root to the stack
		else if (strncmp((char *)&savedTree[i],"I", 1) == 0)								
		{
			if(decStack->top > 1)
			{
				treeNode *right = pop(decStack);
				treeNode *left = pop(decStack);
				
				treeNode *nodeI = join(left, right);
				push(decStack, nodeI);
				i++;
			}
			else
			{
				treeNode *right = pop(decStack);
				treeNode *nodeI = newNode(0x24, 0, right->count);
				nodeI->right = right;
			}
		}
    }
    treeNode *rootNode = pop(decStack);
    delStack(decStack);
	return rootNode;
}

