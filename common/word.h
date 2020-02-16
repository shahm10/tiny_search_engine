/* 
 * word.h
 *
 * Seung Hyun Hahm - February 2020
 */

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include "file.h"

/**************** NormalzieWord ****************/
/* Return the lower-cased word/character.
 *
 * Caller provides:
 *   word that is not converted to lower case yet.
 * We return:
 *   character word 
 */
char *NormalizeWord (char *word);

#endif //__WORD_H