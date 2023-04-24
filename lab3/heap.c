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
        h->pos = malloc(sizeof(int) * (maxsize + 1));
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

void pos_swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(heap *h)
{
    int i = h->nnodes;
    while (i > 1 && h->nodes[i].key < h->nodes[heap_parent(i)].key)
    {
        heap_swap(&h->nodes[i], &h->nodes[heap_parent(i)]);
        pos_swap(&h->pos[h->nodes[i].value], &h->pos[h->nodes[heap_parent(i)].value]);
        i = heap_parent(i);
    }
}

heapnode *heap_min(heap *h)
{
    if (h->nnodes == 0)
        return NULL;
    
    return &h->nodes[1];
}

int heap_insert(heap *h, int key, int value)
{
    if(h->nnodes >= h->maxsize)
        return -1;
    
    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;
    h->pos[value] = h->nnodes;
    heapify_down(h);
    return 0;
}

heapnode heap_extract_min(heap *h)
{
    if (h->nnodes == 0)
		return (heapnode){0, -1};
    heapnode minnode;
    minnode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes];
    h->pos[h->nodes[1].value] = 1;
    h->nnodes--;
    heap_heapify(h, 1);
    return minnode;
}

void heap_heapify(heap *h, int index)
{
    for(;;)
    {
        int left = heap_left(index);
        int right = heap_right(index);
        int smallest = index;
        if (left < h->nnodes && h->nodes[left].key < h->nodes[index].key)
        {
            smallest = left;
        }
        if (right < h->nnodes && h->nodes[right].key < h->nodes[smallest].key)
		{
			smallest = right;
		}
        if(smallest == index)
            break;
        heap_swap(&h->nodes[index], &h->nodes[smallest]);
        pos_swap(&h->pos[h->nodes[index].value], &h->pos[h->nodes[smallest].value]);
        index = smallest;
    }
}

int heap_decrease_key(heap *h, int index, int newkey)
{   
    int shift = h->pos[index];
    if(h->nodes[shift].key < newkey)
        return -1;
    h->nodes[shift].key = newkey;
	for (;shift > 1; shift = shift / 2;)
	{
		if (h->nodes[shift].key < h->nodes[shift / 2].key)
		{
			heap_swap(&h->nodes[shift], &h->nodes[shift / 2]);
			pos_swap(&h->pos[h->nodes[shift].value], &h->pos[h->nodes[shift / 2].value]);
		}
	}
	return shift;
}
