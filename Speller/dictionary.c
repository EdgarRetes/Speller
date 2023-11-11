// Implements a dictionary's functionality

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
}
node;

// TODO: Choose number of buckets in hash table

//prime number to have a better spreading of buckets

//increase N until its faster

const unsigned int N = 112129;

// Hash table
node *table[N];


//adittional table
//the maximum letters of a word is 31
//long aux_hash[676][31];
//int aux_hash2[26][26];

//counter of words in dictionary

int counter = 0;

//check if it loads for size function

bool loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //gets the word of the text and assigns a value for its bucket

    int search_bucket = hash(word);

    //auxiliar node to search in each linked list

    node *cursor = table[search_bucket];


    //condition to end the loop when there are no more elements to search
    while (cursor != NULL)
    {
        //if the word pointed by cursor matches the word in the text its spelled correctly
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        //if not keep looking by passing into the next linked node
        else
        {
            cursor = cursor->next;
        }
    }

    //if not found it is mispelled returns false

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    /* not fast enough
    //assuming the longest word posible contains 31 letters
    //buckets would be letters * length (676)

    //take first letter of the word
    int get_letter1 = toupper(word[0]) - 'A';

    //get the lenght of the word
    int length = strlen(word);

    if (length > 1)
    {
        int get_letter2 = toupper(word[1]) - 'A';
        int get_coordinate = aux_hash2[get_letter1][get_letter2];
        return aux_hash[get_coordinate][length - 1];
    }

    else
    {
        return aux_hash[get_letter1 * 26][length - 1];
    }
    */

    //the value of the word is divided with MOD to get a bucket from within N
    //this allows the code to have less collisions

    //the time changes evertime I run it but it checks faster most of the times
    //outperforms holmes most of the times

    int add_char = 0;
    int l = strlen(word);

    for (int i = 0; i < l; i++)
    {
        add_char = add_char * 31 + toupper(word[i]);
    }

    return add_char % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    /* not fast enough
    //get the pair of letters aa, ab, ..., tb, tc, ...

    int pair = 0;

    for (int first = 0; first < 26; first++)
    {
        for (int second = 0; second < 26; second++)
        {

            aux_hash2[first][second] = pair;
            pair++;

        }
    }



    //set all values in the 2d array
    int value = 0;

    for (int y = 0; y < 676; y++)
    {
        for (int x = 0; x < 31; x++)
        {
            aux_hash[y][x] = value;
            value++;
        }
    }
    */
    // TODO

    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    //string of the word for scan to write in

    char *word = malloc(LENGTH + 1 * sizeof(char));

    while (fscanf(dict, "%s", word) != EOF)
    {

        node *new_word = malloc(sizeof(node));

        if (new_word == NULL)
        {
            return false;
        }

        strcpy(new_word->word, word);
        new_word->next = NULL;

        int bucket = hash(word);

        //if there isn't a word set it sets the new_word

        if (table[bucket] == NULL)
        {
            table[bucket] = new_word;

            counter++;
        }

        //if there is an existing word change pointers

        else
        {
            new_word->next = table[bucket]->next;

            table[bucket]->next = new_word;

            counter++;
        }

    }
    fclose(dict);
    free(word);
    return loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded == false)
    {
        return 0;
    }
    return counter;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //loop to free all the buckets
    for (int i = 0; i < N; i++)
    {
        //set cursor to the table in bucket i
        node *cursor = table[i];

        //free tmp while there are still elements of linked lists
        while (cursor != NULL)
        {
            //set tmp to cursor
            node *tmp = cursor;
            //pass cursor to the next node
            cursor = cursor->next;
            //free tmp
            free(tmp);
        }

    }
    return true;
}

