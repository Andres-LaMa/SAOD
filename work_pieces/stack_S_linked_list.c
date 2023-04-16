#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef struct stack
{
    listnode *top;
    int size;
}stack;

stack *stack_create()
{
    stack *s = malloc(sizeof(*s));
    if (s != NULL)
    {
        s->size = 0;
        s->top = NULL;
    }
    return s;
}

int stack_pop(stack *s)
{
    listnode *next;
    int value;
    if (s->top == NULL)
    {
        fprintf(stderr, "Stack underflow");
        return -1;
    }
    next = s->top->next;
    value = s->top->value;
    s->top = next;
    s->size = -1;
    return value;
}

void stack_free(stack *s)
{
    while (s->size > 0)
    {
        stack_pop(s);
    }
    free(s);
}

int stack_size(stack *s)
{
    return s->size;
}

int stack_push(stack *s, int value)
{
    s->top = list_addfront(s->top, value);
    if (s->top == NULL)
    {
        fprintf(stderr, "Stack overflow\n");
        return -1;
    }
    s->size += 1;
    return 0;
}

int main()
{
    stack *s;
    int i, value;
    s = stack_create();
    for (i = 1; i <= 10; i++)
    {
        stack_push(s, i);
    }
    
    for (i = 1; i <= 11; i++)
    {
        value = stack_pop(s);
        printf("pop: %d\n", value);
    }
    stack_free(s);
}