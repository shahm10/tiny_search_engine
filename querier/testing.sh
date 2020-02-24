#!/bin/sh

# testing.sh
# Author:Seung Hyun Hahm
# Date: February, 2020
#
# testing.sh is a shell script for integration for testing querier.c
#
# usage: bash testing.sh
#

#Define variables

seedURL=http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
File_incorrect=incorrectsyntax
File_correct=testfile
TESTDIR=data/letters
INDEX=data/index_letters
####################
### First setup for Querier ###

echo "Hi! Now testing for querier "
echo "If the directory does not exist, create one"

cd ..
echo "Making a directory in crawler/"
mkdir data
cd data
mkdir letters

cd ../../crawler

echo "Now running crawler"

./crawler $seedURL ../data/letters 3

cd ..data/letters
touch .crawler
cd ../../indexer

echo "Crawler file has been created"

echo "Now onto the Indexer!"

echo "Creating an IndexFile inside the indexer"
./indexer ..data/letters ../data/index_letters

cd ..

echo "The setup is complete"
echo "Now going into the querier"
cd ../querier

#run querier
### These tests should fail 
######################################
### These tests should fail ####
echo " "
echo "Now these tests should fail"

echo "Too few arguments"
#few arguments
./querier ../data/letters

#no arguments
./querier

#incorrect directory 
./indexer ../data/notcrawlerfile oldindexfile

echo " "
echo "Now, creating a correct querier"
#correct output
./querier ../data/letters ../data/index_letters

echo "First, test with incorrect syntax"
./querier ../data/letters ../data/index_letters < $File_incorrect

echo "Now, test with a different file"
./querier ../data/letters ../data/index_letters < $File_correct


echo "If the testing is finished, need to clean up the files created"

cd ..
rm -rf data

echo "finish"
