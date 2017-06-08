# ifndef  _QUEUE_H
# define  _QUEUE_H
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"


// typedef struct treeNode treeNode;

// struct treeNode
// {
	// uint8_t   symbol;
	// uint64_t  count;
	// bool      leaf;
	// treeNode *left , *right;
// };

//  treeNode  defined  in  huffman.h


typedef  struct  queue
{
	uint32_t  size;         // How big is it?
	uint32_t  head , tail; //  Front  and  rear  locations
	treeNode *Q;                // Array to hold it (via  calloc)
} queue;

queue *newQueue(uint32_t  size); //  Constructor

void  delQueue(queue *q);       //  Destructor

bool  empty(queue *q);             // Is it empty?

bool  full (queue *q);             // Is it full?

bool  enqueue(queue *q, treeNode i); // Add an item

bool dequeue(queue *q, treeNode *i); //  Remove  from  the  rear
//treeNode *dequeue(queue *q); //  Remove  from  the  rear

# endif
