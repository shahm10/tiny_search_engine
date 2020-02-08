/* 
 * pagedir.c - functions for crawler
 * 
 * Seung Hyun Hahm - February 2020
 * 
 *
 */

//pagesaver - check whether the pathname is a pageDirectory and writable 
/* Short Description: 
pagedir.c checks whether the pathname provided is a valid directory and is writable. 
It saves the webpage in the directory.
It saves the webage's URL, depth, and HTML
*/

#include "pagedir.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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