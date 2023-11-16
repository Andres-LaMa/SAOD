#pragma once

typedef struct AVL_Tree{
    int key;
    char *value;

    int height;
    int deleted;
    struct AVL_Tree *left_node;
    struct AVL_Tree *right_node;
} AVL_Tree;

typedef struct AVL_nad_tree{
    AVL_Tree *tree;

    int count_lists;
    int count_deleted;
    double procent_d;
}AVL_nad_tree;


void Tree_free(AVL_Tree *tree);
AVL_Tree *Tree_lookup(AVL_Tree *tree, int key);
AVL_Tree *Node_create(int key, char *value);
int Tree_height(AVL_Tree *tree);
AVL_Tree *AVL_RRotate(AVL_Tree *tree);
AVL_Tree *AVL_LRotate(AVL_Tree *tree);
AVL_Tree *AVL_LRRotate(AVL_Tree *tree);
AVL_Tree *AVL_RLRotate(AVL_Tree *tree);
int Tree_balance(AVL_Tree *tree);
AVL_nad_tree *Node_add(AVL_nad_tree *nad_tree, int key, char *value);
AVL_nad_tree *Node_deleted(AVL_nad_tree *nad_tree, int key);
void inOrderTravers(AVL_Tree *tree, AVL_Tree **new_tree);
AVL_Tree *min_noda(AVL_Tree *tree);
AVL_Tree *max_noda(AVL_Tree *tree);
int max(int a, int b);
AVL_Tree *min_noda(AVL_Tree *tree);
AVL_Tree *max_noda(AVL_Tree *tree);