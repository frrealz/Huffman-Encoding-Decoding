# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "stack.h"

# define MIN_STACK 10

stack *newStack()
{
        stack *s = (stack *) calloc(MIN_STACK, sizeof(stack));
        s->size = MIN_STACK;
        s->top  = 0;
        s->entries = (int *) calloc(MIN_STACK, sizeof(int));
        return s;
}

void delStack(stack *s) { free(s->entries); free(s); return; }

int pop(stack *s)
{
        if (s->top > 0)
        {
            s->top -= 1;
            return s->entries[s->top];
        }
        else
        {
			printf("invalid in stack\n");
            return 0;
        }
}

void push(stack *s, int i)
{
        if (s->top == s->size)
        {
                s->size *= 2;
                s->entries = (int *) realloc(s->entries, s->size * sizeof(int));
        }
        s->entries[s->top] = i;
        s->top += 1;
        return;

}

bool emptyS(stack *s)
{
	return (s->top == 0);
}
