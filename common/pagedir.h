/* 
 * pagedir.h
 *
 * Seung Hyun Hahm - February 2020
 */


/* Short Description: 
pagedir.h checks whether the pathname provided is a valid directory and is writable. 
It saves the webpage in the directory.
It saves the webage's URL, depth, and HTML

*/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include "file.h"

/****************FUNCTION**********************/

/**************** pagesaver ****************/
/* 
 * Caller provides:
 *   valid page, pageDirectory, ID
 * We return:
 *   True if it saved page, URL, depth, and HTML
 */
bool pagesaver (webpage_t *page, char *pageDirectory, int ID); 

/**************** isCrawlerDirectory ****************/
/* 
 *
 * Caller provides:
 *   valid pointer to hashtable, valid string for key.
 * We return:
 *   true if dir is created by crawler directory 
 * Notes:
 *   Assumption: Assume ".crawler" is inside the directory created by crawler
 */
bool isCrawlerDirectory (char *dir);

/**************** webpage_t pagedir_load ****************/
/* Return the webpage
 *
 * Caller provides:
 *   valid file 
 */
webpage_t *pagedir_load (FILE *fp);

#endif //__PAGEDIR_H