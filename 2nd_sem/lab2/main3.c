#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "hashtab.h"

#define HASH_SIZE 200003

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long double)t.tv_sec + (long double)t.tv_usec * 1E-6;
}


int main(int arg, char *argv[])
{
    FILE *f;
    listnode *Jentab[HASH_SIZE], *exp;
    listnode *KPtab[HASH_SIZE];

    char words[200000][15];
    char *w;
    long double t_Jen, t_KP;

    f = fopen(argv[1], "rb");
    for (int i = 0; i < HASH_SIZE-3; i++)
        fscanf(f, "%s", words[i - 1]);
    
    
    hashtab_init(Jentab);
    hashtab_init(KPtab);
    
    printf("Size \t     t_Jen \tnum_col_Jen\t t_KP  \t       num_col_KP\n");
    int num_col_Jen = 0, num_col_KP = 0;
    int *p_num_col_Jen = &num_col_Jen, *p_num_col_KP = &num_col_KP;

    int i;
    for (i = 1; i < HASH_SIZE; i++)
    {
        J_hashtab_add(Jentab, words[i-1], i, p_num_col_Jen);
        Ker_and_Rich_hashtab_add(KPtab, words[i-1], i, p_num_col_KP);
        
        if (i % 10000 == 0)
        {
            char *w = words[rand() % (i + 1)];
            t_Jen = wtime();
            exp = J_hashtab_lookup(Jentab, w);
            t_Jen = wtime() - t_Jen;

            t_KP = wtime();
            exp = KP_hashtab_lookup(KPtab, w);
            t_KP = wtime() - t_KP;

            printf("%d \t %.12Lf\t     %3d\t%.12Lf\t %3d \n", i, t_Jen, num_col_Jen, t_KP, num_col_KP);
        }
        
    }
    // printf("Lol\n");
    fclose(f);
    return 0;
}