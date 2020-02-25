/* 
 * index.c - CS50 'index' module
 *
 * see index.h for more information.
 *
 * Seung Hyun Hahm, February 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../libcs50/set.h"
#include "../libcs50/jhash.h"
#include "../libcs50/hashtable.h"
#include "index.h"
#include "../libcs50/counters.h" 
#include "pagedir.h"
#include "word.h"



/*********** helper functions ***************/
counters_t *findindex (index_t *index, const char *word);

void printhash(FILE *fp, const char *key, void *item) {
    //store item as a integer
    int *number = item;
    fprintf(fp, "%s-%d", key, *number);
}
void print_counters (void *file, const int ID, const int count) {
    FILE *fp = file;
    fprintf (fp, "%d %d ", ID, count);
}

void print_index (void *file, const char *word, void *item) {
    FILE *fp = file;
  counters_t *ctrs = item;
  if (fp != NULL && ctrs != NULL) {
        fprintf (fp, "%s  ", word);
        counters_iterate (ctrs, fp, print_counters);
        fprintf (fp, "\n");
  }
}

void indexdelete (void *item) {
    counters_t *ctrs = item;
    counters_delete (ctrs);
}

// construct an index structure
/**************** global types ****************/
typedef struct index {
    hashtable_t *hashtable;
    int num_slots; 
} index_t;

/**************** global functions ****************/
// create an new index
// later responsible for calling index_delete 
index_t *index_new (const int num_slots) {
    index_t *index = malloc (sizeof (index_t));
    if (index == NULL) {
        fprintf (stderr, "Error: index not created \n");
        exit (1);
    }
    index->hashtable = hashtable_new (num_slots);
    index->num_slots = num_slots; 

    return index; 
}

//index_insert (insert a counter inside the item under the word)
void index_insert (index_t *index, const char *word, const int ID) {
    //if index, word, ID is all appropriate
    if (index != NULL && word != NULL && ID >= 0) {
        //insert the counters_t inside the 'item' of hashtable
        counters_t *ctrs = hashtable_find (index->hashtable, word);
        if (ctrs == NULL) {
            //create a new counter
            counters_t *new_ctrs = counters_new();
            if (new_ctrs == NULL) {
                fprintf (stderr, "No new counter created\n");
                exit (3);
            }
            counters_add (new_ctrs, ID);
            hashtable_insert (index->hashtable, word, new_ctrs);
        } else {
            //increment the counter associated with the ID 
            counters_add (ctrs, ID); 
        }
    }
}

//check if the directory is created by the crawler in the main function 
void index_build (char *directory, index_t * index) {
    webpage_t *word_page;
    int ID = 1; 
    char *word;

    char worddir [200];
    FILE *fp;
    sprintf (worddir, "%s/%d", directory, ID);
    fp = fopen (worddir, "r");

    while (fp != NULL) {

        //need a loop to increase ID 
        word_page = pagedir_load(fp);
        //return word_page 
        int pos = 0;
        char *result;

        while ((result = webpage_getNextWord (word_page, &pos)) != NULL) {
             if (strlen (result) >= 3) {
                 word = NormalizeWord (result);
                index_insert (index, word, ID); 
            }
            free (result);
        }

        fclose(fp);
        webpage_delete (word_page);
        
        ++ID;
        sprintf (worddir, "%s/%d", directory, ID);
        fp = fopen (worddir, "r");
    }

}

void index_delete(index_t *index) {
    //call hashtable_delete
    hashtable_delete (index->hashtable, (*indexdelete));
    free (index);
}

void index_save (FILE *fp, index_t *index) {
    //may or may not already exist 
    hashtable_iterate (index->hashtable, fp, print_index);
}

counters_t *findindex (index_t *index, const char *word) {
    //returns the counter assoicated with the word 
    counters_t *item = hashtable_find(index->hashtable, word);
    //counters_print (item, stdout);

    //counters_print (item, stdout);
    if (item == NULL) {
        counters_t *item = counters_new();
        hashtable_insert (index->hashtable, word, item); 
    }
    //counters_print (item, stdout);

    return item;
}

//index_load
void indexLoad(FILE *fp, index_t *index) {
// // //load the index from the oldIndexFilename into an inverted-index data structure???
// // // take an index file and loads it into an index data structure??
//     //create an index from a file
     char *word;
     int ID;
     int count;

    if (fp == NULL) {
        printf ("The file has nothing written\n");
    } else {
        while((word = freadwordp(fp)) != NULL) {
            counters_t *counters = counters_new();
            hashtable_insert (index->hashtable, word, counters);
            while (fscanf (fp, "%d %d", &ID, &count) == 2) {
                counters_set (counters, ID, count);
            }
            free (word);
        }
    }
}
    