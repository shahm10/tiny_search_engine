# CS50 Lab 6
## Seung Hyun Hahm, CS50 Winter 2020

### User Interface 
The querier reads from the command-line; it must have three arguments and stdin

`./querier pageDirectory indexFile`

where `pageDirectory` is the pathname of a directory produced by the Crawler
and where `indexFile` is the pathname of a file produced by the Indexer. 

### Inputs and Outputs
Input: a standard input or from a file 

Output: We return a score of each word in each document ID. 

### Major Data Structures
The following are structures made inside the `querier.c`

1. query structure: stores counters of result variable and counters of temporary variable. 
2. scoreID strcuture: stores the document ID and the score. 
3. scoreofarray strcutures: stores an array of scoreID structure. 

### Functional decomposition into modules
We anticipate the following modules or functions:

1. main, which passes arguments and checks for valid input and run and print the query scores.
2. scoreID, a type construct that builds the ID and score. 
3. scoreofarray, a type construct that builds an array of struct scoreID.
4. query, a type construct that builds the query.
5. sep_words, separate the individual words into the array. 
6. make_lower, make all words lowercase.
5. counters_union, when it sees an "or" and it is done looking for word, it merges the two counters associated with each words.
6. coutners_intersect, it returns the counters with scores less than the other scores. 
7. union_iterator, a helper function for counters_union.
8. intersect_iterator, a helper function of coutners_intersect.
9. scorearray, returns an entire array of the counter result with each key as the document ID. 
10. sortrank, takes the completearray that is made through `scorearray` and sort them with scores in descending order. 
11. countmatch, counts how many documents match inside the directory files. 


And some helper modules that provide data structures:

1. *counters* to keep track of the words's score repeated in the page.
2. *query* to keep track of two words's counters.  
3. *array_t* to keep track of the array of word's counters. 


### Pseudo code for logic/algorithmic flow

Brief function: querier reads the index produced by the Indexer and the page files produced by the Crawler, to interactively answer written queries entered by the user. 

1. execute from a command line with usage syntax
`./querier pageDirectory indexFilename`
where `pageDirectory` is the pathname of a directory produced by the Crawler, and
where `indexFilename` is the pathname of a file produced by the Indexer.
2. load the index from indexFilename into an internal data structure.
3. read search queries from stdin, one per line, until EOF.
	1. check if the stdin has any non-alphabetic characters
	2. check if it uses any invalid "and" or "or" words.
	2. if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
	3. print the ‘clean’ query for user to see.
	4. use the index to identify the set of documents that satisfy the query, as described below.
	5. if the query is empty (no words), print nothing.
	6. if no documents satisfy the query, print `No documents match`.
	7. otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
	8. Exit with zero status when EOF is reached on stdin.



### Testing plan

*Integration testing*. Assemble the querier and test it as a whole using `testing.sh` In each case, examine the ouput carefully to be sure they print the correct query. 
Here, I do not include the test with wiki because it takes too much time. 

1. Test the program with various forms of incorrect command-line arguments to ensure theat its command-line parsing, and validation of those parameters, works correctly.
2. Test the querier with a non-valid arguments
3. Test the querier with an incorrect pagedirectory 
4. Test the querier with a correct input
5. Test the `indextest` with a correct input
6. Compare the file output by calling `indexsort.awk`
7. Check if two created files match or fail to match
8. Run two cases of `indexer` and `indextest` with `myvalgrind` to check for memory leaks