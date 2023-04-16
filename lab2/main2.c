#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "bstree.h"
#include "hashtab.h"

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long double)t.tv_sec + (long double)t.tv_usec * 1E-6;
}


int main(int arg, char *argv[])
{
    FILE *f;
    bstree *tree, *tode;
    listnode *hashtab[200003], *hode;

    char words[200003][15];
    char *t_w, *h_w;
    long double t_tree, t_hash;

    f = fopen(argv[1], "rb");
    for (int i = 1; i <= 200003; i++)
        fscanf(f, "%s", words[i - 1]);
    
    

    tree = bstree_create(words[0], 0);
    hashtab_init(hashtab);

    for (int i = 1; i <= 200003; i ++)
    {
        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);

        if (i % 10000 == 0)
        {
            char *t_w = words[(i - 1) ]; // без рандома беру последнее
            char *h_w = words[0];
            t_tree = wtime();
            tode = bstree_lookup(tree, t_w);
            t_tree = wtime() - t_tree;

            t_hash = wtime();
            hode = hashtab_lookup(hashtab, h_w);
            t_hash = wtime() - t_hash;

            printf("%d \t %.12Lf \t %.12Lf\n", i, t_tree, t_hash);
        }
        
    }
    free(tree);
    fclose(f);
    return 0;
}