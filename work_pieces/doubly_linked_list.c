#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct D_listnode
{
    char *key;
    struct D_listnode *next;
    struct D_listnode *prev;
}D_listnode;

D_listnode *list_createnode(char *key)
{
    D_listnode *node = malloc(sizeof(D_listnode));

    node->key = key;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

D_listnode *list_addfront(D_listnode *list, char *key)
{
    D_listnode *node = list_createnode(key);
    node->next = list;
    if (list != NULL)
    {
        list->prev = node;
    }
    return node;
}

D_listnode *list_addend(D_listnode *list, char *key)
{
    D_listnode *newnode = list_createnode(key);
    if (list == NULL)
    {
        return newnode;
    }
    D_listnode *node = list;
    while (node->next != NULL)
    {
        node = node->next;
    }
    node->next = newnode;
    newnode->prev = node;
    return list;
}

D_listnode *list_lookup(D_listnode *list, char *key) //почему-то не работает
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

D_listnode *list_delete(D_listnode *list, char *key)
{
    D_listnode *node = list;
    for (; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
        {
            if (node->prev == NULL)
            {
                list = node->next;
            }
            else
            {
                node->prev->next = node->next;
            }
            if (node->next != NULL)
            {
                node->next->prev = node->prev;
            }
            free(node);
            return list;
        }
    }
    return NULL;
}

int main(void)
{
    D_listnode *head, *node = NULL;

    head = list_addfront(NULL, "Lef");
    head = list_addend(head, "Fox");
    head = list_addfront(head, "Elephant");

    node = head;
    for (; node != NULL; node = node->next)
    {
        printf("Key: %s\n", node->key);
    }

    node = list_lookup(head, "Fox");
    if (node != NULL)
    {
        printf("Key: %s\n", node->key);
    }    
    return 0;
}