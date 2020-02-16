# Makefile for 'common' 
# Seung Hyun Hahm, February, 2020

# Function: By default, build common.a library 
# must have clean target to remove files produced by Make 

#Builds common.a for use by progrma 
# need path to get to common
L = ../libcs50

OBJS = pagedir.o index.o word.o
LIBS = $(L)/libcs50-given.a
LIB = common.a 

#FLAGS = 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I $(L)
CC = gcc
MAKE = make

.PHONY: all clean

######default#####
all: $(LIB)

$(LIB): $(OBJS)
		ar cr $(LIB) $(OBJS) 

######crawler dependencies#####
#index.o: $L/index.h $L/file.h $L/counters.h $L/hashtable.h
pagedir.o: pagedir.h $L/file.h $L/webpage.h
word.o: word.h
index.o: index.h $L/hashtable.h $L/counters.h word.h 
clean:
	rm -f core
	rm -f $(LIB) *~ *.o *.dSYM
	rm -f $(LIB) *~ *.o *.a
