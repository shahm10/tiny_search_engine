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

### Assumption
Creating a directory before compiling or running is essential. 
Only use internal URL

### Compilation

To compile, type `make` 
To clean, type `make clean`

### ETC
Further information is found in [IMPLEMENTATION.md]
