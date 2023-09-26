#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE 13

typedef struct listnode
{
    char *key;
    int value;

    struct listnode *next;
}listnode;

unsigned int hashtab_hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;

    while (*key)
    {
        h = h * hash_mul + (unsigned int)*key++;
    }
    return h % 13;
}

void hashtab_init(listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}

void hashtab_add(listnode **hashtab, char *key, int value)
{
    listnode *node;

    int index = hashtab_hash(key);
    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

listnode *hashtab_lookup(listnode **hashtab, char *key)
{
    listnode *node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(key, node->key) == 0)
        {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(listnode **hashtab, char *key)
{
    listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(key, node->key) == 0)
        {
            if (prev == NULL)
            {
                hashtab[index] = node->next;
            }
            else
            {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
    
}
