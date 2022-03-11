// Header pentru structura de date de tip graf cu liste de adiacenta

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "trie.h"

// Structura unui nod din lista de adiacenta
typedef struct graph_node
{
    int id;
    struct graph_node *next;
} graph_node;

// Structura grafului cu lista de adiacenta ce stocheaza numele in trie
// pentru o ordonare automata a numelor
typedef struct graph
{
    int size;
    trie_node *trie;
    graph_node **adj_list;
} graph;

// Initializeaza un graf
graph *init_graph(int number)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->size = number;
    g->adj_list = (graph_node **)calloc(number, sizeof(graph_node *));
    g->trie = init_trie();
    int i;
    for (i = 0; i < number; i++)
        g->adj_list[i] = NULL;
    return g;
}

// Adauga o muchie in graf (unidirectionala)
void add_edge(graph *g, int from, int to)
{
    graph_node *aux1 = (graph_node *)malloc(sizeof(graph_node));
    graph_node *aux2 = (graph_node *)malloc(sizeof(graph_node));
    aux1->id = from;
    aux2->id = to;
    aux1->next = g->adj_list[to];
    aux2->next = g->adj_list[from];
    g->adj_list[to] = aux1;
    g->adj_list[from] = aux2;
}

// Cauta daca id-ul unui actor se regaseste in lista altui actor sau nu
int contains_id(graph *g, int insert, int id)
{
    graph_node *aux = g->adj_list[insert];
    for (; aux; aux = aux->next)
        if (aux->id == id)
            return 1;
    return 0;
}

// Sterge lista de adiacenta a unui actor
void delete_list(graph_node **gn, int value)
{
    graph_node *del = *gn, *urm;
    if (del->id == value && del != NULL)
    {
        *gn = del->next;
        free(del);
        return;
    }
    while (del->id != value && del->next != NULL)
    {
        urm = del;
        del = del->next;
    }
    if (del == NULL)
        return;
    urm->next = del->next;
    free(del);
}

// Sterge toate listele de adiacenta
void delete_all(graph_node **gn)
{
    while (*gn != NULL)
        delete_list(gn, (*gn)->id);
}

// Distruge graful si toate structurile din acesta
void destroy_graph(graph *g)
{
    int i;
    for (i = 0; i < g->size; i++)
        delete_all(&g->adj_list[i]);
    free(g->adj_list);
    destroy_trie(g->trie);
    free(g);
}

#endif
