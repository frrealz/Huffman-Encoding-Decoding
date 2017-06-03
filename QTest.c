# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>

# include "queue.h"

# define MAX 10


/*
typedef struct treeNode treeNode;

struct treeNode
{
	uint8_t   symbol;
	uint64_t  count;
	bool      leaf;
	treeNode *left , *right;
};

typedef  struct  queue
{
	uint32_t  size;         	// How big is it?
	uint32_t  head , tail; 		// Front and rear locations
	treeNode *Q;                // Array of pointers to treenodes
} queue;

typedef treeNode item;
*/

int main()
{
	// The queue is meant to sort an array of pointers to tree nodes

	uint32_t count = 0;
	queue   *q     = newQueue(MAX);

	srand((long) time((time_t *) 0));
	do
	{
		uint32_t add = rand() % MAX;

		printf("Head = %u Tail = %u\n", q->head, q->tail);
		printf("Adding %u elements\n", add);

		for (uint32_t i = 0; i < add; i += 1)
		{
				if (full(q))
				{
						printf("Ouch! Full with only %u!\n", i);
						break;
				}
				else
				{
					treeNode *newTree = malloc(sizeof(treeNode));
					newTree->left = malloc(sizeof(treeNode));
					newTree->right = malloc(sizeof(treeNode));
					newTree->count = rand() % 1000;
					printf("\t%4llu", newTree->count);
					(void) enqueue(q, *newTree);
					count += 1;
				}
				printf("  H%u T%u\n", q->head, q->tail);
		}

		uint32_t pop = rand() % MAX;

		printf("Head = %u Tail = %u\n", q->head, q->tail);
		printf("Popping %u elements\n", pop);

		for (uint32_t i = 0; i < pop; i += 1)
		{
				if (empty(q))
				{
						printf("Woah! Empty after only %u!\n", i);
						break;
				}
				else
				{
					treeNode *newTree1 = malloc(sizeof(treeNode));
					//newTree1->left = malloc(sizeof(treeNode));
					//newTree1->right = malloc(sizeof(treeNode));
					(void) dequeue(q, newTree1);
					printf("\t%4llu", newTree1->count);
				}
				printf("  H%u T%u\n", q->head, q->tail);
		}
	} while (!empty(q));

	return 0;
}
