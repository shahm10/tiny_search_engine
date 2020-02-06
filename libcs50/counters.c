/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * Seung Hyun Hahm, January 2020
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"


/**************** local types ****************/
typedef struct counterset {
  int key;                 
  int count;
  struct counterset *next; //counterset's next in a pointer
} counterset_t;

/**************** global types ****************/
typedef struct counters {
  struct counterset *head;       // head of the list of counterset
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counters.h for comments about exported functions */

/**************** local function ****************/
/* not visible outside this file */
static counterset_t *counterset_new(int key) {
	counterset_t *counterset = malloc(sizeof(counterset_t));
	//if malloc has error, return NULL
	if (counterset == NULL) {
		return NULL;
	} else {
		counterset->key = key;
		counterset->count = 0;
		return counterset;
	}
}

/**************** global function counters_new() ****************/
counters_t *counters_new(void)
{
	//counters initialized 
	counters_t *counters = malloc(sizeof(counters_t));
	if (counters == NULL) {
		return NULL;
	} else {
		counters->head = NULL;
		return counters;
	}
}

/**************** counters_get() ****************/
int counters_get (counters_t *ctrs, const int key)
{
	if (ctrs != NULL && key >= 0) {
		for (counterset_t *counterset = ctrs->head; counterset != NULL; counterset = counterset->next) {
			if (counterset->key == key) {
				return counterset->count;
			}
		}
	}
	//return 0 if ctrs is NULL or key not found
	return 0;
}

/**************** counters_add() ****************/

int counters_add (counters_t *ctrs, const int key)
{
	if (ctrs != NULL && key >= 0) {
		//if the key does not exist, create a counter for it
		// and initialize it to 1
		if (counters_get(ctrs, key) == 0){
			counterset_t *init = counterset_new(key);
			init->count = 1;

			if (init != NULL) {
				init->next = ctrs->head;
				ctrs->head = init;
			}
		} else {
			for (counterset_t *counterset = ctrs->head; counterset != NULL; counterset = counterset->next) {
				if (counterset->key == key) {
					counterset->count += 1;
					return counterset->count;
				}
			}
		}
	}
	return 0;
}

/**************** counters_set() ****************/
// boolean value

bool counters_set (counters_t *ctrs, const int key, const int count)
{
	if (ctrs != NULL && key >= 0 && count >= 0) {
		if (counters_get(ctrs, key) == 0) {
			counters_add(ctrs, key);
			return true;
			
		}
		else {
			for (counterset_t *counterset = ctrs->head; counterset != NULL; counterset = counterset->next) {
				if (counterset->key == key) {
					counterset->count = count;
					return true; 
					
				}
			}
		}
	}
	return false;
}
/**************** counters_print() ****************/
void counters_print (counters_t *ctrs, FILE *fp)
{
	if (fp != NULL) {
		if (ctrs != NULL) {
			fputc('{', fp);
			for (counterset_t *counterset = ctrs->head; counterset != NULL; counterset = counterset->next) {
				fprintf(fp, "%d=%d", counterset->key, counterset->count);

				if (counterset->next != NULL){
					fputc(',', fp);
				}
			}
			fputc('}', fp);
		}
		else {
			fputs("(null)\n", fp);
		}
	}
}

/**************** counters_iterate() ****************/
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count))
{
	if (ctrs != NULL && itemfunc != NULL) {
		//call itemfunc once for each item
		for (counterset_t *counterset = ctrs->head; counterset != NULL; counterset = counterset->next) {
			(*itemfunc)(arg, counterset->key, counterset->count);
		}
	}
}

/**************** counters_delete()****************/
void counters_delete(counters_t *ctrs)
{
	if (ctrs != NULL){
		for (counterset_t *counterset = ctrs->head; counterset != NULL;) {
			counterset_t *next = counterset->next;
			free (counterset); //free counterset
			counterset = next; //move on to the next
		}
		free (ctrs);
		
	}
}
