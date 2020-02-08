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

/****************FUNCTION**********************
 * bool pagesaver () saves the page and its URL, depth, and HTML
*/

bool pagesaver (webpage_t *page, char *pageDirectory, int ID); 

#endif //__PAGEDIR_H