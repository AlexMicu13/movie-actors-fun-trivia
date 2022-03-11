// Headerul specific functiilor necesare rezolvarii taskului 3

#ifndef __TASK3_H__
#define __TASK3_H__

#include <limits.h>

#include "graph.h"
#include "task1.h"

typedef struct bridge
{
    char *vertex1;
    char *vertex2;
} bridge;

// Compara lexicografic doua muchii pentru ordonarea qsort
int compare_bridges(const void *a, const void *b)
{
    bridge *p1 = (bridge *)a;
    bridge *p2 = (bridge *)b;
    if (strcmp(p1->vertex1, p2->vertex1) != 0)
        return strcmp(p1->vertex1, p2->vertex1);
    return strcmp(p1->vertex2, p2->vertex2);
}

// Algoritmul DFS modificat sa gaseasca puntile
void DFS_mod(graph *g, int node, int time, int *index, int *low, int *parents,
             bridge *result, int *size)
{
    index[node] = time;
    low[node] = time;
    time++;
    graph_node *aux = g->adj_list[node];
    for (; aux; aux = aux->next)
        if (aux->id != parents[node])
        {
            if (index[aux->id] == -1)
            {
                parents[aux->id] = node;
                DFS_mod(g, aux->id, time, index, low, parents, result,
                        size);
                if (low[aux->id] < low[node])
                    low[node] = low[aux->id];
                if (low[aux->id] > index[node])
                {
                    char *vertex1 = find_by_id(g->trie, aux->id);
                    char *vertex2 = find_by_id(g->trie, node);
                    if (strcmp(vertex1, vertex2) < 0)
                    {
                        result[(*size)].vertex1 = vertex1;
                        result[(*size)++].vertex2 = vertex2;
                    }
                    else
                    {
                        result[(*size)].vertex1 = vertex2;
                        result[(*size)++].vertex2 = vertex1;
                    }
                }
            }
            else
            {
                if (index[aux->id] < low[node])
                    low[node] = index[aux->id];
            }
        }
}

// Algoritmul de gasire a tuturor puntilor prin parcurgerea lor in adancime,
// sortarea lor cu ajutorul functiei qsort si afisarea lexicografica a puntilor
void bridges(graph *g, FILE *output)
{
    int i, time = 0, size = 0;
    int *index = (int *)malloc(g->size * sizeof(int));
    int *low = (int *)malloc(g->size * sizeof(int));
    int *parents = (int *)calloc(g->size, sizeof(int));
    bridge *result = (bridge *)malloc(g->size * sizeof(bridge));
    for (i = 0; i < g->size; i++)
    {
        index[i] = -1;
        low[i] = INT_MAX;
    }
    for (i = 0; i < g->size; i++)
        if (index[i] == -1)
            DFS_mod(g, i, time, index, low, parents, result, &size);
    fprintf(output, "%d\n", size);
    qsort(result, size, sizeof(bridge), compare_bridges);
    for (i = 0; i < size; i++)
        fprintf(output, "%s %s\n", result[i].vertex1, result[i].vertex2);
    free(index);
    free(low);
    free(parents);
    free(result);
}

#endif
