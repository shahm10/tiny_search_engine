#!/bin/bash/


# Testing script for index.c and indextest.c
# Author: Seung Hyun Hahm
# Date: Feb, 2020
#
# usage: bash testing.sh


# Define variables
seedURL=http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html

#####################################
### These tests should fail ###

echo "Hi! Now testing for indexer "
echo "If the directory does not exist, create one in crawler"
echo "Going into crawler/"

cd ../crawler
echo "Making a directory in crawler/"
mkdir crawlerfile

echo "Now running crawler"
./crawler $seedURL crawlerfile 3

cd crawlerfile
touch .crawler
cd ..

echo "Crawler file has been created"

echo "Now onto the Indexer!"

cd ../indexer

######################################
### These tests should fail ####
echo " "
echo "Now these tests should fail"

echo "Too few arguments"
#few arguments
./indexer ../crawler/crawlerfile 


#no arguments
./indexer


#incorrect directory 
./indexer ../crawler/notcrawlerfile oldindexfile

echo " "
echo "Next, create an index"
#correct output
./indexer ../crawler/crawlerfile oldindexfile


echo "Test if indextest works"
./indextest oldindexfile newindexfile

echo "Need to check if the outputs printed are same"

#use indexsort.awk
gawk -f indexsort.awk oldindexfile > oldindexfile.sorted
gawk -f indexsort.awk newindexfile > newindexfile.sorted

if cmp "oldindexfile.sorted" "newindexfile.sorted"
then
   echo "The files match"
else
   echo "The files are different"
fi

### etc.
echo "Testing if there are memory leaks"
echo "sample Memory leak"
valgrind --leak-check=full ./indexer ../crawler/crawlerfile oldindexfile
valgrind --leak-check=full ./indextest oldindexfile newindexfile

#At the end remove the directory in crawler to run multiple times
echo "Removing the crawler directory"
cd ../crawler
rm -rf crawlerfile
