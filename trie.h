// Headerul pentru structura de date de tip trie pentru stocarea numelelor
// actorilor

#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

// Structura unui nod trie (stochez la final id-ul si numele ca sa nu fie
// nevoie sa reconstruiesc numele)
typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
    int is_end;
    char *name;
} trie_node;

// Initializeaza un nod de trie
trie_node *init_trie()
{
    trie_node *root = (trie_node *)malloc(sizeof(trie_node));
    root->is_end = -1;
    root->name = (char *)malloc(ALPHABET_SIZE * sizeof(char));
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        root->children[i] = NULL;
    return root;
}

// Adauga un cuvant in trie
void insert_trie(trie_node *trie, char *word, int *id)
{
    int i, idx;
    trie_node *aux = trie;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 0)
            idx = word[i];
        else
            idx = ALPHABET_SIZE + word[i];
        if (!aux->children[idx])
            aux->children[idx] = init_trie();
        aux = aux->children[idx];
    }
    aux->is_end = *id;
    (*id)++;
    strcpy(aux->name, word);
}

// Verifica daca un nod este in trie
int contains(trie_node *trie, char *word)
{
    int i, idx;
    trie_node *aux = trie;
    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] >= 0)
            idx = word[i];
        else
            idx = ALPHABET_SIZE + word[i];
        if (!aux->children[idx])
            return -1;
        aux = aux->children[idx];
    }
    if (aux == NULL)
        return -1;
    return aux->is_end;
}

// Cauta o denumire dupa id
char *find_by_id(trie_node *trie, int id)
{
    if (trie == NULL)
        return NULL;
    if (trie->is_end != -1)
    {
        if (trie->is_end == id)
            return trie->name;
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        if (trie->children[i])
        {
            char *aux = find_by_id(trie->children[i], id);
            if (aux)
                return aux;
        }
    return NULL;
}

// Distruge structura de date de tip trie
void destroy_trie(trie_node *trie)
{
    if (trie == NULL)
        return;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        if (trie->children[i] != NULL)
            destroy_trie(trie->children[i]);
    free(trie->name);
    free(trie);
    trie = NULL;
}

#endif
