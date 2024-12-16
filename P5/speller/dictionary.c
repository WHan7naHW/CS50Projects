// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 70000;

// Hash table
node *table[N];

// word count
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash the word to obtain its hash value
    unsigned int index = hash(word);

    // traverse the linked list at [index]
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // compare, case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += (tolower(word[i]) * i);
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // initialize table
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF && strlen(word) <= LENGTH)
    {
        // count the word
        count++;

        // create space for a new hash table node (allocate memory)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }

        // copy the word into the new node
        strcpy(n->word, word);
        n->next = NULL;

        // obtain hash value: hash()
        unsigned int index = hash(word);

        // add each word to the hash table
        n->next = table[index];
        table[index] = n;
    }

    // close file and return
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
