#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "AVL_tree.hpp"

long double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long double)t.tv_sec + (long double)t.tv_usec * 1E-6;
}

void print_line(char* c, int p, int s)
{
    int t = s, i;
    for(i = 0; i < p; i++) 
    {
        printf(t & 1 ? "|  " : "   "); 
        t /= 2;
    }
    printf("%s", c);
}

void print_tree(AVL_Tree *tree, int p, int s)
{
    if (tree == NULL)
        return;
    
    printf("%d ", tree->key);
    printf("\n");
    
    if (tree->right_node != NULL)
    {        
        print_line("|\n", p, s);
        print_line("R: ", p, s);
        print_tree(tree->right_node, p+1, s + ((tree->right_node == NULL ? 0 : 1)<<p));
    }
    if (tree->left_node != NULL)
    {
        print_line("|\n", p, s);
        print_line("L: ", p, s);
        print_tree(tree->left_node, p+1, s);
    }
    
}

int main(int arg, char *argv[]){
    FILE *f;
    AVL_Tree *tree = NULL, *tode;

    char words[55000][15];
    long double t_tree;

    f = fopen(argv[1], "rb");
    for (int i = 1; i <= 17; i++)
        fscanf(f, "%s", words[i - 1]);

    for (int i = 0; i < 17; i++){
        printf("Chapter %d\n", i);
        tree = Node_add(tree, i, words[i]);
        print_tree(tree, 0, 32);
    }
    
    printf("%s = %d\n", tree->value, tree->key);

    return 0;
}