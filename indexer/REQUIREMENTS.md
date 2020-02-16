# CS50 Lab 5
## Seung Hyun Hahm, CS50 Winter 2020

### Indexer

1. Execute from a command line with usage syntax
	* ./indexer pageDirectory indexFilename
	* validate its command-line arguments using pagedir.c
	* where pageDirectory is the pathname of a directory produced by the Crawler, and
	* where indexFilename is the pathname of a file into which the index should be written; the indexer creates the file (if needed) and overwrites the file (if it already exists).
	* the indexer should be able to handle cases in which the index file is not a valid pathname and/or the crawler directory is not a valid.
2. read documents from the pageDirectory, each of which has a unique document ID, wherein
	* the document id starts at 1 and increments by 1 for each new page,
	* and the filename is of form pageDirectory/id,
	* and the first line of the file is the URL,
	* and the second line of the file is the depth,
and the rest of the file is the page content (the HTML, unchanged).
3. build an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and “normalize” the word before indexing. Here, “normalize” means to convert all letters to lower-case.

4. create a file indexFilename and write the index to that file, in the format described below.

### Assumptions_Indexer
* `pageDirectory` has files named 1,2,3,.. without gaps.
* `pageDirectory` can be formated as `word  1 3`

### Index Tester

1. execute from a command line with usage syntax
	* ./indextest oldIndexFilename newIndexFilename
	* where `oldIndexFilename` is the name of a file produced by the indexer, and
	* where `newIndexFilename` is the name of a file into which the index should be written.
2. load the index from the `oldIndexFilename` into an inverted-index data structure.
3. create a file `newIndexFilename` and write the index to that file, in the format described below.


### Assumptions_Index tester
* Does not need to validate its command line unless wrong nubmer of inputs are put. 
* The content of the index file follows `word   1 3` 
* When recreating an index structure need not have to have extensive error checking. 