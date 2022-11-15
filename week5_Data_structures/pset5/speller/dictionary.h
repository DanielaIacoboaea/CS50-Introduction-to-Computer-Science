// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>


// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
void insert_node(char *new_word, unsigned int index);
//node* find_end(node* head);
//void free_node(node* current);
unsigned int hash_letter(const char l);
void initialize_head(unsigned int root_index, char letter);
void add_nodes(const char *word, unsigned int root_index);

#endif // DICTIONARY_H
