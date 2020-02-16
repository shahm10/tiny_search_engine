# Makefile for 'crawler' 
# Seung Hyun Hahm, February, 2020

# Function: Build everything from the top-level directory by 'make'
# clean up everything by typing m'make clean'

#These are the variables 

# need path to get to common
C = ../common
#library name 
L = ../libcs50

PROG = crawler

OBJS = crawler.o
#libs tell the linker to link with the library 
LIBS = $(L)/libcs50-given.a $(C)/common.a
#link with libcs50/common lib 
#LLIBS = $(C)/common.a $(L)/libcs50.a 

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

# tells the compiler to lookk for include files in the directoreis 
#FLAGS = # -DAPPTEST # - DMEMTEST
# above are the macros 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I $(L) -I $(C)
CC = gcc
MAKE = make

.PHONY: all test valgrind clean

######default#####
#all: $(PROGS)
#it runs by order <- make ('all')
######crawler#####
#left side is a target; right side is the dependencies 
#@ = automatic variable 
crawler: crawler.o
		$(CC) $(CFLAGS) $^ $(LIBS) -o $@

######crawler dependencies#####
#These are recommended 
#crawler.o: $(L)/webpage.h $(C)/pagedir.h
#	$(L)/memory.h $(L)/bag.h $(L)/hashtable.h 

#bash -v = verbose 
test: $(PROGS) testing.sh
	bash testing.sh
	
#include rm -f core 
clean:
	rm -f core 
	rm -f *~ *.o *.dSYM
	rm -f $(PROGS)
	rm -f stocks
	rm -f vgcore*

