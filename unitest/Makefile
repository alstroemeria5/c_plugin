.PHONY: all cleana
CC=gcc
CFLAGS=-I ../include -L..
LIBS=-ltout 
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LIBS)	
	chmod +x $@
#					$< first prerequisite::unitest*.c
#					$@ name of the target::unitest*.o
#					$^ all prerequisite
all : $(OBJS)
	
clean:
	rm -r *.o
