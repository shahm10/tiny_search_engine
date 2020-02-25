#!/bin/bash/


# Testing script for querier.c
# Assume all directories have been created. 
# Author: Seung Hyun Hahm
# Date: Feb, 2020
#
# usage: bash testing.sh


echo "Hi, this is a testing file for querier.c"

echo "First, assume all data/letters directory have been created for convenience with the same URL given from the lecture demo page provided in a course webpage"

echo "1. Test it with wrong syntax "
#1. with few arguments
./querier ../data/letters 

#2. with non-crawler created files
./querier ../data/non-crawler-created ../data/letters

#3. with non-indexer created files
./querier ../data/letters ../data/non-indexer


echo "2. the output of a wrong syntax, from a file incorrectsyntax "
echo "incorrectsyntax file has test cases for spaces, non-characters, and capitalization"
./querier ../data/letters ../data/index_letters < incorrectsyntax

echo "3. The output of a wrong and correct syntax, from a file testfile"

./querier ../data/letters ../data/index_letters < testfile


echo "4. sample valgrind check for the query"

valgrind --leak-check=full ./querier ../data/letters ../data/index_letters < testfile

valgrind --leak-check=full ./querier ../data/letters ../data/index_letters < incorrectsyntax


