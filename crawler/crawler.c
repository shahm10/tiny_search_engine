/* 
crawls the web and retrieves webpages straring from a "seed" URL 
- parses the seed webpage
- extracts any embedded URLs
- retrieves each of those pages
- limit its exploration to a given "depth"

execute from a command line
    ./crawler seedURL pageDirectory maxDepth 
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "webpage.h"
#include "pagedir.h"
#include "set.h"
#include "bag.h"
#include "hashtable.h"
#include <sys/stat.h>
#include <sys/types.h>

void crawler (char *seedURL, char *pageDirectory, int maxdepth);

int main (int argc, char *argv[]) {
    //REQUIREMENTS
    //check1: number of conditions
    

    if (argc !=4) {
        fprintf (stderr, "Please input: crawler seedURL pageDirectory maxDepth\n");
        exit (1);
    }

    char *seedURL = malloc (strlen(argv[1]) +1);
    char *pageDirectory = malloc (strlen(argv[2]) +1);

    sscanf (argv[1], "%s", seedURL);
    sscanf (argv[2], "%s", pageDirectory);

    //check2: seedURL must be internal URL
    if (!IsInternalURL(seedURL)) {
        fprintf (stderr, "Initial URL not internal\n");
        exit (2);
    }
    //check3: pageDirectory is the pathway
    struct stat validdir; 

    if (stat (pageDirectory, &validdir) != 0 ) {
        fprintf (stderr, "File cannot access %s\n", argv[2]);
        exit (3);
    }
    if (!S_ISDIR (validdir.st_mode)) {
        fprintf (stderr, "Not a valid directory\n");
        exit (4);
    }
    //check4: maxdepth needs to be an integer >0 
    int maxdepth;
    if (sscanf (argv[3], "%d", &maxdepth) == 1 ) {
        if (maxdepth < 0) {
            fprintf (stderr, "Depth is not a positive integer");
            exit (5);
        }
    } else {
        fprintf (stderr, "Depth is not even an integer");
        exit (6);
    }

    printf( "Crawling...\n");
    crawler (seedURL, pageDirectory, maxdepth);

    free(pageDirectory);
    return 0;
}

//crawler function: loops over pages to explore
//methods: pagefetcher, pagescanner, pagesaver 

void crawler (char *seedURL, char *pageDirectory, int maxdepth) {
    //need to initialize
    bag_t *bag = bag_new ();
    if (bag == NULL) {
        fprintf (stderr, "failed to initialize \n");
        exit (7);
    }
    hashtable_t *hashtable = hashtable_new(100);
    if (hashtable == NULL) {
        fprintf (stderr, "Initialization for hashtable failed");
        exit (8);
    }
    //make a webpage for the seedURL, marked with depth 0
    webpage_t *page = webpage_new(seedURL, 0, NULL);
    //add that page to the bag of webpages to crawl
    // URL to hashtable of URL seen 
    bag_insert (bag, page);
    hashtable_insert (hashtable, seedURL, "");

    //while there are more webpages to crawl
    //extract a webpage item from the bag
    webpage_t *cPage;

    int ID = 1; //the document ID = need to be incremented by page
    while ((cPage = bag_extract(bag))  != NULL) {
        //pagefetcher to retrieve a webpage for that URL
        //if any error in fetching? log the error and continue to next URL
        //if page fetched
        if (webpage_fetch (cPage)) { //must later free html
            printf ("fetched: \n");
            //pagesaver to write the webpage to pageDirectory with ID
            if (!pagesaver(cPage, pageDirectory, ID)) {
                printf ("page not saved");
            }

             //else continue
        } else {
            fprintf(stderr, "Fetching failed\n");
            
        }
        //if webpage depth < maxDepth, explore webpage
        if (webpage_getDepth(cPage) < maxdepth) {
            //pagescanner to parse and extract all embedded URLs
            printf ("Scanning...\n");
            //webpage_getNextURL
            int depth = webpage_getDepth(cPage);
            int pos  = 0;
            char *URL;

            while ((URL = webpage_getNextURL(cPage, &pos)) != NULL) {
                //printf ("Found url");
                //normalize the URL and make sure it is internal
                if (NormalizeURL(URL) && IsInternalURL(URL)) {
                    //printf("URL: normalized and is internal");

                    //insert URL into the hashtable of URLS seen
                    if (hashtable_insert(hashtable, URL, &ID)) {
                        //printf ("Inserted");
                        //if not in the table
                        //make a new webpage for that URL, depth +1
                        printf ("depth: %d\n", depth);
                        printf ("found URL: %s\n\n", URL);
                        webpage_t *nPage = webpage_new (URL, (depth + 1), NULL); 
                        //add new webpage to the bag of webpages to be crawled
                        bag_insert(bag, nPage);
                    } else {
                        //printf ("URL has already been visited");
                        free (URL);
                    }
                } else {
                    free (URL);
                }
            }
        }
        webpage_delete(cPage);
        ID += 1;
    }
    //free everything
    bag_delete (bag, NULL);
    hashtable_delete (hashtable, NULL);
}