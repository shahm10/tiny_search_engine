# CS50 Lab 6
## Seung Hyun Hahm, CS50 Winter 2020

### Querier
`Querier` reads the index file produced by the `indexer`, and the page fiels produced by the `crawler`, and answers search queries submitted by standard input. 

### Required Conditions
1. Needs to execute from a command line with usage syntax `./querier pageDirectory indexFilename`.
Further informations are in [REQUIREMENTS.md]() 


### Usage
First need to create a directory inside the `crawler/` directory by typing `mkdir [directoryname]`. Then make an indexfile inside the `indexer/` directory. Then use
`./querier [pageDirectory] [indexfile]`.
More specifically, `./querier ../crawler/[crawlerfilename] ../indexer/[indexfilename]`. 

### Assumption
Inside the directory created by the `crawler`, need to type `.crawler` before running the code. 

### Compilation

To compile, type `make` 
To clean, type `make clean`

### Functionality

1. Querier prints the set of documents that contain all the words in the query. It ignores if the words are not in the query, through only putting in the score greater than 0 inside the `completearray`. 

2. Querier prints the document set in decrasing order by score, through the function `sortrank` by getting the input of the `array_t *completearray`. 

Further information is found in [IMPLEMENTATION.md]

