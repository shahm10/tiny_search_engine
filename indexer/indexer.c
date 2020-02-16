/* 
 * indexer.c -builds an index from the index data structure 
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
    //command line: ./indexer pageDirectory indexFilename
    if (argc != 3) {
        fprintf (stderr, "Please type ./indexer pageDirectory indexFilename");
        exit (1);
    } else {
        if (!isCrawlerDirectory (argv[1])) {
            fprintf (stderr, "INCORRECT DIRECTORY ");
            exit (5);
        }
    }

    if (argv[1] != NULL) {
        //set pageDirectory file 
        FILE *pageDirectory = fopen (argv[1], "r");
        if (pageDirectory != NULL) {
            //check if the directory is created by crawler
            if (isCrawlerDirectory (argv[1])) {
                printf ("\n pageDirectory is crated by crawler\n");
            } else {
                fprintf (stderr, "Incorrect directory\n");
                exit (2);
            }
            fclose (pageDirectory);
        } else {
            exit (3);
        }

        //need to create a newindexFilename if not existing
        //has to overwrite if it already exists
        FILE *newindexFile;
        if ((newindexFile = fopen(argv[2], "w")) == NULL) {
            //need to create a newIndexFilename
            fprintf (stderr, "\n Unable to be created ");
            exit (4);
        }
        if (isCrawlerDirectory (argv[1])) {
            //create an index structure
            index_t *index = index_new (500);
            //builds the index from the directory 
            index_build (argv[1], index);
            //saves the built index into the newindexfile
            index_save (newindexFile, index);
            fclose (newindexFile);
            index_delete (index);
        }
    }
}