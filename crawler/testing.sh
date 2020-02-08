#!/bin/bash/


# Testing script for crawler.c
# Author: Seung Hyun Hahm
# Date: Feb 5, 2020
#
# usage: bash  testing.sh


# Define variables
seedURL=http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html

seedURL2=http://old-www.cs.dartmouth.edu/~cs50/index.html

externalURL=www.google.com


#####################################
### These tests should fail ###

echo "Hi! Now testing for crawler "
echo "These tests should fail "

mkdir TEST
# 1 argument
echo "One argument "

./crawler

# 2 arguments
echo "2 arguments "

./crawler $seedURL

# 3 arguments
echo "3 arguments "

./crawler $seedURL TEST

# 4 arguments + externalURL
echo "4 arguments + externalURL "

./crawler $externalURL TEST 2

# 5 non-existent server
echo "non-existent server "

./crawler http://old-www.cs.noschool.edu/~cs50/data/tse/non-existent/index.html TEST 1

# 6 valid server but non-existent page
echo "Valid server but non-existent page "

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/NO.html TEST 1

# 7 Invalid depth
echo "Invalid depth "

./crawler $seedURL TEST a2


######################################
### These tests should pass ####
echo " "
echo " Now these tests should pass"

echo " At depth 0"
# at depth 0
./crawler $seedURL TEST 0


# at depth 1
echo " At depth 1"
./crawler $seedURL TEST 1

# at depth 2
echo " At depth 2"
./crawler $seedURL TEST 2

# at depth 3
echo "At depth 3"
./crawler $seedURL TEST 3

# at depth 4
echo "At depth 4"
./crawler $seedURL TEST 4

# at depth 5
echo " At depth 5"
./crawler $seedURL TEST 5

echo "At depth 1a it should pass"
./crawler $seedURL TEST 1a


echo " With test2: testing with different seedURL in different directory"
mkdir TEST2
echo "TEST2 directory created"

echo "With a seedURL_crossed: TEST2"
./crawler $seedURL2 TEST2 1

echo " At depth 2"
./crawler $seedURL2 TEST2 2

echo "At depth 3"
./crawler $seedURL2 TEST2 3

echo "At depth 4"
./crawler $seedURL2 TEST2 4

echo "At depth 5"
./crawler $seedURL2 TEST2 5

# If everything is done correctly
echo "SUCCESS!"

### etc.
echo "Testing if there are memory leaks"
echo "sample Memory leak"
valgrind --leak-check=full ./crawler $seedURL TEST 2
