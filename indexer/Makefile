# by default, build the indexer and indextest executalbe programs
# make clean = removes files produced by
# make or yoru tests
# make test target that tests your indexer 
#make test should run bash -v testing.sh


# Makefile for 'indexer' 
# Seung Hyun Hahm, February, 2020

C = ../common
#library name 
L = ../libcs50

PROGS = indexer 
PROGS2 = indextest

OBJS = indexer.o 
OBJS2 = indextest.o
#libs tell the linker to link with the library 
LIBS = $(C)/common.a $(L)/libcs50-given.a
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
all: $(PROGS) $(PROGS2)

$(PROGS): $(OBJS) $(LIBS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGS) 

$(PROGS2): $(OBJS2) $(LIBS)
		$(CC) $(CFLAGS) $(OBJS2) $(LIBS) -o $(PROGS2)

######crawler dependencies#####
#index.o: $L/index.h $L/file.h $L/counters.h $L/hashtable.h
indexer.o: $L/hashtable.h $L/counters.h $L/file.h $L/webpage.h $C/index.h $C/pagedir.h 
indextest.o: $L/hashtable.h $L/counters.h $L/file.h $L/webpage.h $C/index.h $C/pagedir.h 

#bash -v = verbose 
test: $(PROGS) $(PROGS2) testing.sh
	bash testing.sh 

clean:
	rm -f core 
	rm -f *~ *.o *.dSYM
	rm -f $(PROGS)
	rm -f $(PROGS2)
	rm -f stocks
	rm -f vgcore*

