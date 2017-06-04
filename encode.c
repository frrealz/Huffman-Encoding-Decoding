# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>


# include "queue.h"
# include "huffman.h"
# include "code.h"

# define MAX 10
# include <time.h>


int main(int argc, char **argv)
{
	uint32_t histogram[256] = {0};		//histogram
	for(int i = 0; i < 256; i++)		//initialize everything to 0
	{
		histogram[i] = 0;
	}
	
	char *inputFile = NULL;
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
				break;
			}
			case 'v':
			{
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
	if(inputFile)
	{
		printf("tried to open\n\n");
		file = open(inputFile, O_RDONLY);

	}
	if (file == -1)
	{
		perror(inputFile);
		exit(errno);
        printf("Error Opening %s\n", inputFile);
    }
	else
	{
		while( read(file, buffer, 1) == 1 )
		{
			int index = (int) buffer[0];
			histogram[ index ]++;
		}
		histogram[0]++;
		histogram[255]++;
	}

	
	
	// for(int i = 0; i < 256; i++)
	// {
		// printf("%d: %u\n", i, histogram[i]);
	// }		
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//creating priority queue
	queue *priorityQueue = newQueue(10000);
	
	for(int i = 0; i < 256; i++)
	{
		if(histogram[i] != 0)
		{
			///printf("%d\n", i);
			treeNode *newTree = newNode(i, 0, histogram[i]);	//new node for each item in histogram
			enqueue(priorityQueue, *newTree);							//puts each node in priority queue
			//printf("symbol: %x, count: %lu, leaf: %d\n", newTree->symbol, newTree->count, newTree->leaf);
		}
	}
	printf("\n");
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	//trying to make huffman tree
	treeNode *root = newNode('$', 0, 0);
	while(abs(priorityQueue->head - priorityQueue->tail) != 1)	//until only one item left in queue, which is root
	{//joins two smallest items in queue
		treeNode *leaf0 = malloc(sizeof(treeNode));
		leaf0->left = malloc(sizeof(treeNode));
		leaf0->right = malloc(sizeof(treeNode));
		
		treeNode *leaf1 = malloc(sizeof(treeNode));
		leaf1->left = malloc(sizeof(treeNode));
		leaf1->right = malloc(sizeof(treeNode));
		
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
		
		treeNode *internalNode = join(leaf0, leaf1);	//joins two leaf
		//debug
		// printf("HEAD symbol: %x, count: %lu, leaf: %d\n", internalNode->symbol, internalNode->count, internalNode->leaf);
		// printf("RIGHT symbol: %x, count: %lu, leaf: %d\n", internalNode->right->symbol, internalNode->right->count, internalNode->right->leaf);
		// printf("LEFT symbol: %x, count: %lu, leaf: %d\n", internalNode->left->symbol, internalNode->left->count, internalNode->left->leaf);
		enqueue(priorityQueue, *internalNode);
		
		//printf("symbol: %x, count: %lu, leaf: %d\n\n", priorityQueue->Q[3].symbol, priorityQueue->Q->count, priorityQueue->Q->leaf);
		if(abs(priorityQueue->head - priorityQueue->tail) == 1)//set root when only one item left in queue
		{
			*root = *internalNode;
		}
	}
	
	//delete priority Queue
	delQueue(priorityQueue);
	///////////////////////////////////////////////////////////////////////////////////////
	
	
	
	printTree(root, 1);
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	//Make the code for each character
	code code = newCode();
	struct code codeTable[256];
	for(int i = 0; i < 256; i++)	//new code for each of 256 bits
	{
		codeTable[i] = newCode();
	}
	

	buildCode(root, code, codeTable);
	
	
	for(int i = 0; i < 256; i++)
	{
		if(codeTable[i].l != 0)
		{

			//printf("symbol %c: %x, length: %u\n", i, codeTable[i].bits[0], codeTable[i].l);
		}
		
		
	}
	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	//dequeue to test to see if huffman tree works
	
	// do
		// {
		
		// printf("head: %u\n", priorityQueue->head);
		// printf("tail: %u\n", priorityQueue->tail);
			// uint32_t pop = 100000;
			// printf("Popping %u elements\n", pop);
			// for (uint32_t i = 0; i < pop; i += 1)
			// {
					// if (empty(priorityQueue))
					// {
							// printf("Woah! Empty after only %u!\n", i);
							// break;
					// }
					// else
					// {
						// treeNode *newTree1 = malloc(sizeof(treeNode));
						// newTree1->left = malloc(sizeof(treeNode));
						// newTree1->right = malloc(sizeof(treeNode));
							// (void) dequeue(priorityQueue, newTree1);
							// printf("\t%4lu\n", newTree1->count);
					// }
			// }
	// } while (!empty(priorityQueue));


	
	
	//printTree(priorityQueue->Q, 1);
	
	
	// printf("symbol: %x, count: %lu, leaf: %d\n", priorityQueue->Q->symbol, priorityQueue->Q->count, priorityQueue->Q->leaf);
	// printf("symbol: %x, count: %lu, leaf: %d\n", 
	// priorityQueue->Q->left->symbol, priorityQueue->Q->left->count, priorityQueue->Q->left->leaf);
	// printf("symbol: %x, count: %lu, leaf: %d\n", 
	// priorityQueue->Q->right->symbol, priorityQueue->Q->right->count, priorityQueue->Q->right->leaf);
	// printTree(internalNode, 1);
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	////////////////////////////////////////////////////////////////////////////////
	//Testing queue
	// uint32_t count = 0;
	// queue   *q     = newQueue(2 * MAX);

	// srandom((long) time((time_t *) 0));
	// do
	// {
			// uint32_t add = random() % MAX;
		// printf("head: %u\n", q->head);
		// printf("tail: %u\n", q->tail);
			// printf("Adding %u elements\n", add);
			// for (uint32_t i = 0; i < add; i += 1)
			// {
					// if (full(q))
					// {
							// printf("Ouch! Full with only %u!\n", i);
							// break;
					// }
					// else
					// {
						// treeNode *newTree = malloc(sizeof(treeNode));
						// newTree->left = malloc(sizeof(treeNode));
						// newTree->right = malloc(sizeof(treeNode));
							// newTree->count = random() % 1000;
							// printf("\t%4lu\n", newTree->count);
							// (void) enqueue(q, *newTree);
							// count += 1;
					// }
			// }

			// uint32_t pop = random() % MAX;
		// printf("head: %u\n", q->head);
		// printf("tail: %u\n", q->tail);
			// printf("Popping %u elements\n", pop);
			// for (uint32_t i = 0; i < pop; i += 1)
			// {
					// if (empty(q))
					// {
							// printf("Woah! Empty after only %u!\n", i);
							// break;
					// }
					// else
					// {
						// treeNode *newTree1 = malloc(sizeof(treeNode));
						// newTree1->left = malloc(sizeof(treeNode));
						// newTree1->right = malloc(sizeof(treeNode));
							// (void) dequeue(q, newTree1);
							// printf("\t%4lu\n", newTree1->count);
					// }
			// }
	// } while (!empty(q));

	

	
	
	
	
	
	
	
	return 0;
}

