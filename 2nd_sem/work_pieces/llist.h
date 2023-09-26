typedef struct listnode
{
    int value;
    struct listnode *next;
}listnode;

listnode *list_createnode(int value);

listnode *list_addfront(listnode *list, int value);