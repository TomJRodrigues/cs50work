/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Tom Rodrigues tomjrodrigues@gmail.com 30-6-2015
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"

// size of hashtable
#define SIZE 1000000

// defines the node structure
typedef struct node
{
   char word[LENGTH + 1];
   struct node* next;
}
node;

// initializes hashtable
node* hashtable[SIZE] = {NULL};
 
// hash function
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // alphabet case
        if(isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        
        // comma case
        else
        {
            n = 27;
        }
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}

// create global variable for dictionary size
int dictionarysize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create temporary storage variable
    char temp[LENGTH + 1];
    
    // store word in temp, after lowcasing it
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';
    
    // hash temp and see if the index exists
    int index = hash(temp);
    
    // if exists strcmp, if not, false
    if (hashtable[index] == NULL)
    {
        return false;
    }
    
    // create cursor to compare to word
    node* cursor = hashtable[index];
    
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory using a hash table.  Returns true if successful else false.
 */ 
bool load(const char* dictionary)
{
    // open dictionary
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file.");
        return false;
    }
    
    // create array container for each scanned word
    char word[LENGTH + 1];
    
    while (fscanf(dict, "%s\n", word) != EOF)
    {
        // increment dictionary size
        dictionarysize++;
        
        // allocate memory for new word
        node* newWord = malloc(sizeof(node));
        
        // put word in the new node
        strcpy(newWord->word, word);
        
        // find what index of array the word should go into
        int index = hash(word);
        
        // if hashtable is empty at index, insert
        if (hashtable[index] == NULL)
        {
            hashtable[index] = newWord;
            newWord->next = NULL;
        }
        
        // if hashtable is not empty, append
        else
        {
            newWord->next = hashtable[index];
            hashtable[index] = newWord;
        }
    }
  
    // close dictionary
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictionarysize > 0)
    {
        return dictionarysize;
    }
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // create an indexing variable
    int index = 0;
    
    while (index < SIZE)
    {
        // if empty move on
        if (hashtable[index] == NULL)
        {
            index++;
        }
        // if not empty, start freeing
        else
        {
            while (hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }   
            index++;
        }
        
    }
    
    return true;
}