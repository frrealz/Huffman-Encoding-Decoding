# ifndef  _QUEUE_H
# define  _QUEUE_H
# include  <stdint.h>
# include  <stdbool.h>

typedef  treeNode  item; //  treeNode  defined  in  huffman.h
typedef  struct  queue
{
	uint32_t  size;         // How big is it?
	uint32_t  head , tail; //  Front  and  rear  locations
	item *Q;                // Array to hold it (via  calloc)
} queue;

queue *newQueue(uint32_t  size); //  Constructor

void    delQueue(queue *q);       //  Destructor

bool  empty(queue *q);             // Is it empty?

bool  full (queue *q);             // Is it full?

bool  enqueue(queue *q, item   i); // Add an item

bool  dequeue(queue *q, item *i); //  Remove  from  the  rear

# endif
