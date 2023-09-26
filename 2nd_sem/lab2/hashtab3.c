#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE 200003

typedef struct listnode
{
    char *key;
    int value;

    struct listnode *next;
}listnode;

void hashtab_init(listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}

unsigned int Ker_and_Rich_hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;

    while (*key)
    {
        h = h * hash_mul + (unsigned int)*key++;
    }
    return h % HASHTAB_SIZE;
}

unsigned int jenkins_hash(char *s)
{
    unsigned int hash = 0;
    while (*s)
    {
        hash += (unsigned int) * s++;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % HASHTAB_SIZE;
}

void Ker_and_Rich_hashtab_add(listnode **hashtab, char *key, int value, int *col)
{
    listnode *node;

    int index = Ker_and_Rich_hash(key);
    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        if (hashtab[index] != NULL)
        {
            *col += 1;
        }
        
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

void J_hashtab_add(listnode **hashtab, char *key, int value, int *col)
{
    listnode *node;

    int index = jenkins_hash(key);
    node = malloc(sizeof(*node));

    if (node != NULL)
    {
        if (hashtab[index] != NULL)
        {
            *col += 1;
        }
        
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

listnode *J_hashtab_lookup(listnode **hashtab, char *key)
{
    listnode *node;

    int index = jenkins_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(key, node->key) == 0)
        {
            return node;
        }
    }
    return NULL;
}

listnode *KP_hashtab_lookup(listnode **hashtab, char *key)
{
    listnode *node;

    int index = Ker_and_Rich_hash(key);
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
    int index = jenkins_hash(key);
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

void free_hashtab(listnode **hashtab)
{
    for (unsigned int i = 0; i < HASHTAB_SIZE; i++)
    {
        if (hashtab[i] == NULL)
        {
            continue;
        }
        while (hashtab[i]->next != NULL)
        {
            listnode *cp_l;
            cp_l = hashtab[i];
            hashtab[i] = hashtab[i]->next;
            free(cp_l);
        }
        free(hashtab[i]);
    }
    
}