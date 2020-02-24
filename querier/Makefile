
# Makefile for 'querier' 
# Seung Hyun Hahm, February, 2020

C = ../common
#library name 
L = ../libcs50

PROGS = querier 
OBJS = querier.o

#libs tell the linker to link with the library 
LIBS = $C/common.a $L/libcs50-given.a
#link with libcs50/common lib 
#LLIBS = $(C)/common.a $(L)/libcs50.a 

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

# tells the compiler to lookk for include files in the directoreis 
#FLAGS = # -DAPPTEST # - DMEMTEST
# above are the macros 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I$C
CC = gcc
MAKE = make

.PHONY: all test valgrind clean

######default#####
#all: $(PROGS) 

$(PROGS): $(OBJS) $(LIBS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGS) 

######crawler dependencies#####
querier.o: $(LIBS)
#bash -v = verbose 
test: $(PROGS) testing.sh
	bash testing.sh 

clean:
	rm -f core 
	rm -f *~ *.o *.dSYM
	rm -f $(PROGS)
	rm -f stocks
	rm -f vgcore*
	rm -f testing.out

