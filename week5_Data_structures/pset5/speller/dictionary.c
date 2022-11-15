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
/*
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
*/

// Number of buckets in hash table
const unsigned int N = 27;

typedef struct node{
    int word_end;
    struct node* next[N];
}
node;

// Hash table
//node *table[N];

node* root = NULL;

int word_count = 0;
void free_node(node* current);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int i;
    unsigned int hash_code_root = hash_letter(word[0]);
    unsigned int code;

    node* temp = root->next[hash_code_root];

    int n = strlen(word);

    if (n == 1)
    {
        if (temp->word_end == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (i = 1; i < n; i++)
        {
            code = hash_letter(word[i]);

            if (temp->next[code] == NULL)
            {
                return false;
            }
            else
            {
                temp = temp->next[code];
            }
            if (i == n - 1 && temp->word_end == 1)
            {
                return true;
            }
        }
    }
    return false;
}

//Hash letter to a number

unsigned int hash_letter(const char l)
{
    unsigned int code = 0;

    if(islower(l))
    {
        code = (unsigned int) ((int)l - 97);
    }
    else if (isupper(l))
    {
        code = (unsigned int) ((int)l - 65);
    }
    else
    {
        code = 26;
    }

    return code;
}

// Hashes word to a number

/*
unsigned int hash(const char *word)
{
    // TODO


}
*/


void initialize_head(unsigned int root_index, char letter)
{
    node* add_new = (node *) malloc(sizeof(node));
    add_new->word_end = 0;
    for (int j = 0; j < N; j++)
    {
        add_new->next[j] = NULL;
    }

    root->next[root_index] = add_new;
}


void add_nodes(const char *word, unsigned int root_index)
{
    int i, j;
    node* temp = root->next[root_index];
    node* add_new;
    int n = strlen(word);
    unsigned int code;

    if (n == 1)
    {
        temp->word_end = 1;
    }else
    {
        for (i = 1; i < n; i++)
        {
            code = hash_letter(word[i]);
            if (temp->next[code] != NULL)
            {
                temp = temp->next[code];
                if (i == n-1)
                {
                    temp->word_end = 1;
                }
            }
            else
            {
                add_new = (node *) malloc(sizeof(node));
                if (i == n-1)
                {
                    add_new->word_end = 1;
                }else
                {
                    add_new->word_end = 0;
                }
                for (j = 0; j < N; j++)
                {
                    add_new->next[j] = NULL;
                }
                temp->next[code] = add_new;
                temp = temp->next[code];
            }
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char read_word[LENGTH + 1];
    unsigned int root_code;
    int i;

    FILE* f = fopen(dictionary, "r");
    if(f == NULL)
    {
        printf("error, error, could not open dictionary file\n");
        return 1;
    }

    root = (node *) malloc(sizeof(node));
    root->word_end = 0;
    for (i = 0; i < N; i++)
    {
        root->next[i] = NULL;
    }

    while (fscanf(f, "%s", read_word) != EOF)
    {
        root_code = hash_letter(read_word[0]);

        if (root->next[root_code] == NULL)
        {
            initialize_head(root_code, read_word[0]);
        }

        add_nodes(read_word, root_code);

        word_count++;
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count != 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

void free_node(node* current)
{
    if (current == NULL)
    {
        return;
    }
    for (int i = 0; i < N; i++)
    {
        free_node(current->next[i]);
    }

    free(current);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int i;
    for (i = 0; i < N; i++)
    {
        free_node(root->next[i]);
    }
    free(root);

    return true;
}
