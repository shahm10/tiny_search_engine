/* 
 * indexer.c -builds an index from the index data structure 
 * inspired by code given for activity in lecture 24
 * Seung Hyun Hahm - February 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../libcs50/set.h"
#include "../libcs50/jhash.h"
#include "../libcs50/hashtable.h"
#include "../common/index.h"
#include "../libcs50/counters.h" 
#include "../common/pagedir.h"
#include "../common/word.h"
#include <ctype.h>
#include <unistd.h>
#include "file.h"

/* process a query and ranking the results are tricky 
start with a simplified test

function: loads the index into memeory (a data structure we devleoped for the indexer)
and then prompts the user for queries 

queries = comprised of words, with optional and/or operators 
*/

typedef struct query {
    counters_t *result;
    counters_t *temp;
} query_t;

typedef struct scoreID {
    int ID;
    int score;
} score_t;

typedef struct scoreofarray {
    score_t **Array;
} array_t; 

char** sep_words (char* input, int *);
void make_lower(char **array);
int inputstatus (char *input);
int countwords (char **words);
int andorcheck (char *words[], int size);
int countfiles (char *pageDirectory);
counters_t *findindex (index_t *index, const char *word);
counters_t *scores (char **words, int countwords, index_t *index);
void union_iterator (void *arg, const int key, int count);
void counters_union (counters_t *word1, counters_t *word2);
query_t *query_new (counters_t *word1, counters_t *word2);
counters_t *findindex (index_t *index, const char *word);
void intersect_iterator (void *arg, const int key, int count);
void counters_intersect (counters_t* ct1, counters_t* ct2);
int compare (const void *firstobject, const void *secondobject);
void countdocuments (void *arg, const int key, const int count);
array_t *scorearray (counters_t *result, int documents, int file_num);
array_t *sortrank (array_t *completearray, int documents);



int main (const int argc, char *argv[]) {
    FILE *indexfile;
    //index delete at the end 

    
    if (argc != 3) {
        fprintf (stderr, "Usage: ./querier [pageDirectory] [indexFilename] \n");
        exit (1);
    }
    //if correct arguments, go into the query program
    if ((argv[1]) != NULL) {
        //check if it is directory created by crawler
        if (!isCrawlerDirectory(argv[1])) {
            fprintf (stderr, "Directory not created from the crawler \n");
            exit (2);
        }
    }

    if (argv[2] != NULL) {
        //check if it is produced by the indexer
       // sprintf (indexfilename, ".indexer/%s", argv[2]);
        indexfile = fopen (argv[2], "r");
        if (indexfile == NULL) {
            fprintf (stderr, "Indexfile can't be read \n"); 
            exit (3);
        } 
    }

    //load the index with count the number of lines
    int index_lines = lines_in_file(indexfile);
    int slots;
    slots = (index_lines * 50);
    index_t *index = index_new(slots);
    
    indexLoad (indexfile, index); 

    char **words;
    char *input;
    int count;
    printf ("Query? ");

    //1. check if input is correct 
    while ((input = freadlinep (stdin)) != NULL) {

        //checks if the inputstatus is correct: 1 means it is correct
        int status = inputstatus (input);
        if (status == 2) {
            printf ("\n no alphabet");
            // break;
        }
        if ((status == 1)) {
            //Read the input when it passes all conditions
            //Then it goes to check for "and" and "or" errors 
            // words are the character array 
            words = sep_words (input, &count);
            printf ("\n print clean query\n");
            for (int j = 0; j < count; j++) {
                printf ("%s ", words[j]);
            }

            int size = countwords (words);
            int file_num = countfiles (argv[1]);

           //2. valid input check = and/or
           int exit = andorcheck (words, size);
           //only if it passes the "andorcheck"
           if (exit == 0) {
                //create a counter result
                counters_t *result = scores (words, size, index);
                //count the number of results
                int documents = 0; 
                counters_iterate(result, &documents, countdocuments);

                //if no documents match 
                if (documents == 0) {
                    printf ("\nNo documents match. \n");
                }
                //If there are documents that match 
                //print the number of documents that match 
                else { 
                    printf ("Matches %d documents (ranked): \n", documents);
                
                    //create an array of scores 
                    array_t *rankedscore = scorearray(result, documents, file_num);
                    //rank the array 
                    array_t *rankedscores = sortrank (rankedscore, documents);

                    //print the array 
                    for (int i = 0; i < documents; i++) {
                        int ID = rankedscores->Array[i]->ID;
                        int scores = rankedscores->Array[i]->score;

                        char filename [200];
                        sprintf (filename, "%s/%d", argv[1], ID);

                        FILE *fp = fopen (filename, "r");
                        char *url = freadlinep(fp);

                        printf ("\nScore: %3d  doc:  %3d: %s\n", scores, ID, url);

                        fclose(fp);
                        free(url);
                        }
                        
                        for (int c = 0; c < documents; c++) {
                            free(rankedscores->Array[c]);
                        }
                        free(rankedscores->Array);
                        free (rankedscores);
                    }
                    counters_delete(result);
                }
                free (words);
            }
        free (input);
        printf ("\nQuery?: ");
        }
        free(input);
        index_delete(index);

        fclose (indexfile);
        return 0;
}

//check whether the input is correct
// int correct (char *input) {
//     char 


//only return the characters 
char** sep_words (char* input, int * num) {
    //set array of char*
    char** words; 

    words = calloc (strlen(input)/2+1, sizeof (char*));

    //split words
    int count = 0;
    
    for (char *rest = input; *rest != '\0'; ) {
        //starting address of a word
        char *start;
        //seek the start of a word


        for (start = rest; (!isalpha (*start)) && *start != '\0'; start++) {}
        //seek the end of the word 
        for (rest = start; isalpha (*rest) && *rest != '\0'; rest++) {}

        if (*rest != '\0') {
            *rest++ = '\0';
            //insert \0 to signal the end of the word
        }

        if (*start != '\0') {
            words[count++] = start;
        }
    }
    make_lower (words);
    *num = count;

    return words; 
}

void make_lower(char **array)
{   
    int i = 0, j;
    while (array[i] != NULL){
        j = 0;
        while (array[i][j] != '\0') {
             array[i][j] = tolower(array[i][j]);
             j++;
        }
        i++;
    }
}    

//checks if the input is valid without and and or 
int inputstatus (char *input) {
    int inputstatus = 0;
    char *start = input;

    for (int i = 0; start[i] != '\0'; i++){
        if (isalpha (start[i])) {
            inputstatus = 1;
        } 
        if (isspace (start[i])) {
            inputstatus = 1;
        }
        //only if it sees a non-space non-alphabet character
        if (!isalpha (start[i]) && !isspace (start[i])) {
            inputstatus = 2;
            // fprintf (stderr, "\nError: non-alphabet letter detected \n");
            
        }
    }
    return inputstatus;
}

//count words
int countwords (char **words) {
    int numofwords = 0;
    for (int i = 0; (words[i] != NULL); i++) {
        numofwords++;
    }

    //printf ("%d", numofwords);

    return numofwords; 
}

//and function
int andorcheck (char *words[], int size) {
    int exitand = 0;

     //if first word or last word is "and"; error
    if ((strcmp (words[0], "and") == 0) || (strcmp (words[0], "or") == 0)) {
        fprintf (stderr, "Error: AND or OR cannot come at front \n"); 
        exitand = 1;
    }
    //if last word is and; error

    //can't have 'and' and 'or' together
    //check the back 
    if (exitand != 1) {
    for (int i = (size - 1); i >= 0; i--) {
        if (words[i] != NULL) {
            if ((strcmp(words[i], "and") == 0) || (strcmp (words[i], "or") == 0)) {
                fprintf (stderr, "AND or OR cannot come at last");
                exitand = 1;
                break;
            }
            else {
                exitand = 0;
                break;
            }
        }
    }
    }

    if (exitand != 1){
        for (int i = (size - 1); i >= 0; i--) {
            if (words[i] != NULL) {
                if ((strcmp (words[i], "and") == 0) || (strcmp (words[i], "or") == 0)) {
                    if ((strcmp (words[i-1], "and") == 0) || (strcmp (words[i-1], "or") == 0)) {
                        fprintf (stderr, "and and or can't be together\n");
                        exitand = 1;
                        break;
                    }
                    else {
                        exitand = 0;
                    }
                }
            }
        }
    }
    printf ("%d", exitand);
    return exitand;
}

int countfiles (char *pageDirectory) {
    FILE *fp;
    char crawlerfiles [200];

    int ID = 1;

    sprintf (crawlerfiles, "%s/%d", pageDirectory, ID);
    fp = fopen (crawlerfiles, "r");
    while (fp != NULL) {
        fclose (fp);
        ID++;
        sprintf (crawlerfiles, "%s/%d", pageDirectory, ID);
        fp = fopen (crawlerfiles, "r");
    }
    return (ID -1);
}

//iterate over one set and for each item
// check whether the document exists in the other set
//update the first set according to what you find 

static inline int min (const int a, const int b) {
    return (a < b ? a : b);
}

void counters_intersect (counters_t* ct1, counters_t* ct2) {

    query_t query_new = {ct1, ct2};

    counters_iterate (ct1, &query_new, intersect_iterator);
}

void intersect_iterator (void *arg, const int key, int count) {

    query_t *query = arg; 
    //query->result; query->other

    //save the minimum count to the set
    //update the first set according to what you find 
    //int min_count = counters_get (query->result, key);
    counters_set (query->result, key, min(count, counters_get (query->temp, key)));
}



//the set of documents that match either word is the union
// score = sum of count for each document
//iterate over 2nd set 
void counters_union (counters_t *word1, counters_t *word2) {
    //need to set temp to counter 0
    query_t query = {word1, word2};

    counters_iterate (word2, &query, union_iterator);

}

void union_iterator (void *arg, const int key, int count) {
    query_t *query = arg;

    int initial = counters_get (query->result, key);
    if (initial > 0 ) {
        counters_set (query->result, key, count + initial);
    } else {
        counters_set (query->result, key, count);
    }
}


counters_t *scores (char **words, int countwords, index_t *index) {

    //set very 1st word's counter into result
    //treat all as 'ands' and find minimum and then look for or 

    printf ("inside the scores\n");
    
    counters_t *result = counters_new();
    if (result == NULL) {
        fprintf (stderr, "memory not correctly allocated\n");
        exit (10);
    }
    counters_t *temp;


    //loop through every word in the array
    bool empty = true; 

    for (int i = 0; i < countwords; i++) {

        //0 means it is equal 
        if (strcmp (words[i], "and") == 0) {
            //do nothing
            printf ("\n do nothing\n");
        }
        //if it sees an "or"
        else if (strcmp (words[i], "or") == 0) {
            printf ("\n OR is detected\n");
            empty = true;
            counters_union (result, temp);
            counters_delete(temp);
        }
        else {
            if (empty) {
                printf ("\n empty is detected\n");
                counters_t *current = findindex (index, words[i]);
                counters_print (current, stdout);
                temp = counters_new();
                if (current != NULL) {
                    counters_union(temp, current); 
                }
                empty = false;
            }
            else {
                counters_t *current = findindex (index, words[i]);
                if (current != NULL) {
                    counters_intersect (temp, current);
                }
            }
        }
    }

    counters_union (result, temp);
    counters_delete (temp);

    printf ("\n printing the result\n");
    counters_print (result, stdout);
    return result;

    counters_delete(result);
}


array_t *scorearray (counters_t *result, int documents, int file_num) {
    array_t *completearray = calloc (documents, sizeof(score_t)); //contains array and elements
    completearray->Array = calloc (documents, sizeof(score_t));

    if (completearray == NULL) {
        fprintf (stderr, "\n can't allocate memory\n");
    }
    if (completearray->Array == NULL) {
        fprintf (stderr, "can't either");
    }

    int space = 0;

    for (int i = 1; i <= file_num; i++) {
        int score = counters_get(result, i); 

        if (score > 0) {
            score_t *final = malloc(sizeof(score_t));

            final->ID = i;
            final->score = score;
            
            completearray->Array[space] = final;

            space++;

        }
       
    }
    return completearray;
}

array_t *sortrank (array_t *completearray, int documents) {
    printf ("\nInside the sorting\n");

    for (int i = 0; i < (documents - 1); i++) {
        //descending order
        for (int j = i+1; (documents - j); j++) {
            if (completearray->Array[i]->score < completearray->Array[j]->score) {
                score_t *element = completearray->Array[i];
                completearray->Array[i] = completearray->Array[j];
                completearray->Array[j] = element;
            }
        }
    }
    // free (element);
    return completearray;

}

//check how many document match exist
void countdocuments (void *arg, const int key, const int count) {
    //skip when it is 0 
    if (count > 0 ) {
        int *documents = arg;
        (*documents)++;
    }
}

