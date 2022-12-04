.RECIPEPREFIX = >
CC=g++

# good for any file
# src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lm

myprog: $(obj)
> $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
> rm -f $(obj) t