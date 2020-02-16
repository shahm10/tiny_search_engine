/* 
 * indextest.c -loads the index and save it in different file 
 *
 * Seung Hyun Hahm - February 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "jhash.h"
#include "hashtable.h"
#include "index.h"
#include "counters.h" 
#include "pagedir.h"
#include "word.h"

int main (const int argc, char *argv[]) {
    //check if correct number of arguments
    if (argc != 3) {
        printf ("Exactly 2 files should be passed\n");
        exit (5);
    }

    index_t *index2 = index_new (500);
    FILE *oldIndex; //create an oldIndex file
    FILE *newIndex; //create a newIndex file
    oldIndex = fopen(argv[1], "r");
    newIndex = fopen(argv[2], "w");

    //check if both files are readable or writeable 
    if (oldIndex == NULL || newIndex == NULL) {
        printf ("Files do not exist or cannot be written\n");
        exit (6);
    }

    //retrives the index2 from the oldIndex 
    indexLoad(oldIndex, index2);
    //saves the index2 into a newIndex file 
    index_save(newIndex, index2);
    fclose(oldIndex);
    fclose(newIndex);
    //free the items 
    index_delete(index2);

    
    
    return 0;
}

