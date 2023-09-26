#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct S_listnode
{
    char *key;
    int value;
    struct S_listnode *next;
}S_listnode;

S_listnode *list_createnode(char *key, int value) //Singly_listnode
{
    S_listnode *p;

    p = malloc(sizeof(*p));
    if (p != NULL)
    {
        p->key = key;
        p->value = value;
        p->next = NULL;
    }
    return p;
}

S_listnode *list_addfront(S_listnode *list, char *key, int value)
{
    S_listnode *newnode;
    newnode = list_createnode(key, value);

    if (newnode != NULL)
    {
        newnode->next = list;
        return newnode;
    }
    return list;
}

S_listnode *list_lookup(S_listnode *list, char *key)
{
    for (; list != NULL; list = list->next)
    {
        if (strcmp(list->key, key) == 0)
        {
            return list;
        }
    }
    return NULL;
}

S_listnode *list_delete(S_listnode *list, char *key)
{
    S_listnode *p, *prev = NULL;

    for (p = list; p != NULL; p = p->next)
    {
        if (strcmp(p->key,key) == 0)
        {
            if (prev == NULL)
            {
                list = p->next;
            }
            else
            {
                prev->next = p->next;
            }
            free(p);
            return list;
        }
        prev = p;
    }
    return NULL;
}
