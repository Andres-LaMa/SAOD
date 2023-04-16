#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstree
{
    char *key;
    int value;

    struct bstree *left;
    struct bstree *right;
}bstree;

bstree *bstree_create(char *key, int value)
{
    bstree *node;

    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    
    return node;
}

void bstree_add(bstree *tree, char *key, int value)
{
    if (tree == NULL)
    {
        return;
    }
    bstree *parent, *node;
    while (tree != NULL)
    {
        parent = tree;
        if (strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
        }
        else if (strcmp(key, tree->key) > 0)
        {
            tree = tree->right;
        }
        else
        {
            return;
        }
    }
    node = bstree_create(key, value);
    if (strcmp(key, parent->key) < 0)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
}

bstree *bstree_lookup(bstree *tree, char *key)
{
    while (tree != NULL)
    {
        if (strcmp(key, tree->key) == 0)
        {
            return tree;
        }
        else if (strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }
    return tree;
}

bstree *bstree_min(bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    bstree *node = (bstree *)malloc(sizeof(node));
    if (node == NULL)
    {
        return NULL;
    }
    node = tree;
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

bstree *bstree_max(bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    
    while (tree->right != NULL)
    {
        tree = tree->right;
    }
    return tree;
}

void replace_node(bstree *parent, bstree *node, bstree *child)
{
    if (parent != NULL)
    {
        if (strcmp(node->key, parent->key) < 0)
            parent->left = child;
        else
            parent->right = child;
    }
}

bstree *delete_node(bstree *tree, bstree *node, bstree *parent)
{
    if (node->left == NULL)
    {
        replace_node(parent, node, node->right);
        if (parent == NULL)
        {
            tree = node->right;
        }
    }
    else if (node->right == NULL)
    {
        replace_node(parent, node, node->left);
        if (parent == NULL)
        {
            tree = node->left;
        }
    }
    else
    {
        bstree *min = malloc(sizeof(bstree));
        bstree *minparent = malloc(sizeof(bstree));
        if (!min || !minparent)
        {
            printf("Ошибка выделения памяти!\n");
            return tree;
        }
        
        min = node->right;
        minparent = min;

        while (min->left != NULL)
        {
            minparent = min;
            min = min->left;
        }
        replace_node(parent, node, min);
        if (parent == NULL)
        {
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
            tree = min;
        }
        else if (node->right != min)
        {
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        }
        else
        {
            min->left = node->left;
        }
    }
    free(node);
    return tree;
}

bstree *delete(bstree *tree, char *key)
{
    bstree *parent;
    bstree *node;

    parent = NULL;
    node = tree;
    int check;
    while (node != NULL && ((check = strcmp(node->key, key)) != 0) )
    {
        parent = node;
        if (check > 0)
            node = node->left;
        else
            node = node->right;
    }
    if (node == NULL)
    {
        return tree;
    }
    tree = delete_node(tree, node, parent);
    return tree;
}

void free_bstree(bstree *tree)
{
    if (tree == NULL)
    {
        return ;
    }
    else if (tree->left != NULL)
    {
        free_bstree(tree->left);
    }
    else
    {
        free_bstree(tree->right);
    }
    free(tree);
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

void print_tree(bstree *tree, int p, int s)
{
    if (tree == NULL)
        return;
    
    printf("%s ", tree->key);
    printf("\n");
    
    if (tree->right != NULL)
    {        
        print_line("|\n", p, s);
        print_line("R: ", p, s);
        print_tree(tree->right, p+1, s + ((tree->right == NULL ? 0 : 1)<<p));
    }
    if (tree->left != NULL)
    {
        print_line("|\n", p, s);
        print_line("L: ", p, s);
        print_tree(tree->left, p+1, s);
    }
    
}
