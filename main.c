// Micu Alexandru - 311CCb
// Tema 3 SD - Grafuri

#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "reading.h"

#define SAFE 100000

// Efectueaza pasii necesari rezolvarii primului task
void task1(FILE *output, graph *g)
{
    int max = 0;
    int *order = (int *)malloc(g->size * sizeof(int));
    biggest_component(g, &max, order);
    order = (int *)realloc(order, (max + 1) * sizeof(int));
    fprintf(output, "%d\n", max);
    display_component(g->trie, order, max, output);
    free(order);
}

// Efectueaza pasii necesari rezolvarii celui de al doilea task
void task2(FILE *input, FILE *output, graph *g)
{
    char actor1[ALPHABET_SIZE], actor2[ALPHABET_SIZE];
    fscanf(input, "%[^\n]\n", actor1);
    fscanf(input, "%[^\n]\n", actor2);
    int start = contains(g->trie, actor1);
    int finish = contains(g->trie, actor2);
    int *dist = (int *)malloc(g->size * sizeof(int));
    fprintf(output, "%d\n", BFS(g, start, finish, dist));
    free(dist);
}

// Efectueaza pasii necesari rezolvarii celui de al doilea task
void task3(FILE *output, graph *g)
{
    bridges(g, output);
}

// Citeste inputul, face cerinta corespunzatoare si afiseaza
int main(int argv, char *args[])
{
    FILE *input, *output;
    input = fopen(args[2], "r");
    output = fopen(args[3], "w");
    graph *g = init_graph(SAFE);
    read_graph(g, input);
    g = (graph *)realloc(g, g->size * sizeof(graph));
    if (strcmp(args[1], "-c1") == 0)
    {
        task1(output, g);
    }
    else if (strcmp(args[1], "-c2") == 0)
    {
        task2(input, output, g);
    }
    else
    {
        task3(output, g);
    }
    destroy_graph(g);
    fclose(input);
    fclose(output);
    return 0;
}