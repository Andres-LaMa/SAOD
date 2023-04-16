#include <stdio.h>

typedef struct listnode 
{
    int value;
    struct listnode *next;
}listnode;

listnode *list_createnode(int value) //Singly_listnode
{
    listnode *p;

    p = malloc(sizeof(*p));
    if (p != NULL)
    {
        p->value = value;
        p->next = NULL;
    }
    return p;
}

listnode *list_addfront(listnode *list, int value)
{
    listnode *newnode;
    newnode = list_createnode(value);

    if (newnode != NULL)
    {
        newnode->next = list;
        return newnode;
    }
    return list;
}
