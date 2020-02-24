# CS50 Lab 6
## Seung Hyun Hahm, CS50 Winter 2020

### Querier
`Querier` reads the index file produced by the `indexer`, and the page fiels produced by the `crawler`, and answers search queries submitted by standard input.

### User interface
`./querier ../crawler/pageDirectory ../indexer/indexfile`

### Querier Pseudo code
Please see [DESIGN.md]() 

### Breakdown of functions for index
Below are the breakdown of how I built the query structure. 

```c

/**************** helper structs ****************/
/* struct name: query_t
* Contains:
*   counters_t *result
*   counters_t *temp;
*/
typedef struct query query_t;

/**************** score_t ****************/
/* Define a new struct.
 *
 * Contains: 
 *   int ID;
 *   int score;
 *  
 */
typedef struct scoreID score_t; 

/**************** array_t ****************/
/* Define a new struct with an array. 
 *
 * Contains: 
 *   score_t **Array;
 *
 */
typedef struct scoreofarray array_t;

/*********** helper functions ***************/

char** sep_words (char* input, int *);
void make_lower(char **array);
int inputstatus (char *input);
int countwords (char **words);
int andorcheck (char *words[], int size);
int countfiles (char *pageDirectory);
counters_t *findindex (index_t *index, const char *word);
counters_t *scores (char **words, int countwords, index_t *index);
void union_iterator (void *arg, const int key, int count);
void counters_union (counters_t *word1, counters_t *word2);
void intersect_iterator (void *arg, const int key, int count);
void counters_intersect (counters_t* ct1, counters_t* ct2);
void countmatch (void *arg, const int key, const int count);
array_t *scorearray (counters_t *result, int documents, int file_num);
array_t *sortrank (array_t *completearray, int documents);


/**************** sep words ****************/
/* Separate the individual words into an array.
 *
 * Caller provides:
 *   char * input;
 *   int *; 
 * Notes:
 *   Only go inside this function after all the conditions have been chekced. 
 * 	 Only take in the charcters 
 * 	Only when there is a valid input given.
 */
char** sep_words (char* input, int *);

/**************** make_lower ****************/
/* Convert all the characters into lower case. 
 *
 * Caller provides:
 *  Character **array.
 * Notes:
 *  Only go through this function inside the sep_words, which means correct input is given. 
 */
void make_lower(char **array);

/**************** inputstatus ****************/
/* Returns an inputstatus if the input is valid or not 
 * 
 * Caller provides:
 *  stdin
 * 
 * Return:
 *  1 means the input conditions are correct
 *  2 means the input conditions are wrong 
 */
int inputstatus (char *input);

/**************** countwords ****************/
/* Counts the number of words in the array 
 * 
 * Caller provides:
 * 	 char **words;
 */
int countwords (char **words);

/**************** andorcheck ****************/
/* Checks whether the stdin input has valid conditions of implementing "and" and "or"
 *
 * Caller provides:
 *   char *words[];
 *   int size; 
 * 
 * Return:
 * 		1: means the conditions are wrong
 * 		0: means the conditions are correct
 *  
 */
int andorcheck (char *words[], int size);

/**************** countfiles ****************/
/* Count the number of files inside the pageDirectory inside the crawler directory 
 *
 * Caller provides:
 *  Char *pageDirectory.
 * 
 * Returns:
 *  Number of files inside the crawler directory
 */
int countfiles (char *pageDirectory);

/**************** counters_t *findindex ****************/
/* Returns the counters_t of the word
 * 
 * Caller provides:
 *  index
 * 	char *word
 * 
 * Return:
 *  The counter associated with the given word in index
 */
counters_t *findindex (index_t *index, const char *word);

/**************** counters_t *scores ****************/
/* Calculate the scores inside the words in the query
 * 
 * Caller provides:
 * 	 char **words;
 * 	 int countwords;
 * 	 index_t *index;
 * 
 * Returns:
 * 		The complete scores of the each word in query in a counter structure
 */
counters_t *scores (char **words, int countwords, index_t *index);

/**************** counters_union ****************/
/* Merges the two counters associated with each word
 *
 * Caller provides:
 *   counters_t *word1;
 * 	 counters_t *word2;
 * 	 
 * 
 * Notes
 * 	  This function needs to be iterated by a helper function
 *  
 */
void counters_union (counters_t *word1, counters_t *word2);

/**************** union_iterator ****************/
/* A helper function to iterate thorough the above function: counters_union
 *
 * Caller provides:
 *  	void *arg;
 * 	 	const int key;
 * 		const int count;
 * 
 * Note:
 *  An iterator function to be called on counters_union
 */
void union_iterator (void *arg, const int key, int count);

/**************** counters_intersect****************/
/* Compares the counters associated with given words and return the counter assoicated with the minimum score. 
 * 
 * Caller provides:
 *  counters_t *ct1;
 * 	counters_t *ct2;
 * 
 * Return:
 *  The counter associated with less score of the counter. 
 */
void counters_intersect (counters_t* ct1, counters_t* ct2);

/**************** intersect_iterator****************/
/* A helper function for the counters_intersect 
 * 
 * Caller provides:
 * 	 void *arg;
 * 	 int key;
 * 	 int count;
 * 
 *
 */
void intersect_iterator (void *arg, const int key, int count);

/**************** countmatch ****************/
/* Counts how many documents match inside the directory files 
 *
 * Caller provides:
 *  	void *arg;
 * 	 	const int key;
 * 		const int count;
 * 
 * Returns:
 *  The number of documents that match
 */
void countmatch (void *arg, const int key, const int count);

/**************** array_t *scorearray ***************/
/* Returns the entire array of the counter result with each key as the document ID. 
 * 
 * Caller provides:
 *  counters_t *result;
 * 	int documents;
 *  int file_num;
 * 
 * Note:
 *  It only creates an array with a of a counter score greater than 0 
 */
array_t *scorearray (counters_t *result, int documents, int file_num);

/**************** array_t *sortrank r****************/
/* Sorts the completearray into a descending order based on the score 
 * 
 * Caller provides:
 * 	 array_t *completearray
 * 	 int documents;
 * 
 *
 */
array_t *sortrank (array_t *completearray, int documents);

```

### Major data structures

Inside the querier, I use two helper modules
`counters.h` `index.h` `file.h` modules
I use them to initialize, insert, iterate, and free.
Below are the implementations of `counters` and `index` and `file`

```c

/**************** lines_in_file ****************/
/* Returns the number of lines in the given file,
 * i.e., the number of newlines in the file.
 * (If the file does not end with a newline, it will undercount by one.)
 * On return, the file pointer is back to beginning of file.
 * This will not work for pipes or stdin when it is attached to keyboard.
 */
int lines_in_file(FILE *fp);
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

/**************** counters_set ****************/
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

/**************** index_delete ****************/
/* Delete the indexx, calling a delete function on each item 
 *
 * Caller provides:
 *  valid pointer to the function that handles the deleting
 * Notes:
 *  call hashtable_delete to free the memory inside the index 
 */
void index_delete(index_t *index);

/******** findindex *****/
/* returns the counters associated with the word in the index 
*/ 

counters_t *findindex (index_t *index, const char *word);

/**************** index_load ****************/
/* 
 * retrieves the index from a file 
 * 
 */
void indexLoad(FILE *fp, index_t *index);




```

### Errors_in Querier
* Exit 1: 
	* Incorrect number of inputs: Usage: ./querier [pageDirectory] [indexFilename]
* Exit 2: pageDirectory is not created by crawler 
	* "Directory not created from the crawler"
* Exit 3: If "indexfile can't be read"
* Exit 4: If complete array cannot allocate memory
	* "Cannot allcoate memory"
* Exit 5: If array of completearray cannot allocate memory
	* "Cannot allocate memory"
* Exit 6: if counters_t *result cannot be created 


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



