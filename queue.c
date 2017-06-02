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


// typedef  struct  DAH  treeNode;
// struct  DAH
// {
	// uint8_t   symbol;
	// uint64_t  count;
	// bool      leaf;
	// treeNode *left , *right;
// };

bool enqueue(queue *q, treeNode i) // Add an item
{
//right now we get a segmentation fault (try queue size = 20)
//when we reach the end of the queue
//I think it's not wrapping around?
	bool check = full(q);
	if(check == 0)//not full
	{
		//insertion sort
		if(q->head == q->tail)//if only one
		{
			q->Q[q->head] = i;
			q->head = (q->head +1) % q->size;
			return 1;
		}
		else
		{
			// for(uint32_t b = q->head; b != q->tail; b = ((b-1) % q->size))
			// {
				// if(i.count < q->Q[b].count)
				// {
					// q->Q[b+1] = q->Q[b];
				// }
				// else
				// {
					// break;
				// }
			// }
			// q->head = (q->head +1) % q->size;
			// return 1;

			for(uint32_t a = (q->tail); a != q->head; a = ((a+1) % q->size))
			{//transversal through list from tail to head
				if(i.count <= q->Q[a].count)		//if less than
				{
					for(uint32_t b = q->head; b != a; b = ((b-1) % q->size))
					{	//have to go backwards so no overwrite
						q->Q[b]= q->Q[(b-1)%q->size];		//shift array over
					}
					q->Q[a] = i;
					q->head = (q->head +1) % q->size;
					return 1;
				}
			}
			q->Q[q->head] = i;
			q->head = (q->head +1) % q->size;
			return 1;
		}
	}
	else
	{
		printf("queue full\n");
	}
	return 0;
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






















