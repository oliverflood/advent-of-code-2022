.RECIPEPREFIX = >
CFLAGS = -O
CC=g++

# good for any file
# src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

# new stuff
# SRC = $(obj) cpplite.cpp

LDFLAGS = -lm

myprog: $(obj)
> $(CC) $(CFLAGS) $@ $^ $(LDFLAGS)

# cpplite.o: cpplite.cpp
# > $(CC) $(CFLAGS) -c cpplite.cpp

.PHONY: clean
clean:
> rm -f $(obj) t


# CFLAGS = -O
# CC = g++

# NumTest: day16a.o cpplite.o
# > $(CC) $(CFLAGS) -o day16a.exe day16a.o cpplite.o

# day16a.o: day16a.cpp
# > $(CC) $(CFLAGS) -c day16a.cpp

# cpplite.o: cpplite.cpp
# > $(CC) $(CFLAGS) -c cpplite.cpp

# clean:
# > rm -f core *.o


# CC=gcc
# CXX=g++
# RM=rm -f
# CPPFLAGS=-g $(shell root-config --cflags)
# LDFLAGS=-g $(shell root-config --ldflags)
# LDLIBS=$(shell root-config --libs)

# SRCS=tool.cc support.cc
# OBJS=$(subst .cc,.o,$(SRCS))

# all: tool

# tool: $(OBJS)
# > $(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS)

# depend: .depend

# .depend: $(SRCS)
# > $(RM) ./.depend
# > $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

# clean:
# > $(RM) $(OBJS)

# distclean: clean
# > $(RM) *~ .depend

# include .depend