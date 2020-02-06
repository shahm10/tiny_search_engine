/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Seung Hyun Hahm, January 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "jhash.h"
#include "hashtable.h"

// Array of sets 
/**************** global types ****************/
//set contains all the linked list needed
typedef struct hashtable {
    set_t **index;
    int num_slots; 
} hashtable_t;

/**************** global functions ****************/
// create a hashtable
//return: pointer to new hashtable 
hashtable_t *hashtable_new (const int num_slots) {
    if (num_slots > 0) {
        hashtable_t *hashtable = malloc (sizeof (hashtable_t));
        //give memory to hashtable's each index   
        hashtable->index = calloc(num_slots, sizeof(set_t*));
        hashtable->num_slots = num_slots;

        //create a set_new in each index of hashtable
        for (int i = 0; i < num_slots; i++) {
            hashtable->index[i] = set_new();
        }
        if (hashtable !=NULL && hashtable->index != NULL) {//|| hashtable->index == NULL
            return hashtable;
        }
    }
    return NULL;
}

/**************** hashtable_find () ****************/
void *hashtable_find(hashtable_t *ht, const char *key) 
// return the item associated with the given key 
//if found, pointer to the item for the given key
{
	if (ht != NULL && key != NULL) {
        //each index = set; so implement set_find 
        //below integer will be the address of the keys (hash mod) 
        int index_num = JenkinsHash(key, ht->num_slots);
        //find the given key in the index_num
        return set_find(ht->index[index_num], key);
    }
    //return NULL if hashtable is NULL, key not found, key is NULL
	return NULL;
}

/**************** hashtable_insert() ****************/

bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
//insert item identified by a key(string), into the given hashtable
//need to make a copy of key string; memory
{
	if (ht != NULL && key != NULL && item != NULL) {
		//true if new item was inserted 
		//copy the key string through set_insert
        int index_num = JenkinsHash (key, ht->num_slots);
        return set_insert(ht->index[index_num], key, item);
    }
    else {
        //false: key exists in ht, any parameter is NULL, or error
        return false;
    }
}

/**************** hashtable_print() ****************/
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
//print whole table through itemprint 
//one line per hash slot, with no items, if NULL itemprint.
//otherwise, one line per hash slot, listing (key,item) pairs in that slot.
//nothing, if NULL fp.
// "(null)" if NULL ht.
{
	if (ht != NULL) {
		if (fp != NULL) { 
			for (int i = 0; i < ht->num_slots; i++) {
				fprintf(fp, "Index[%d] ", i);
                if (itemprint != NULL) {
                    set_print(ht->index[i], fp, (*itemprint));
                } else {
                    set_print(ht->index[i], fp, NULL);
                }
        }
    } 
    } else {
        fputs("(null)\n", fp);
    }
}

/**************** hashtable_iterate() ****************/
//iterate over the set, calling  a funciton on each item
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
	if (ht != NULL && itemfunc != NULL) {
		//call itemfunc once for each item
        for (int i = 0; i < ht->num_slots; i++) {
            set_iterate (ht->index[i], arg, (*itemfunc));
        }
    }
}
    
/**************** hashtable_delete()****************/
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) )
{
	if (ht != NULL){
		if (itemdelete != NULL) {
            for (int i = 0; i < ht->num_slots; i++) {
                set_delete(ht->index[i], (*itemdelete));
            }
        }
        free (ht->index);
        free (ht);
    }
}
