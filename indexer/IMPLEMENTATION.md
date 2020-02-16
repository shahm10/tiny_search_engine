# CS50 Lab 3
## Seung Hyun Hahm, CS50 Winter 2020

### Indexer
`crawler` reads the documents in `pageDirectory` output by the `crawler`, build an *inverted index* mappin gfrom words to documents, and writet aht index to a file. It is called *inverted index* because it maps from words to documents, the opposite of a document which is a sequence of words. 

### User interface
`./indexer ../crawler/pageDirectory indexfile`

### Indexer Pseudo code
Please see [DESIGN.md]() 

### Breakdown of functions for index
Below are the breakdown of how I built the index structure, as in `indexer.c` I mostly just called the functions I already constructed.

```c
/*********** helper functions ***************/

void print_counters (void *file, const int ID, const int count);
void print_index (void *file, const char *word, void *item);
void indexdelete (void *item);


/**************** global types ****************/
typedef struct index index_t;
/**************** functions ****************/

/**************** index_new ****************/
/* Create a new (empty) index.
 *
 * Caller provides:
 *   number of slots
 * We return:
 *   index data structure with hashtable
 * Caller is responsible for:
 *   later calling hashtable_delete.
 */
index_t *index_new (const int num_slots);

/**************** index_insert ****************/
/* Insert item, which is the counters_t
 *
 * Caller provides:
 *   valid pointer to index, valid normalized word, valid pointer for item.
 * Notes:
 *   The *item should be called by the counters_t under the key (word)  
 */
void index_insert (index_t *index, const char *word, const int ID);

/**************** index_build ****************/
/* Builds the index with the given structure to a file
 *
 * Caller provides:
 *   valid directory created by the crawler directory
 *   valid index 
 *
 * Notes:
 *   valid directory should be checked inside this function
 *   reads the word from each directory/ID
 */
void index_build (char *directory, index_t * index);

/**************** index_delete ****************/
/* Delete the indexx, calling a delete function on each item 
 *
 * Caller provides:
 *  valid pointer to the function that handles the deleting
 * Notes:
 *  call hashtable_delete to free the memory inside the index 
 */
void index_delete(index_t *index);

/**************** index_save ****************/
/* Saves the index to a file 
 * 
 * Caller provides:
 *  valid pointer to the function that handles the writing the index
 * 
 * Notes:
 *  call print_index = a helper function 
 */
void index_save (FILE *fp, index_t *index);

/**************** index_load ****************/
/* 
 * retrieves the index from a file 
 * 
 */
void indexLoad(FILE *fp, index_t *index);

```

### Major data structures

Inside the index, I use two helper modules
`counters.h` `hashtable.h`modules
I use them to initialize, insert, iterate, and free.
Below are the implementations of `counters` and `hashtable`.

```c
/* Create a new (empty) counter structure.
 *
 * We return:
 *   pointer to a new counterset; NULL if error. 
 * We guarantee:
 *   counterset is intialized empty.
 * Caller is responsible for:
 *   later calling counters_delete();
 */
counters_t *counters_new(void);

/**************** counters_add ****************/
/* Increment the counter indicated by key.
 * 
 * Caller provides:
 *   valid pointer to counterset, and key(must be >= 0)
 * We return:
 *   the new value of the counter related to the indicated key.
 *   0 on error (if ctrs is NULL or key is negative)
 * We guarantee:
 *   counter values will always be >= 1.
 * We do:
 *  ignore if ctrs is NULL or key is negative.
 *  if the key does not yet exist, create a counter for it and initialize to 1.
 *  if the key does exist, increment its counter by 1.
 */
int counters_add(counters_t *ctrs, const int key);

**************** counters_set ****************/
/* Set the current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset, 
 *   key(must be >= 0), 
 *   counter value(must be >= 0).
 * We return:
 *   false if ctrs is NULL, if key < 0 or count < 0, or if out of memory.
 *   otherwise returns true.
 * We do:
 *   If the key does not yet exist, create a counter for it and initialize to
 *   the given value. 
 *   If the key does exist, update its counter value to the given value.
 */
bool counters_set(counters_t *ctrs, const int key, const int count);

/**************** counters_delete ****************/
/* Delete the whole counterset.
 *
 * Caller provides:
 *   a valid pointer to counterset.
 * We do:
 *   we ignore NULL ctrs.
 *   we free all memory we allocate for this counterset.
 */
void counters_delete(counters_t *ctrs);

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
 *   true if new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/**************** hashtable_delete ****************/
/* Delete hashtable, calling a delete function on each item.
 *   if hashtable==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the hashtable itself.
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );

/**************** hashtable_iterate ****************/
/* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to hashtable, 
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (key, item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, key, item).
 * Notes:
 *   the order in which hashtable items are handled is undefined.
 *   the hashtable and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
                       void (*itemfunc)(void *arg, const char *key, void *item) );

```

### Errors_in indexer
* Exit 1: 
	* Few arguments: Please type ./indexer pageDirectory indexFilename"
* Exit 2: pageDirectory is not created by crawler 
	* "Incorrect directory"
* Exit 3: if pageDirectory is NULL
* Exit 4: if newindexfile cannot be created 
	* "Unable to be created"
* Exit 5: if first argument is not given 
	* "INCORRECT DIRECTORY"

### Assumption
Assume .crawler is inside the directory created by crawler 

### Check for memory leak 
All the valid outputs are demonstrated in 
`testing.sh` shell script. 
The ouput of the testing can be found in `testing.out` 
In order to access `testing.out` type `make test &> testing.out`
Memory leaks can be checked in `testing.sh` and `testing.out`


### Compilation

To compile, type `make` 
To clean, type `make clean`



