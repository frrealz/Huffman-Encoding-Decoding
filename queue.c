# include "queue.h"


typedef  treeNode  item; // treeNode defined in huffman.h


// Constructor
queue *newQueue(uint32_t  size) 
{
	queue *newQ = malloc(sizeof(queue));
	newQ->size = size;
	newQ->head = 0;
	newQ->tail = 0;
	
	return (newQ);
}

// Destructor
void delQueue(queue *q)      
{
	free(q->Q);
	free(q);
}

// Check for empty
bool  empty(queue *q)          
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

// Check for full
bool full (queue *q)        
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


// Add an item to the queue
/*
Seg fault solved
 - Issue was when going backwards while head == 0
 - Cannot modulo in reverse (-1 % q->size)
New issue: won't check over gap when comparing counts
 - Will pick numbers in order if looped over gap
 */
bool enqueue(queue *q, treeNode i)
{
	// Check if full
	if(full(q) == 0)
	{
		// Insertion sort
		if(q->head == q->tail)//if only one
		{
			q->Q[q->head] = i;
			q->head = (q->head +1) % q->size;
			return 1;
		}
		else
		{
			// Transversal through list from tail to head
			for(uint32_t a = (q->tail); a != q->head; a = ((a+1) % q->size))
			{
				// Compare counts of queue items
				if(i.count <= q->Q[a].count)		
				{
					// Traverse backwards to avoid overwrite
					uint32_t b = q->head;

					while(b != a)
					{
						// If head is 0, skip to the other end
						if(b == 0)
						{
							// Shift array over to other end
							q->Q[b]= q->Q[q->size];
							b = q->size;
						}
						else
						{
							// Shift array over
							q->Q[b]= q->Q[b-1];	
							b--;
						}
					}
					// Insert item
					q->Q[a] = i;
					q->head = (q->head +1) % q->size;
					return 1;
				}
			}
			// Insert item
			q->Q[q->head] = i;
			q->head = (q->head +1) % q->size;
			return 1;
		}
	}
	else
	{
		printf("Queue is full\n");
	}
	return 0;
}

// Remove from the rear
bool dequeue(queue *q, treeNode *i) 
{
	// From Darrell's code
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



