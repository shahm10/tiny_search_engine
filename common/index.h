/* 
 * index.h
 *
 * Seung Hyun Hahm - February 2020
 */


#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "jhash.h"
#include "hashtable.h"
#include "counters.h" 
#include "pagedir.h"
#include "word.h"



/*********** helper functions ***************/

void print_counters (void *file, const int ID, const int count);
void print_index (void *file, const char *word, void *item);
void indexdelete (void *item);


/**************** global types ****************/
typedef struct index index_t;
/**************** functions ****************/

/**************** index_new ****************/
/* Create a new (empty) index.
 *
 * Caller provides:
 *   number of slots
 * We return:
 *   index data structure with hashtable
 * Caller is responsible for:
 *   later calling hashtable_delete.
 */
index_t *index_new (const int num_slots);

/**************** index_insert ****************/
/* Insert item, which is the counters_t
 *
 * Caller provides:
 *   valid pointer to index, valid normalized word, valid pointer for item.
 * Notes:
 *   The *item should be called by the counters_t under the key (word)  
 */
void index_insert (index_t *index, const char *word, const int ID);

/**************** index_build ****************/
/* Builds the index with the given structure to a file
 *
 * Caller provides:
 *   valid directory created by the crawler directory
 *   valid index 
 *
 * Notes:
 *   valid directory should be checked inside this function
 *   reads the word from each directory/ID
 */
void index_build (char *directory, index_t * index);

/**************** index_delete ****************/
/* Delete the indexx, calling a delete function on each item 
 *
 * Caller provides:
 *  valid pointer to the function that handles the deleting
 * Notes:
 *  call hashtable_delete to free the memory inside the index 
 */
void index_delete(index_t *index);

/**************** index_save ****************/
/* Saves the index to a file 
 * 
 * Caller provides:
 *  valid pointer to the function that handles the writing the index
 * 
 * Notes:
 *  call print_index = a helper function 
 */
void index_save (FILE *fp, index_t *index);

/**************** index_load ****************/
/* 
 * retrieves the index from a file 
 * 
 */
void indexLoad(FILE *fp, index_t *index);

#endif //__INDEX_H