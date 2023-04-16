#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Graph
{
    int nvertices; // число вершин
    int *m; // матрица n x n
    int *visited;
}graph;

graph *graph_create(int nvertices);
void graph_clear(graph *g);
void graph_free(graph *g);
void graph_set_edge(graph *g, int x, int y, int weight);
int graph_get_edge(graph *g, int x, int y);
void graph_dfs(graph *g, int v);
void graph_bfs(graph *g, int v);

typedef struct Heapnode
{
    int key; // приоритет/вес
    char *value; // данные
}heapnode;

typedef struct Heap
{
    int maxsize; // максимальный размер кучи
    int nnodes; // число элементов
    heapnode *nodes; // массив элементов
}heap;

int heap_left(int i);
int heap_right(int i);
int heap_parent(int i);

heap *heap_create(int maxsize);
void heap_free(heap *h);
void heap_swap(heapnode *a, heapnode *b);
heapnode *heap_min(heap *h);
int heap_insert(heap *h, int key, char *value);
heapnode heap_extract_min(heap *h);
void heap_heapify(heap *h, int index);
int heap_decrease_key(heap *node, int index, int newkey);