# CS50 Lab 5
## Seung Hyun Hahm, CS50 Winter 2020

### User Interface 
The indexer's only interface with the user is on the command-line; it must have three arguments

`./index ../crawler/TEST filename`

### Inputs and Outputs
Input: A valid directory created by crawler
		and a command line

`./indexer pageDirectory indexfilename`

Output: We return a type integer and the file  created by the function. 

### Functional decomposition into modules
We anticipate the following modules or functions:

1. main, which passes arguments and initializes other modules.
2. pagedir, return the lines in the page fetched. 
3. word, a hleper function that normalizes the word.
4. index, a type construct that builds he index.
5. indexer, read the documents in the `pageDirectory` output by the `crawler` and create an inverted index.  

And some helper modules that provide data structures:

1. *counters* to keep track of the words repeated in the page.
2. *hashtable* to keep track of the words and counters.  


### Pseudo code for logic/algorithmic flow _ only for indxer

1. Process and validate command-line parameters
2. Initialize data structure index
3. create the `newindexFile` if it does not exist.
	4. Check if the `pagedirectory` is created by crawler by calling `isCrawlerDirectory`
	5. initialize data structure index
	6. call index_build which builds the index
	7. call index_save to save the index to a file.  	
	5. clean up datas structures

### Pseudo code for logic/algorithmic flow _ only for index

1. construct a data structure `index` by using `hashtable`.
2. create a *hashtable of countersets* to map from a word to a list of pairs (docID, count)
3. create `index_insert` to insert a counter inside the item under the word
4. `index_build` gets the normalzied word and insert it into `index_insert`
5. `index_delete` frees the items by using hashtable_delete
6. `index_save` iterates through the hashtable and prints its output by calling a helper function.
7. `index_load` gets the data from th e index and creates the index.


### Helper functions

1. `print counters` receives the file pointer and prints the ID and count in a format [1 1]
2. `print_index` receives the file pointer and initialize the counters. If initialized successfully, print the word
3. `indexdelete`while hashtable is also deleted, it needs to delete the *item*, the counters too. 

### Testing plan

*Integration testing*. Assemble the indexer and test it as a whole using `testing.sh` In each case, examine the ouput carefully to be sure they print the correct index. 
Here, I do not include the test with wiki because it takes too much time. 

1. Test the program with various forms of incorrect command-line arguments to ensure theat its command-line parsing, and validation of those parameters, works correctly.
2. Test the indexer with a non-valid arguments
3. Test the indexer with an incorrect pagedirectory 
4. Test the indexer with a correct input
5. Test the `indextest` with a correct input
6. Compare the file output by calling `indexsort.awk`
7. Check if two created files match or fail to match
8. Run two cases of `indexer` and `indextest` with `myvalgrind` to check for memory leaks