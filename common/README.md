# CS50 Lab 3
## Seung Hyun Hahm, CS50 Winter 2020

### common

Currently, in common directory we have `pagedir.h` which checks and writes the URL, depth, and HTML in the directory. 
This can be used in `crawler` module to further augment the function.  

### pagedir.c
pagedir.c checks whether the pathname provided is a valid directory and is writable. 
It saves the webpage in the directory.
It saves the webage's URL, depth, and HTML

### Usage
call it inside the `crawler.c`

### Compilation

To compile, type `make` 
If successful, it creates `common.a` that can be used in crawler. 
