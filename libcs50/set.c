/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Seung Hyun Hahm, January 2020
 */ 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

/**************** local types ****************/
// set_list contains the linked list 
typedef struct set_list {
  char *key;                
  void *item;
  struct set_list *next; //set_list's next in a pointer
} set_list_t;

/**************** global types ****************/
typedef struct set {
  struct set_list *head;       // head of the list of set_list
} set_t;

/**************** local function ****************/
// create a set
static set_list_t *set_list_new(char *key, void *item) {
	set_list_t *set_list = malloc(sizeof(set_list_t));
	//if malloc has error, return NULL
	if (set_list == NULL) {
		return NULL;
	} else {
		set_list->key = key;
		set_list->item = item;
		return set_list;
	}
}

/**************** global function set_new ****************/
// create a empty set 
set_t *set_new(void)
{
    //set initialized 
	set_t *set = malloc(sizeof(set_t));
	if (set == NULL) {
		return NULL;
	} else {
		set->head = NULL;
		return set;
	}
}

/**************** set_find () ****************/
void *set_find (set_t *set, const char *key)
//return the item associated with the given key 
{
	if ((set != NULL) && (key != NULL)) {
		for (set_list_t *set_list = set->head; set_list != NULL; set_list = set_list->next) {
			//check if desired key exists
			if (strcmp (key, set_list->key) == 0) {
				return set_list->item;
			}
		}
	}
	//return NULL if set is NULL, key not found, key is NULL
	return NULL;
}

/**************** set_insert() ****************/

bool set_insert (set_t *set, const char *key, void *item)
//insert item identified by a key(string), into the given set
//need to make a copy of key string; memory
{
	if (set != NULL && key != NULL && item != NULL) {
		//copy the key string
		
		//if key not found, insert
		if (set_find(set, key) == NULL) {
			char *keycopy = malloc(sizeof(key)); //free this later
			strcpy (keycopy, key);
			//create new set
			set_list_t *init = set_list_new(keycopy, item);
			init->next = set->head;
			set->head = init;
			//true if new item is inserted 
			return true;
		}
		else {
			return false;
		}
	}
	//false if key exists, parameter is NULL, or error
	return false;
}

/**************** set_print() ****************/
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) )
//print whole set, through itemprint 
//print {} when itemprint is NULL 
//comma separated list of items {}
{
	if (set != NULL) {
		if (fp != NULL) { //file open for writing?
			fputc('{', fp);
			for (set_list_t *set_list = set->head; set_list != NULL; set_list = set_list->next) {
				if (itemprint != NULL) {
					(*itemprint)(fp, set_list->key, set_list->item);
					if (set_list->next != NULL) {
						fputc(',', fp);
					}
				}
			}
			//close the bracket after printing all sets 
			fputc('}', fp);
			fputc('\n', fp);
		}
	}
	if (set == NULL) {
		fputs("(null)\n", fp);
	}
}

/**************** set_iterate() ****************/
//iterate over the set, calling  a funciton on each item
void set_iterate(set_t *set, void *arg,void (*itemfunc)(void *arg, const char *key, void *item) )
{
	if (set != NULL && itemfunc != NULL) {
		//call itemfunc once for each item
		for (set_list_t *set_list = set->head; set_list != NULL; set_list = set_list->next) {
			(*itemfunc)(arg, set_list->key, set_list->item);
		}
	}
}

/**************** set_delete()****************/
void set_delete(set_t *set, void (*itemdelete)(void *item))
//detele set, use itemdelete func
//if itemdelete != NULL, call each item 
{
	if (set != NULL){
		//if itemdelete != NULL, call each item 
		if (itemdelete != NULL) {
			for (set_list_t *set_list = set->head; set_list != NULL; ) {
				if(set_list->item !=NULL){
					(*itemdelete)(set_list->item);
				}
				set_list_t *next = set_list->next;
				free(set_list->key); //free key
				free(set_list);
				set_list = next; //move on to the next
			}
			free (set);
		} else {
			//need to free even when itemdelete == NULL
			for (set_list_t *set_list = set->head; set_list != NULL; ) {
				set_list_t *next = set_list->next;
				free(set_list->key); //free key
				free(set_list);
				set_list = next; //move on to the next
			}
			free (set);
		}
	}
}
