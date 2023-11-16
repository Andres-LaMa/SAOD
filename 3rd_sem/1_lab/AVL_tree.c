#include "AVL_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

void Tree_free(AVL_Tree *tree){
    if (tree == NULL)
        return;
    
    Tree_free(tree->left_node);
    Tree_free(tree->right_node);
    free(tree);
}

AVL_Tree *Tree_lookup(AVL_Tree *tree, int key){
    while (tree != NULL){
        if (key == tree->key){
            if (tree->deleted == -1){
                return NULL;
            }
            return tree;
        }else if (key < tree->key){
            tree = tree->left_node;
        }else{
            tree = tree->right_node;
        }
    }
    return tree;
}

AVL_Tree *Node_create(int key, char *value){
    AVL_Tree *node = malloc(sizeof(AVL_Tree));

    if (node != NULL){
        node->key = key;
        node->value = value;
        node->deleted = 1;
        node->left_node = NULL;
        node->right_node = NULL;
        node->height = 0;
    }else{
        assert("Node_create: memory allocation error ");
    }
    
    return node;
}

AVL_nad_tree *create_nad_tree(AVL_nad_tree *nad_tree){
    nad_tree = malloc(sizeof(AVL_nad_tree));
    if (nad_tree == NULL){
        assert("Create_nad_tree: memory allocation error");
    }
    nad_tree->tree = NULL;
    nad_tree->count_deleted = 0;
    nad_tree->count_lists = 0;
    nad_tree->procent_d = 0;
    return nad_tree;
}

int Tree_height(AVL_Tree *tree){
    return (tree != NULL) ? (tree->height) : -1;
}

AVL_Tree *AVL_RRotate(AVL_Tree *tree){
    AVL_Tree *left;

    left = tree->left_node;
    tree->left_node = left->right_node;
    left->right_node = tree;

    tree->height = max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    left->height = max(Tree_height(left->left_node), tree->height) + 1;
    return left;
}

AVL_Tree *AVL_LRotate(AVL_Tree *tree){
    AVL_Tree *right;

    right = tree->right_node;
    tree->right_node = right->left_node;
    right->left_node = tree;

    tree->height = max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    right->height = max(Tree_height(right->right_node), tree->height) + 1;
    return right;
}

AVL_Tree *AVL_LRRotate(AVL_Tree *tree){
    tree->left_node = AVL_LRotate(tree->left_node);
    return AVL_RRotate(tree);
}

AVL_Tree *AVL_RLRotate(AVL_Tree *tree){
    tree->right_node = AVL_RRotate(tree->right_node);
    return AVL_LRotate(tree);
}

int Tree_balance(AVL_Tree *tree){
    return Tree_height(tree->left_node) - Tree_height(tree->right_node);
}

AVL_Tree *add(AVL_Tree *tree, int key, char *value){
    if (tree == NULL){
        tree = Node_create(key, value);
    }
    
    if (key < tree->key){
        tree->left_node = add(tree->left_node, key, value);
        if (Tree_height(tree->left_node) - Tree_height(tree->right_node) == 2){
            if (key < tree->left_node->key){
                tree = AVL_RRotate(tree);
            } else{
                tree = AVL_LRRotate(tree);
            }
        }
    } else if (key > tree->key){
        tree->right_node = add(tree->right_node, key, value);
        if (Tree_height(tree->right_node) - Tree_height(tree->left_node) == 2){
            if (key > tree->right_node->key){
                tree = AVL_LRotate(tree);
            } else{
                tree = AVL_RLRotate(tree);
            }
        }
    } else if(key == tree->key) {
        tree->deleted = 1;
        tree->value = value;
    }
    tree->height = max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    return tree;
}

AVL_nad_tree *Node_add(AVL_nad_tree *nad_tree, int key, char *value){
    if (nad_tree == NULL){
        nad_tree = create_nad_tree(nad_tree);
    }
    nad_tree->tree = add(nad_tree->tree, key, value);

    nad_tree->count_lists++;
    return nad_tree;
}

void inOrderTravers(AVL_Tree *tree, AVL_Tree **new_tree){
    if (tree){
        inOrderTravers(tree->left_node, new_tree);
        if (tree->deleted == 1){
            int key = tree->key;
            char *value = tree->value;
            *new_tree = add(*new_tree, key, value);
        }
        inOrderTravers(tree->right_node, new_tree);
    }
}

AVL_nad_tree *Node_deleted(AVL_nad_tree *nad_tree, int key){
    AVL_Tree *d_node = Tree_lookup(nad_tree->tree, key);
    if (d_node == NULL)
        return nad_tree;
    d_node->deleted *= -1;
    nad_tree->count_deleted++;
    if (d_node->deleted == 1){
        return nad_tree;
    }
    nad_tree->procent_d = (double)nad_tree->count_deleted / (double)nad_tree->count_lists;
    if (nad_tree->procent_d < 0.5)
        return nad_tree;
    
    AVL_Tree *new_tree = NULL;
    inOrderTravers(nad_tree->tree, &new_tree);
    nad_tree->count_lists = (nad_tree->count_lists) - (nad_tree->count_deleted);
    nad_tree->count_deleted = 0;
    Tree_free(nad_tree->tree);
    nad_tree->tree = new_tree;

    return nad_tree;
}

void inOrder_min(AVL_Tree *tree, AVL_Tree **min){
	if (tree){        
		inOrder_min(tree->left_node, min);
        if (tree->deleted != -1){
            if (!(*min)){
                *min = tree;
            }else{
                return;
            }
        }
		inOrder_min(tree->right_node, min);
	}
}

void inOrder_max(AVL_Tree *tree, AVL_Tree **min){
	if (tree){        
		inOrder_max(tree->right_node, min);
        if (tree->deleted != -1){
            if (!(*min)){
                *min = tree;
            }else{
                return;
            }
        }
		inOrder_max(tree->left_node, min);
	}
}

AVL_Tree *min_noda(AVL_Tree *tree){
    AVL_Tree **min = malloc(sizeof(AVL_Tree *));
    inOrder_min(tree, min);
    AVL_Tree *temp = (*min);
    free(min);
    return temp;
}
AVL_Tree *max_noda(AVL_Tree *tree){
    AVL_Tree **max = malloc(sizeof(AVL_Tree *));
    inOrder_max(tree, max);
    AVL_Tree *temp = (*max);
    free(max);
    return temp;
}
