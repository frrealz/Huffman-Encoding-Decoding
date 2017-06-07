# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef struct stack
{
        uint32_t size;
        uint32_t top;
        treeNode **entries;
} stack;

stack *newStack();

void delStack(stack *);

treeNode *pop(stack *);

void push(stack *, treeNode *i);

bool emptyS(stack *);

#endif

