#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "bstree.h"

#define SIZE 10

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long double)t.tv_sec + (long double)t.tv_usec * 1E-6;
}

int main(int arg, char *argv[])
{
    FILE *f;
    bstree *tree;
    char words[SIZE][15];

    f = fopen(argv[1], "rb");
    for (int i = 1; i <= SIZE; i++)
        fscanf(f, "%s", words[i - 1]);

    tree = bstree_create(words[0], 0);

    for (int i = 1; i <= SIZE; i ++)
    {
        bstree_add(tree, words[i - 1], i - 1);
    }
    
    print_tree(tree, 1, 64);
    tree = delete(tree, "moorfowl");
    printf("\n\n\n");
    print_tree(tree, 1, 64);
    free_bstree(tree);
    fclose(f);
    return 0;
}