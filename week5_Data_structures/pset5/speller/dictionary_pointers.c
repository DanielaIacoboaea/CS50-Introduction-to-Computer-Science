// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    unsigned int hash_code = hash(word);

    node* temp = table[hash_code];
    while (temp)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_code = 0;

    if(islower(word[0]))
    {
        hash_code = (unsigned int) (word[0] - 97);
    }

    if (isupper(word[0]))
    {
        hash_code = (unsigned int) (word[0] - 65);
    }

    return hash_code;
}

void insert_node(char *new_word, unsigned int index)
{
    node* add_new;

    if (table[index] == NULL)
    {
        add_new = (node *) malloc(sizeof(node));
        strcpy(add_new->word, new_word);

        add_new->next = NULL;
        table[index] = add_new;
    }
    else
    {
        add_new = (node *) malloc(sizeof(node));
        strcpy(add_new->word, new_word);
        add_new->next = table[index];

        table[index] = add_new;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char read_word[LENGTH + 1];
    unsigned int get_code;
    int n, i;

    FILE* f = fopen(dictionary, "r");
    if(f == NULL)
    {
        printf("error, error, could not open dictionary file\n");
        return 1;
    }

    for (i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    while (fscanf(f, "%s", read_word) != EOF)
    {
        get_code = hash(read_word);
        insert_node(read_word, get_code);
        word_count++;
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count != 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i;
    for (i = 0; i < N; i++)
    {
        node* head = table[i];
        while (head != NULL)
        {
            node* temp = head->next;
            free(head);
            head = temp;
        }
    }

    return true;
}
