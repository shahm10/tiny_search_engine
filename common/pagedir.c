/* 
 * pagedir.c - functions for crawler
 * 
 * Seung Hyun Hahm - February 2020
 * 
 *
 */


#include "pagedir.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "webpage.h"
#include "file.h"

// for loading pages from a crawler output directory 
// if it can open a file dir/.crawler for reading then dir is a cralwer-produced diectory. 
// if not, it's not a crawler  produced direcotry 
bool isCrawlerDirectory (char *dir) {
    if (dir == NULL) {
        return false;
    }

    FILE *fp;
    char crawler_dir[200];
    //assume there is a .crawler inside the testdir 
    sprintf (crawler_dir, "%s/.crawler", dir);
    fp = fopen (crawler_dir, "r");
    if (fp != NULL) {
        fclose(fp);
        return true;
    } else {
        return false; 
    }

}

webpage_t *pagedir_load (FILE *fp) {

    char *url = freadlinep(fp);
    char *depth = freadlinep(fp);
    char *html = freadfilep(fp);

    //Gets the data from the valid FILE 
    webpage_t *word_page = webpage_new (url, atoi(depth), html);

    free (depth);
    return word_page;
    
}

bool pagesaver (webpage_t *page, char *pageDirectory, int ID) {
    //first, check for valid conditions
    if (page == NULL || pageDirectory == NULL || ID < 0) {
        return false; 
    }

    FILE *fp;
    char saved_dir[200];
    sprintf (saved_dir, "%s/%d" , pageDirectory, ID);
    
    //check if pageDirectory/ID can be opened 
    fp = fopen (saved_dir, "w");
    if (fp == NULL) {
        return false;
    } else {
        //1st line: URL
        fprintf (fp, "%s\n", webpage_getURL(page));
        //2nd line: depth
        fprintf (fp, "%d\n", webpage_getDepth(page));
        //3rd line: html 
        fprintf (fp, "%s", webpage_getHTML(page));
        fclose (fp);

    }

    return true; 
}