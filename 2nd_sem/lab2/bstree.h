typedef struct bstree
{
    char *key;
    int value;

    struct bstree *left;
    struct bstree *right;
}bstree;

bstree *bstree_create(char *key, int value);

void bstree_add(bstree *tree, char *key, int value);

bstree *bstree_lookup(struct bstree *tree, char *key);

void bstree_delete_elements(struct bstree *tree, char *key);

void bstree_delete(bstree *tree);

bstree *bstree_min(bstree *tree);

bstree *bstree_max(bstree *tree);

void free_bstree(bstree *tree);

void print_tree(bstree *tree, int p, int s);

bstree *delete(bstree *tree, char *key);

bstree *delete_node(bstree *tree, bstree *node, bstree *parent);