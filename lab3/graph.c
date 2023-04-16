#include "lib.h"
// #include "queue_array.h"

graph *graph_create(int nvertices)
{
    graph *g = (graph *)malloc(sizeof(*g));
    if (g == NULL)
        return NULL;
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    g->visited = malloc(sizeof(int) * nvertices);
    graph_clear(g);
    return g;
}

void graph_clear(graph *g)
{
    for (int i = 0; i < g->nvertices; i++)
    {
        g->visited[i] = 0;
        for (int j = 0; j < g->nvertices; j++)
        {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

void graph_free(graph *g)
{
    free(g->m);
    free(g->visited);
    free(g);
}

void graph_set_edge(graph *g, int x, int y, int weight)
{
    g->m[(x - 1) * g->nvertices + y - 1] = weight;
    g->m[(y - 1) * g->nvertices + x - 1] = weight;
}

int graph_get_edge(graph *g, int x, int y)
{
    return g->m[(x -1) * g->nvertices + y - 1];
}

void graph_dfs(graph *g, int v)
{
    int i;
    g->visited[v - 1] = 1;
    printf("Vertex %d\n", v);
    for (i = 0; i < g->nvertices; i++)
        if (g->m[(v - 1) * g->nvertices + i] > 0 && g->visited[i] == 0)
            graph_dfs(g, i + 1);
}

void I_Main_I()
{
    graph *g;
    g = graph_create(10);

    graph_set_edge(g, 1, 2, 1);
    graph_set_edge(g, 1, 4, 1);
    graph_set_edge(g, 1, 5, 1);

    graph_set_edge(g, 2, 1, 1);
    graph_set_edge(g, 2, 3, 1);
    graph_set_edge(g, 2, 5, 1);

    graph_set_edge(g, 3, 2, 1);
    graph_set_edge(g, 3, 4, 1);
    graph_set_edge(g, 3, 5, 1);
    graph_set_edge(g, 3, 8, 1);

    graph_set_edge(g, 4, 1, 1);
    graph_set_edge(g, 4, 3, 1);
    graph_set_edge(g, 4, 5, 1);
    graph_set_edge(g, 4, 6, 1);

    graph_set_edge(g, 5, 1, 1);
    graph_set_edge(g, 5, 2, 1);
    graph_set_edge(g, 5, 3, 1);
    graph_set_edge(g, 5, 4, 1);

    graph_set_edge(g, 6, 4, 1);
    graph_set_edge(g, 6, 7, 1);

    graph_set_edge(g, 7, 6, 1);
    graph_set_edge(g, 7, 8, 1);

    graph_set_edge(g, 8, 7, 1);
    graph_set_edge(g, 8, 3, 1);
    
    
    printf("DFS:\n");
    graph_dfs(g, 1);

    graph_free(g);
}
