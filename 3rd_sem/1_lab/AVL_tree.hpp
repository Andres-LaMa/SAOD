struct AVL_Tree{
    int key;
    char *value;

    int height;
    struct AVL_Tree *left_node;
    struct AVL_Tree *right_node;
};
void Tree_free(AVL_Tree *tree);
AVL_Tree *Tree_lookup(AVL_Tree *tree, int key);
AVL_Tree *Node_create(int key, char *value);
int Tree_height(AVL_Tree *tree);
AVL_Tree *AVL_RRotate(AVL_Tree *tree);
AVL_Tree *AVL_LRotate(AVL_Tree *tree);
AVL_Tree *AVL_LRRotate(AVL_Tree *tree);
AVL_Tree *AVL_RLRotate(AVL_Tree *tree);
int Tree_balance(AVL_Tree *tree);
AVL_Tree *Node_add(AVL_Tree *tree, int key, char *value);