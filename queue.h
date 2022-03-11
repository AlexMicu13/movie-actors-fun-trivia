// Header-ul corespunzator structurii de date coada

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

// Structura unui nod de coada
typedef struct queue_node
{
    int *value;
    struct queue_node *next;
} queue_node;

typedef struct
{
    int size;
    queue_node *front, *back;
} queue;

// Initializeaza coada
queue *init_queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = q->back = NULL;
    q->size = 0;
    return q;
}

// Verifica daca coada este goala
int empty_queue(queue *q)
{
    if (q && q->front != NULL && q->back != NULL)
        return 0;
    return 1;
}

// Pune elemente in coada
void push_queue(queue *q, int *value)
{
    queue_node *aux = (queue_node *)malloc(sizeof(queue_node));
    aux->value = value;
    aux->next = NULL;
    if (empty_queue(q))
    {
        q->front = q->back = aux;
        q->size = 1;
        return;
    }
    q->back->next = aux;
    q->back = aux;
    q->size++;
}

// Elimina primul element din coada
int pop_queue(queue *q)
{
    queue_node *aux = q->front;
    if (q->size == 1)
    {
        q->front = q->back = NULL;
        free(aux);
        q->size = 0;
        return 1;
    }
    if (aux)
    {
        q->front = aux->next;
        free(aux);
        q->size--;
        return 1;
    }
    return 0;
}

// Afiseaza primul element din coada
int get_front_queue(queue *q)
{
    if (q)
        return *q->front->value;
    return 0;
}

#endif
