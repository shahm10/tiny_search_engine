# CS50 Lab 3
## Seung Hyun Hahm, CS50 Winter 2020

### Crawler
`crawler` crawls the web and retrieves webpages starting from a "seed" URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given "depth."

### Required Conditions
1. Needs to execute from a command line with usage syntax `./crawler seedURL pageDirectory maxDepth`
2. Crawl all pages reachable from seedURL
3. Pause at least one second before page fetches
4. Wrtie each explored page to the pageDirectory with a unique document ID. 


### Usage
First need to create a directory inside the `crawler/` directory by typing `mkdir [directoryname]`
`./crawler seedURL pageDirectory maxDepth`

### Assumption
Creating a directory before compiling or running is essential. 
Only use internal URL
Delete the directory you used 

### Compilation

To compile, type `make` 
To clean, type `make clean`

### ETC
In `testing.sh` testing for Wikipedia page is not included. However, I did run it in the program and it was verified that the fils created match expectations. I simply did not include them because it takes too much time. 

Further information is found in [IMPLEMENTATION.md]

