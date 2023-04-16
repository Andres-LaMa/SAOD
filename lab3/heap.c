#include "lib.h"

int heap_left(int i)
{
    return 2 * i;
}
int heap_right(int i)
{
    return 2 * i + 1;
}
int heap_parent(int i)
{
    return i / 2;
}

heap *heap_create(int maxsize)
{
    heap *h = (heap *)malloc(sizeof(*h));

    if (h != NULL)
    {
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
        if (h->nodes == NULL)
        {
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(heap *h)
{
    free(h->nodes);
    free(h);
}

void heap_swap(heapnode *a, heapnode *b)
{
    heapnode temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

heapnode *heap_min(heap *h)
{
    if (h->nnodes == 0)
        return NULL;
    
    return &h->nodes[0];
}

int heap_insert(heap *h, int key, char *value)
{
    if (h->nnodes >= h->maxsize)
        return -1;

    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;
    
    // HeapifyUp
    for (int i = h->nnodes; i > 1 && h->nodes[i].key < h->nodes[heap_parent(i)].key; i = heap_parent(i))
        heap_swap(&h->nodes[i], &h->nodes[heap_parent(i)]);

    return 0;
}

heapnode heap_extract_min(heap *h)
{
    if (h->nnodes == 0)
        return (heapnode) {0, NULL};
    
    heapnode minode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes];
    h->nnodes--;
    heap_heapify(h, 0);
    return minode;
}

void heap_heapify(heap *h, int index)
{
    for ( ; ; )
    {
        int left = heap_left(index);
        int right = heap_right(index);

        int largest = index;
        if (left <= h->nnodes && h->nodes[left].key < h->nodes[index].key)
            largest = left;
        
        if (right <= h->nnodes && h->nodes[right].key < h->nodes[index].key)
            largest = right;
        
        if (largest == index)
            break;

        heap_swap(&h->nodes[index], &h->nodes[largest]);
        index = largest;
    }
}

int heap_decrease_key(heap *h, int index, int newkey)
{
    if (h->nodes[index].key < newkey)
        return -1;
    
    h->nodes[index].key = newkey;
    while (index > 1 && h->nodes[index].key < h->nodes[heap_parent(index)].key)
    {
        heap_swap(&h->nodes[index], &h->nodes[heap_parent(index)]);
        index = heap_parent(index);
    }
    return index;
}
