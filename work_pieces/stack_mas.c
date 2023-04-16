#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int *a;
    int top;
    int size;
    int maxsize;
}stack;

stack *stack_create(int maxsize)
{
    stack *s = malloc(sizeof(*s));
    if (s != NULL)
    {
        s->a = malloc(sizeof(int) * maxsize);
        if (s->a == NULL)
        {
            free(s);
            return NULL;
        }
        s->size = 0;
        s->top = 0;
        s->maxsize = maxsize;
    }
    return s;
}

void stack_free(stack *s)
{
    free(s->a);
    free(s);
}

int stack_size(stack *s)
{
    return s->size;
}

int stack_push(stack *s, int value) //разобраться
{
    if (s->top < s->maxsize)
    {
        s->a[s->top + 1] = value;
        s->size += 1;
    }
    else
    {
        fprintf(stderr, "Stack overflow\n");
        return -1;
    }
    return 0;
}

int stack_pop(stack *s) //разобраться
{
    if (s->top == 0)
    {
        fprintf(stderr, "Stack underflow");
        return -1;
    }
    s->size -= 1;
    return s->a[--s->top];
}
