#include "lib.h"

void Dejkstra(graph *g, int src, int *prev)
{
    heap *h;
    heapnode node_minimal;
    int len;
    int wight, new_key; // what is it?
    h = heap_create(SIZE_1); // проверка на не нул

    for (int i = 1; i < SIZE_1 + 1; i++)
    {
        if (i == src)
        {
            len = 0;
            prev[src] = -1;
            heap_insert(h, len, src);
            continue;
        }
        len = ~0U >> 1; //INT_MAX
        prev[i] = -1;
        heap_insert(h, len, i);
    }
    
    for (int i = 1; i < SIZE_1 + 1; i++)
    {
        node_minimal = heap_extract_min(h);
        g->visited[node_minimal.value - 1] = 1;
        for (int u = 1; u < SIZE_1 + 1; u++)
        {
            wight = graph_get_edge(g, node_minimal.value-1, u-1);
            if (wight == 0)
                continue;
            if (g->visited[u-1] > 0)
                continue;
            new_key = node_minimal.key + wight;
            if (new_key < h->nodes[h->pos[u]].key)
            {
                heap_decrease_key(h, u, new_key);
                prev[u] = node_minimal.value;
            }
        }
        printf("key = %d, value = %d\n", node_minimal.key, node_minimal.value);
    }
    heap_free(h);
}

int search_shortest_path(graph *g, int src, int dst, int *prev, int *path)
{
    int pathlen = 1, i, j, w;
    j = 0;
    w = 0;

    for (i = dst; i != src; i = prev[i])
    {
        pathlen++;
        w += graph_get_edge(g, i-1, prev[i]-1);
    }
    j = 0;
    printf("%d\n", w);
    for (i = dst; i != src; i = prev[i])
    {
        path[pathlen - j] = i;
        j++;
    }
    path[pathlen - j] = src;
    return pathlen;
}