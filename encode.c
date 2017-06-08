# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <time.h>

# include "queue.h"
# include "huffman.h"
# include "code.h"

# define MAX 10




int main(int argc, char **argv)
{
	int verboseMode = 0;
	uint32_t magicNumber = 0xDEADD00D;
	
	uint32_t histogram[256] = {0};		//histogram
	for(int i = 0; i < 256; i++)		//initialize everything to 0
	{
		histogram[i] = 0;
	}
	
	char *inputFile = NULL;
	char *outputFile = NULL;
	int c;

	while ((c = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch(c)
		{
			case 'i':
			{
				inputFile = optarg;
				break;
			}
			case 'o':
			{
				outputFile = optarg;
				break;
			}
			case 'v':
			{
				verboseMode = 1;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	char buffer[1];
	int file;
	ssize_t size;
	uint64_t inputFileLength = 0;
	
	file = open(inputFile, O_RDONLY);
	if(file == -1)
	{
		perror(inputFile);
		exit(errno);
	}

	while( (size = read(file, buffer, 1)) > 0 )
	{
		uint8_t index = (int) buffer[0];
		histogram[ index ]++;
		//gets input file length
		inputFileLength++;
	}
	
	if (size == -1)									//error checking for read()
	{
		perror(inputFile);
		exit(errno);
	}
	histogram[0]++;
	histogram[255]++;
	
	//closes file
	size = close(file);
	if(size == -1)		
	{
		perror(inputFile);
		exit(errno);
	}
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//creating priority queue
	queue *priorityQueue = newQueue(300);
	
	
	for(int i = 0; i < 256; i++)
	{
		if(histogram[i] != 0)
		{
			//printf("%d\n", i);
			treeNode *newTree = newNode(i, 0, histogram[i]);	//new node for each item in histogram
			enqueue(priorityQueue, *newTree);							//puts each node in priority queue
			//printf("symbol: %x, count: %lu, leaf: %d\n", newTree->symbol, newTree->count, newTree->leaf);
		}
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	//trying to make huffman tree
	treeNode *root;
	while(abs(priorityQueue->head - priorityQueue->tail) != 1)	//until only one item left in queue, which is root
	{//joins two smallest items in queue
		
		treeNode *leaf0 = malloc(sizeof(treeNode));
		treeNode *leaf1 = malloc(sizeof(treeNode));
		
		dequeue(priorityQueue, leaf0);
		dequeue(priorityQueue, leaf1);


		// printf("symbol: %x, count: %lu, leaf: %d\n", leaf0->symbol, leaf0->count, leaf0->leaf);
		if(leaf0->symbol != 0x24)
		{
			leaf0->leaf = 1;
		}
		if(leaf1->symbol != 0x24)
		{
			leaf1->leaf = 1;
		}
		
		root = join(leaf0, leaf1);	//joins two leaf
		//debug
		// printf("HEAD symbol: %c, count: %lu, leaf: %d\n", root->symbol, root->count, root->leaf);
		// printf("RIGHT symbol: %c, count: %lu, leaf: %d\n", root->right->symbol, root->right->count, root->right->leaf);
		// printf("LEFT symbol: %c, count: %lu, leaf: %d\n", root->left->symbol, root->left->count, root->left->leaf);
		enqueue(priorityQueue, *root);
		
		//printf("symbol: %x, count: %lu, leaf: %d\n\n", priorityQueue->Q[3].symbol, priorityQueue->Q->count, priorityQueue->Q->leaf);
	}
		///////////////////////////////////////////////////////////////////////////////////////


	//delete priority Queue

	delTree(priorityQueue->Q);
	delQueue(priorityQueue);
	///////////////////////////////////////////////////////////////////////////////////////
	
	
	
	//printTree(root, 1);
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	//Make the code for each character
	code code = newCode();
	struct code codeTable[256];
	for(int i = 0; i < 256; i++)	//new code for each of 256 bits
	{
		codeTable[i] = newCode();
	}
	
	uint16_t leafCount = 0;
	buildCode(root, code, codeTable, &leafCount);
	
	
	// for(int i = 0; i < 256; i++)
	// {
		// if(codeTable[i].l != 0)
		// {
			// printf("symbol %c: %x, length: %u\n", i, codeTable[i].bits[0], codeTable[i].l);
		// }
	// }
	
	///////////////////////////////////////////////////////////////////////////////////////
	//write to output file


	
	uint16_t treeSize = 3*leafCount - 1;
	//printf("leafCount: %u\n", leafCount);
	
	
	int file1 = open(outputFile, O_WRONLY);

	if(file1 == -1)
	{
		perror(outputFile);
		exit(errno);
	}
	
	
	if(outputFile)	//writes to outputFile
	{
		write(file1, &magicNumber, 4);
		write(file1, &inputFileLength, 8);
		write(file1, &treeSize, 2);
		dumpTree(root, file1);
		//close(file);
		//fclose(filePointer);
	}
	else			//writes to standard output
	{
		// printf("%x\n", magicNumber);
		// printf("%lx\n", inputFileLength);
		// printf("%x\n", treeSize);
		write(1, &magicNumber, 4);
		write(1, &inputFileLength, 8);
		write(1, &treeSize, 2);
		dumpTree(root, 1);
	}
	
	delTree(root);
	

	
	file = open(inputFile, O_RDONLY);
	if(file == -1)
	{
		perror(inputFile);
		exit(errno);
	}
	
	uint64_t bitsEncoded = 0;
	uint8_t bitVector = 0;
	int j = 0;

	
	
	while( (size = read(file, buffer, 1)) > 0 )		//reads through file byte by byte
	{
		uint8_t index = (int) buffer[0];		//has value '0x0', '0x1', ... '0xFF'
		// printf("\ncode length: %u\n", codeTable[index].l);
		//for(int i = (codeTable[index].l-1); i >= 0  ; i--)			//reverse order of bits
		int max = codeTable[index].l;
		for(int i = 0; i < max ; i++)
		{
			int divisor = i;
			int bitVectorIndex = 0;				//chooses which array of bitvectors
			bitVectorIndex = divisor/32;				//works because takes floor of int division
			//if(codeTable[index].l != 91755790 && codeTable[index].l != 8388991)
			//printf("char: %x, bitVectorIndex: %d length %d, max: %u\n", buffer[0], bitVectorIndex, divisor, codeTable[index].l);
			if( ((codeTable[index].bits[bitVectorIndex] & (1<<i))<<i) == 0)		//clear bit
			{
				//printf("clear %uth bit\n", j);
				bitVector &= ~(0x01 << j);
				//printf("\nbitvector is: %x\n", bitVector);
			}
			else									//set bit
			{
				//printf("set %uth bit\n", j);
				bitVector |= (0x01 << j);
				//printf("\nbitvector is: %x\n", bitVector);
			}
			j++;
			bitsEncoded++;
			if(j == 8)			//if bitVector is full
			{
				if(outputFile)
				{
					//printf("\nbitvector is: %x\n", bitVector);
					write(file1, &bitVector, 1);
				}
				else
				{
					//printf("\nbitvector is: %x\n", bitVector);
					write(1, &bitVector, 1);
				}
				j = 0;		//reset j
				bitVector = 0;
			}			
		}
	}
	
	
	
	if(outputFile)			//prints out any remainder
	{
		write(file1, &bitVector, 1);
	}
	else
	{
		write(1, &bitVector, 1);
	}
	
	
	//closes file
	size = close(file);
	if(size == -1)		
	{
		perror(inputFile);
		exit(errno);
	}
	size = close(file1);
	if(size == -1)		
	{
		perror(inputFile);
		exit(errno);
	}
		

		
	if(verboseMode == 1)
	{
		printf("\nOriginal %lu bits: leaves %d (%u bytes) encoding %lu bits(%f%%)\n", inputFileLength*8, leafCount, treeSize, bitsEncoded, ((float)bitsEncoded*100/((float)inputFileLength*8)));
	}
	return 0;
}
