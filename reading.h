// Headerul pentru citirea inputului din fisiere

#ifndef __READING_H__
#define __READING_H__

#include "graph.h"

// Citeste film cu film, la fiecare film actor cu actor, verifica daca actorul
// este in graf deja sau nu si adauga muchiile spre actorii deja cititi din
// film unde nu au deja un alt film "intre" ei
void read_graph(graph *g, FILE *input)
{
    g->size = 0;
    int i, nr_movies, *actors;
    char buff[ALPHABET_SIZE];
    fscanf(input, "%d\n", &nr_movies);
    for (i = 0; i < nr_movies; i++)
    {
        int j, nr_actors;
        fscanf(input, "%[^\n]", buff);
        fscanf(input, "%d\n", &nr_actors);
        actors = calloc(nr_actors, sizeof(int));
        for (j = 0; j < nr_actors; j++)
        {
            int k, id;
            fscanf(input, "%[^\n]\n", buff);
            id = contains(g->trie, buff);
            if (id == -1)
            {
                insert_trie(g->trie, buff, &g->size);
                actors[j] = g->size - 1;
            }
            else
                actors[j] = id;
            for (k = 0; k < j; k++)
                if (contains_id(g, actors[k], actors[j]) == 0)
                    add_edge(g, actors[k], actors[j]);
        }
        free(actors);
    }
}

#endif
