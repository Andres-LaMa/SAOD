#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#define SIZE_1 9
#define SIZE_2 100

//functions for a graph

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
void random_graph(graph *g);
void random_graph_grid(graph *g);
void graph_print(graph *g);

// functions for a heaps

typedef struct Heapnode
{
    int key; // приоритет/вес
    int value; // номер вершины
}heapnode;

typedef struct Heap
{
    int maxsize; // максимальный размер кучи
    int nnodes; // число элементов
    heapnode *nodes; // массив элементов
    int *pos; // по индексу вершины лежит индекс элемента в масси nodes // массив индексов для нодс
}heap;

int heap_left(int i);
int heap_right(int i);
int heap_parent(int i);

heap *heap_create(int maxsize);
void heap_free(heap *h);
void heap_swap(heapnode *a, heapnode *b);
heapnode *heap_min(heap *h);
int heap_insert(heap *h, int key, int value);
heapnode heap_extract_min(heap *h);
void heap_heapify(heap *h, int index);
int heap_decrease_key(heap *node, int index, int newkey);

// functions of Dijkstra

void Dejkstra(graph *g, int src, int *prev);
int search_shortest_path(graph *g, int src, int dst, int *prev, int *path);
int SearchShortestPath(graph *g, int src, int dst, int *prev, int *path);
void ShortestPathDijkstra(graph *g, int src, int *prev);