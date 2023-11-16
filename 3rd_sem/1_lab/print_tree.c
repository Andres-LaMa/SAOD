#include "print_tree.h"
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
    if (tree == NULL){
        printf("В дереве нет узлов!\n");
        return;
    }
    
    if (tree->deleted == 1){
        printf("%d ", tree->key);
    }else{
        printf("%d(D) ", tree->key);
    }
    
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