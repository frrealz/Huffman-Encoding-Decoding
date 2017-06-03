//from Darrell
# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

typedef struct stack
{
        uint32_t size;
        uint32_t top;
        int *entries;
} stack;


stack *newStack();

void delStack(stack *);

int pop(stack *);

void push(stack *, int);

bool emptyS(stack *);


# endif
