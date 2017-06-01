# include "queue.h"


typedef  treeNode  item; //  treeNode  defined  in  huffman.h



queue *newQueue(uint32_t  size) //  Constructor
{
	queue *newQueue = malloc(sizeof(queue));
	newQueue->size = size;
	newQueue->head = 0;
	newQueue->tail = 0;
	newQueue->Q = malloc(sizeof(treeNode));
	
	return (newQueue);
}

void delQueue(queue *q)      //  Destructor
{
	free(q->Q);
	free(q);
}

bool  empty(queue *q)          // Is it empty?
{
	if(q->head == q->tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool full (queue *q)         // Is it full?
{
	if(((q->head + 1) % q->size) == ((q->tail) % q->size))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// typedef  struct  queue
// {
	// uint32_t  size;         // How big is it?
	// uint32_t  head , tail; //  Front  and  rear  locations
	// item *Q;                // Array to hold it (via  calloc)
// } queue;

bool enqueue(queue *q, treeNode i) // Add an item
{//from Darrell's code
	bool check = full(q);
	if(check == 0)//not full
	{
		q->Q[q->head] = i;
		q->head = (q->head +1) % q->size;
		return 1;
	}
	else
	{
		printf("queue full\n");
		return 0;
	}
}

bool dequeue(queue *q, treeNode *i) //  Remove  from  the  rear
{//from Darrell's code
	if (empty(q))
	{
		return false;
	}
	else
	{
		*i = q->Q[q->tail];
		q->tail = (q->tail + 1) % q->size;
		return true;
	}
}






















