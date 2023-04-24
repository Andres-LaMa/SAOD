#include "lib.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    graph *g = malloc(sizeof(g));
    int prev[SIZE_1+1], path[SIZE_1];
    int j, src, pathlen = 0;
    double time;

    g = graph_create(SIZE_1);
    random_graph_grid(g);
    graph_print(g);
    src = 1;

    time = wtime();
    Dejkstra(g, src, prev);
    time = wtime() - time;
    printf("\n");
    for (int i = 1; i < SIZE_1 + 1; i++)
    {
        if (i == src)
            continue;
        printf("Vertise %d:\n", i);
        pathlen = search_shortest_path(g, src, i, prev, path);
        printf("Path: (");
        for (j = 1; j < pathlen; j++)
        {
           printf("%d, ", path[j]); 
        }
        printf("%d)\n", path[j]);
    }
    graph_free(g);
    printf("%f\n", time);
    return 0;
}