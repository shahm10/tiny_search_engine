# CS50 Lab 3
## Seung Hyun Hahm, CS50 Winter 2020

### common

Currently, in common directory we have `pagedir.h` and `word.h` which checks and writes the URL, depth, and HTML in the directory. 
This can be used in `crawler` module to further augment the function.  
These can also be used in indexer to check for the correct directory and to normalize words 

### pagedir.c word.c
pagedir.c checks whether the pathname provided is a valid directory and is writable. 
It saves the webpage in the directory.
It saves the webage's URL, depth, and HTML

`word.c` normalizes the word
Another function returns the page with the URL, depth, and HTML

### Usage
call it inside the `crawler.c`
call it inside the indexer directory 

### Compilation

To compile, type `make` 
If successful, it creates `common.a` that can be used in crawler and indexer. 
