# CS50 Lab 3
## Seung Hyun Hahm, CS50 Winter 2020

### Crawler
`crawler` crawls the web and retrieves webpages starting from a "seed" URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given "depth."

### User interface
`crawler seedURL pagedirectory maxDepth`

### Crawler Pseudo code
1. Execute from a command line as shown in the User Interface
2. Parse the command line, validate parameters, initialize other modules
3. Make a webpage for the seedURL, marked with depth=0
4. Add that page to the bag of webpages to crawl
5. Add that URL to the hashtable of URLs seen
6. While there are more webpages to crawl,
	1. Extract a webpage (URL,depth) item from the bag of webpages to be crawled,
	2. pause for at least one second,
	3. use pagefetcher to retrieve a webpage for that URL,
	4. use pagesaver to write the webpage to the pageDirectory with a unique document ID, as described in the Requirements.
	5. if the webpage depth is < maxDepth, explore the webpage to find links:
		1. use pagescanner to parse the webpage to extract all its embedded URLs;
		2. for each extracted URL,
			1. ‘normalize’ the URL (see below)
			2. if that URL is not ‘internal’ (see below), ignore it;
			3. try to insert that URL into the hashtable of URLs seen
			4. if it was already in the table, do nothing
			5. if it was added to the table,
				1. make a new webpage for that URL, at depth+1
				2. add the new webpage to the bag of webpages to be crawled



### Breakdown of functions
```c
/* In the main, you check all the required conditions
1. check if correct number of conditions
2. check if seedURL is an internal URL
3. check if pageDirectoryis the pathway and whether 
it is writeable 
4. check if maxDepth is an integer > 0 
*/ 
int main (int argc, char *argv[])

/* In crawler function, it crawls the web by looping over pages to explore
1. First initialize the bag and hashtable
2. Make a webpage for the seedURL, marked with depth 0
3. While there are more webages to crawl, extract a webpage item from the bag
4. Make sure teh page is fetched
5. if webpage depth < amaxdepth, explore webpage
6. Then, go inside and pagescanner 
7. If it found the URL, make sure it is normalized and internal. 
8. Then, insert the URL into the hashtable of URLs seen
9. Then add new webpage to the bag of wepages to be crawled
10. free all the URL,
11. By calling webpage delete, free the currentPage
12. Then empty bag and hashtable. 
*/
void crawler (char *seedURL, char *pageDirectory, int maxdepth);

```

### Major data structures
```c
Inside the crawler, I use two helper modules.
`bag.h` `hashtable.h`modules
I use them to initialize, insert, extract, and free.
Below are the implementations of `bag` and `hashtable`.
/* Create a new (empty) bag; return NULL if error. */
bag_t *bag_new(void);

/* Add new item to the bag; a NULL bag is ignored; a NULL item is ignored. */
void bag_insert(bag_t *bag, void *item);

/* Return any data item from the bag; return NULL if bag is NULL or empty. */
void *bag_extract(bag_t *bag);
/* Delete the whole bag; ignore NULL bag.
 * Provide a function that will delete each item (may be NULL).
 */
void bag_delete(bag_t *bag, void (*itemdelete)(void *item) );


/* Create a new (empty) hashtable.
 *
 * Caller provides:
 *   number of slots to be used for the hashtable (must be > 0).
 * We return:
 *   pointer to the new hashtable; return NULL if error.
 */
hashtable_t *hashtable_new(const int num_slots);

/**************** hashtable_insert ****************/
/* Insert item, identified by key (string), into the given hashtable.
 *
 * We return:
 *   false if key exists in ht, any parameter is NULL, or error;
 *   true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/* Delete hashtable, calling a delete function on each item.
 *   if hashtable==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the hashtable itself.
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
```

### Errors
* Exit 1: 
	* Few arguments: Please input: crawler seedURL pageDirectory maxDepth
* Exit 2: seedURL must be internal URL
	* "Initial URL not internal"
* Exit 3: pageDirectory is cannot be accessed
	* "File cannot access"
* Exit 4: pageDirectory is not valid
	* "Not a valid directory"
* Exit 5: Whend `maxDepth` is invalid
	* "Depth is not a positive integer"
* Exit 6	
	* "Depth is not even an integer"
* Exit 7: Failed to initialize bag
	* "failed to initialize"
* Exit 8: Failed to initialize hashtable
	* "Initialization for hashtable failed"


### Assumption
Creating a directory before compiling or running is essential. 

### Check for memory leak 
All the valid outputs are demonstrated in 
`testing.sh` shell script. 
The ouput of the testing can be found in `testing.out` 
In order to access `testing.out` type `make test &> testing.out`
Memory leaks can be checked in `testing.sh` and `testing.out`

### Function prototypes
Except for `pagedir.c` which is a `pagesaver` function, other functions are directly implemented in `crawler.c`

### Compilation

To compile, type `make` 
To clean, type `make clean`



