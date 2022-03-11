// Headerul pentru functiile corespunzatoare rezolvarii primului task

#ifndef __TASK1_H__
#define __TASK1_H__

#include "graph.h"

// Parcurge in adancime graful
void DFS(graph *g, int start, int *visited, int *count, int *order)
{
    visited[start] = 1;
    order[*count] = start;
    graph_node *aux = g->adj_list[start];
    (*count)++;
    for (; aux; aux = aux->next)
        if (visited[aux->id] == 0)
            DFS(g, aux->id, visited, count, order);
}

// Cauta daca id-ul din trie e in componenta
int contains_id_trie(int *list_id, int size, int id)
{
    int i;
    for (i = 0; i < size; i++)
        if (id == list_id[i])
            return 1;
    return 0;
}

// Afiseaza toate nodurile componentei conexe parcurgand trie-ul
void display_component(trie_node *root, int *ids, int size_ids, FILE *output)
{
    if (root == NULL)
        return;
    if (root->is_end != -1)
    {
        if (contains_id_trie(ids, size_ids, root->is_end))
            fprintf(output, "%s\n", root->name);
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            display_component(root->children[i], ids, size_ids, output);
}

// Gaseste cea mai mare componenta conexa - marimea si inceputul
void biggest_component(graph *g, int *max, int *max_id)
{
    int i, count;
    int *visited = (int *)calloc(g->size, sizeof(int));
    for (i = 0; i < g->size; i++)
        if (visited[i] == 0)
        {
            count = 0;
            int *order = (int *)malloc(g->size * sizeof(int));
            DFS(g, i, visited, &count, order);
            if (count > *max)
            {
                *max = count;
                int k;
                for (k = 0; k < count; k++)
                    max_id[k] = order[k];
            }
            free(order);
        }
    free(visited);
}

#endif
