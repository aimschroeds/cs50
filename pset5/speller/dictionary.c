// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Int for number of words in dictionary
int counter = 0;
// Number of buckets in hash table
const unsigned int N = 135;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_index = hash(word);
    // Follow list until pointer hits end (NULL)
    for (node* pointer = table[hash_index]; pointer != NULL; pointer = pointer->next)
    {
        // If word to check is found in linked list return true
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
    }
    // If at end of list and word not found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash_index = 0;
    int len = strlen(word);
    for (int i = 0; i < len && i < 4; i++)
    {
        int letter_as_int = word[i];
        // If word is small caps (ASCII > 96) then subtract 96 to get val between 1 - 26
        if (letter_as_int > 96)
        {
            letter_as_int = letter_as_int - 96;
        }
        // If letter is caps (ASCII < 96) then subtract 64 to get val between 1 - 26
        else if (letter_as_int > 63)
        {
            letter_as_int = letter_as_int - 64;
        }
        else
        {
            letter_as_int = 27;
        }
        if (i == 0 && letter_as_int > 18)
        {
            letter_as_int = letter_as_int + 126;
        }
        else if (i == 0 && letter_as_int > 9)
        {
            letter_as_int = letter_as_int + 117;
        }
        hash_index = hash_index + letter_as_int;
    }

    return hash_index;
    // // Pull first letter of word
    // int letter_as_int = word[0];
    // // If word is small caps (ASCII > 96) then subtract 96 to get val between 1 - 26
    // if (letter_as_int > 96)
    // {
    //     letter_as_int = letter_as_int - 96;
    // }
    // // If letter is caps (ASCII < 96) then subtract 64 to get val between 1 - 26
    // else
    // {
    //     letter_as_int = letter_as_int - 64;
    // }
    // return letter_as_int;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open input file
    FILE *dict = fopen(dictionary, "r");

    // If file did not open pass error message and return false
    if (!dict)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    else
    {
        // Loop over every word in file until EOF reached
        char word[LENGTH];
        while (fscanf(dict, "%s", word) != EOF)
        {
            // Find has index for word
            int hash_index = hash(word);

            // Increment counter to determine words in dictionary
            counter++;

            // Create new node for word
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            // Copy word to the node
            strcpy(n->word, word);

            // Set node next value to NULL
            n->next = NULL;

            // Insert node into linked list
            node *head = table[hash_index];
            // Check to see if this is first node to be inserted at this index
            if (head == NULL)
            {
                // Set table at hash_index to point to node n.
                table[hash_index] = n;
            }
            // If n is not the first node, point n->next to the existing first node and table at hash_index to point to n
            else
            {
                n->next = head;
                table[hash_index] = n;
            }
        }
        // Close file and return true as dictionary has been hashed and loaded
        fclose(dict);
        return true;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate through every field in table
    for (int i = 0; i < N; i++)
    {
        // Traverse nodes at each index in table
        node *list = table[i];
        while (list != NULL)
        {
            // Free memory
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
