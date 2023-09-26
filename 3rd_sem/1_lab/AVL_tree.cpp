#include <iostream>
#include "AVL_tree.hpp"

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
    AVL_Tree *node = new AVL_Tree();

    if (node != NULL){
        node->key = key;
        node->value = value;
        node->left_node = NULL;
        node->right_node = NULL;
        node->height = 0;
    }
    return node;
}

int Tree_height(AVL_Tree *tree){
    return (tree != NULL) ? (tree->height) : -1;
}

AVL_Tree *AVL_RRotate(AVL_Tree *tree){
    AVL_Tree *left;

    left = tree->left_node;
    tree->left_node = left->right_node;
    left->right_node = tree;

    tree->height = std::max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    left->height = std::max(Tree_height(left->left_node), tree->height) + 1;
    return left;
}

AVL_Tree *AVL_LRotate(AVL_Tree *tree){
    AVL_Tree *right;

    right = tree->right_node;
    tree->right_node = right->left_node;
    right->left_node = tree;

    tree->height = std::max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    right->height = std::max(Tree_height(right->right_node), tree->height) + 1;
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

AVL_Tree *Node_add(AVL_Tree *tree, int key, char *value){
    if (tree == NULL){
        return Node_create(key, value);
    }
    
    if (key < tree->key){
        tree->left_node = Node_add(tree->left_node, key, value);
        if (Tree_height(tree->left_node) - Tree_height(tree->right_node) == 2){
            if (key < tree->left_node->key){
                tree = AVL_RRotate(tree);
            } else{
                tree = AVL_LRRotate(tree);
            }
        }
    } else if (key > tree->key){
        tree->right_node = Node_add(tree->right_node, key, value);
        if (Tree_height(tree->right_node) - Tree_height(tree->left_node) == 2){
            if (key > tree->right_node->key){
                tree = AVL_LRotate(tree);
            } else{
                tree = AVL_RLRotate(tree);
            }
        }
    }
    tree->height = std::max(Tree_height(tree->left_node), Tree_height(tree->right_node)) + 1;
    return tree;
}
