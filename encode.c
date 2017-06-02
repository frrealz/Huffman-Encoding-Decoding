# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>



# include "queue.h"
# include "huffman.h"
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
	FILE *file;
	if(inputFile)
	{
		printf("tried to open\n\n");
		file = fopen(inputFile, "r");

	}
	if (file == NULL)
	{
        printf("Error Opening %s\n", inputFile);
    }
	else
	{
		fseek(file, SEEK_SET, 0);		//beginning of file
		while( fread(buffer, 1, 1, file) == 1 )
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
	queue *priorityQueue = newQueue(256);
	
	for(int i = 0; i < 256; i++)
	{
		if(histogram[i] != 0)
		{
			treeNode *newTree = newNode(i, 0, histogram[i]);	//new node for each item in histogram
			enqueue(priorityQueue, *newTree);							//puts each node in priority queue
		}
	}
	
	while(empty(priorityQueue) != 0)	//joins two smallest items in queue
	{
		treeNode *leaf0 = malloc(sizeof(treeNode));
		leaf0->left = malloc(sizeof(treeNode));
		leaf0->right = malloc(sizeof(treeNode));
		
		treeNode *leaf1 = malloc(sizeof(treeNode));
		leaf1->left = malloc(sizeof(treeNode));
		leaf1->right = malloc(sizeof(treeNode));
		
		dequeue(priorityQueue, leaf0);
		dequeue(priorityQueue, leaf1);
		leaf0->leaf = 1;
		leaf1->leaf = 1;
		
		treeNode *internalNode = join(leaf0, leaf1);	//joins two leaf
		// internalNode->symbol = '$';
		// internalNode->count = leaf0->count + leaf1->count;
		// internalNode->leaf = 0;
		
		enqueue(priorityQueue, *internalNode);
	}
	
	
	printTree(priorityQueue->Q, 4);
	
	
	
	
	
	
	
	
	
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

