typedef struct listnode
{
    char *key;
    int value;

    struct listnode *next;
}listnode;

unsigned int hashtab_hash(char *key);

void hashtab_init(listnode **hashtab);

void hashtab_add(listnode **hashtab, char *key, int value);

listnode *J_hashtab_lookup(listnode **hashtab, char *key);

listnode *hashtab_lookup(listnode **hashtab, char *key);

listnode *KP_hashtab_lookup(listnode **hashtab, char *key);

void hashtab_delete(listnode **hashtab, char *key);

unsigned int jenkins_hash(char *s);

unsigned int Ker_and_Rich_hash(char *key);

unsigned short Ker_and_Rich_hashtab_add(listnode **hashtab, char *key, int value, int *col);

unsigned short J_hashtab_add(listnode **hashtab, char *key, int value, int *col);
