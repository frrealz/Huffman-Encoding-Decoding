# include "stack.h"

# define MIN_STACK 10

stack *newStack()
{
        stack *s = (stack *) calloc(MIN_STACK, sizeof(stack));
        s->size = MIN_STACK;
        s->top  = 0;
        s->entries = (treeNode **) calloc(MIN_STACK, sizeof(treeNode *));
        return s;
}

void delStack(stack *s) { free(s->entries); free(s); return; }

treeNode *pop(stack *s)
{
        if (s->top > 0)
        {
            s->top -= 1;
            return s->entries[s->top];
        }
        else
        {
            printf("Invalid in stack\n");
            return s->entries[s->top];
        }
}

void push(stack *s, treeNode *i)
{
        if (s->top == s->size)
        {
                s->size *= 2;
                s->entries = (treeNode **) realloc(s->entries, s->size * sizeof(treeNode *));
        }
        s->entries[s->top] = i;
        s->top += 1;
        return;

}

bool emptyS(stack *s)
{
    return (s->top == 0);
}


