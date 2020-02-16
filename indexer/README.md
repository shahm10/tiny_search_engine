# CS50 Lab 5
## Seung Hyun Hahm, CS50 Winter 2020

### Indexer
`indexer` extracts all the keywords for each stored webpage and creates a lookup table that maps each word found to all documents (webpages) where the word was found. 

### Indextest
`indextest.c` reads the index from the given file and and saves it to a different file.

### Required Conditions
Further information in [REQUIREMENTS.md]()


### Usage
`./indexer ../crawler/pageDirectory indexfilename`
`./indextest filename1 filename2`

### Assumption
In the pageDirectory created by the `crawler`, make sure to write ".crawler" before running index or indextest. 
Such action is written in `testing.sh` 

### Compilation

Go to indexer directory 
To compile, type `make` 
To clean, type `make clean`

### ETC
In `testing.sh` testing for Wikipedia page is not included. However, I did run it in the program and it was verified that the fils created match expectations. I simply did not include them because it takes too much time. 


