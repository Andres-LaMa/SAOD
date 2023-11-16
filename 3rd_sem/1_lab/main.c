#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "AVL_tree.h"
#include "print_tree.h"

#define SIZE 10

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long double)t.tv_sec + (long double)t.tv_usec * 1E-6;
}

int main(int arg, char *argv[]){
    if (arg < 2){
        printf("Не хватает аргументов командной строки!\n");
        return -1;
    }
    
    FILE *f;
    AVL_nad_tree *nad_tree = NULL;
    AVL_Tree *temp_tree = malloc(sizeof(AVL_Tree));
    AVL_Tree *node = NULL;

    char words[55000][15];
    long double t_tree;
    srand(time(NULL));

    f = fopen(argv[1], "rb");
    for (int i = 1; i <= SIZE; i++)
        fscanf(f, "%s", words[i - 1]);

    
    // printf("Size\tTime\n");

    for (int i = 1; i < SIZE + 1; i++){
        nad_tree = Node_add(nad_tree, i, words[i-1]);
    //                 // поиск елементов
    //     if (i % 1000 == 0){
    //         t_tree = wtime();
    //         for (int j = 0; j < 1000; j++){
    //             node = Tree_lookup(nad_tree->tree, 1 + rand() % i);
    //         }
    //         t_tree = wtime() - t_tree;
    //         // printf("%6d\t%Lf\n", i, t_tree);
        }
                    // демонстрация построения дерева
        // printf("_________________________________________________________________________\n");
        // printf("Chapter %d, count lists = %d, count deleted lists = %d\n", i, nad_tree->count_lists, nad_tree->count_deleted);
        // print_tree(nad_tree->tree, 0, 32);
        // printf("_________________________________________________________________________\n");
    // }
                    // демонстрация удаления дерева 

    printf("Deleted!\n");
    for (int i = 1; i < 5; i++){
        nad_tree = Node_deleted(nad_tree, 1 + rand() % SIZE);

        printf("_________________________________________________________________________\n");
        printf("Chapter %d, count lists = %d, count deleted lists = %d\n", i, nad_tree->count_lists, nad_tree->count_deleted);
        print_tree(nad_tree->tree, 0, 32);
        printf("_________________________________________________________________________\n");

    }

    
    
    // print_tree(tree, 0, 32);
    
    // printf("%s = %d; deleted - %d; count_deleted = %d\n", nad_tree->tree->value, nad_tree->tree->key, nad_tree->tree->deleted, nad_tree->count_deleted);
    AVL_Tree *min = min_noda(nad_tree->tree);
    AVL_Tree *max = max_noda(nad_tree->tree);
    printf("%d\n", min->key);
    printf("%d\n", max->key);

    return 0;
}