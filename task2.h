// Headerul pentru functiile corespunzatoare rezolvarii primului task

#ifndef __TASK2_H__
#define __TASK2_H__

#include <limits.h>

#include "graph.h"
#include "queue.h"

// Un BFS modificat pentru a afla cea mai scurta distanta intre 2 noduri si
// care returneaza aceea distanta daca exista drumul sau -1 daca nu exista un
// drum intre acele 2 noduri
int BFS(graph *g, int start, int finish, int *dist)
{
    queue *q = init_queue();
    int i, *visited = (int *)calloc(g->size, sizeof(int));
    for (i = 0; i < g->size; i++)
        dist[i] = INT_MAX;
    visited[start] = 1;
    dist[start] = 0;
    push_queue(q, &start);
    while (!empty_queue(q))
    {
        int u = get_front_queue(q);
        pop_queue(q);
        graph_node *aux = g->adj_list[u];
        for (; aux; aux = aux->next)
        {
            if (visited[aux->id] == 0)
            {
                visited[aux->id] = 1;
                dist[aux->id] = dist[u] + 1;
                push_queue(q, &aux->id);
                if (aux->id == finish)
                {
                    free(visited);
                    while (!empty_queue(q))
                        pop_queue(q);
                    free(q);
                    return dist[aux->id];
                }
            }
        }
    }
    free(visited);
    free(q);
    return -1;
}

#endif
