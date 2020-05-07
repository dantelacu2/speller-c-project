// Implements a dictionary's functionality
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 33;
unsigned int counter = 0;
// Hash table
node *table[N];
// linked lists empty pointer
node *n = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int z = hash(word);
    for (node *point = table[z]; point != NULL; point = point->next)
    {
        char *compare = point->word;

        if (strcasecmp(compare, word) == 0)
        {
            return true;
        }
    }
    return false;
}

unsigned int hash(const char *word)
{
    //Adapted by Neel Mehta from
    //http://stackoverflow.com/questions/2571683/djb2-hash-function.
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // fscanf reads in dictionary each element gets put into a linked list within a hash table.
    FILE *ptr = fopen(dictionary, "r");

    if (ptr == NULL)
    {
        return false;
    }

    char buffer[LENGTH];
    while (fscanf(ptr, "%s", buffer) != EOF)
    {
        // finds the index
        int j = hash(buffer);
        // creates a new node
        n = malloc(sizeof(node));
        // copies word to new node
        strcpy(n->word, buffer);
        // adds to front of the list
        n->next = table[j];
        table[j] = n;
        counter++;
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *q = table[i];
        node *temp = table[i];
        while (q != NULL)
        {
            q = q->next;
            free(temp);
            temp = q;
        }
    }
    return true;
}
