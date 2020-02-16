/* 
 * word.c -lowers the characters of the word page 
 *
 * Seung Hyun Hahm - February 2020
 */


#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "webpage.h"
#include "file.h"
#include "word.h"
#include <ctype.h>


char *NormalizeWord (char *word) {
    //check if the word is not NULL
    if (word != NULL) {
        for (char *w = word; *w != '\0'; w++) {
            //lower-case each character
            *w = tolower (*w);
        }
    }
    return word;
}