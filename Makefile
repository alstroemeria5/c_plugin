CC=gcc
PIC=-fPIC
SHARED=-shared 
FLAGS=-Wcpp -g
MACROS=-DDEBUG -DLIB_CONCISE -Drb
INCLUDE_PATH=-L.
LIBRARY_PATH=-I ./include
LIBS=-lpthread -ldl
CFLAGS=$(MACROS) $(FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH)
SRCS=$(wildcard *.c)
SRCS:=$(filter-out main.c,$(SRCS)) #single expression expansion
OBJS=$(SRCS:.c=.o)	#recursive expression expansion
TARGET=plugin
.PHONY:all clean unitest 
#$(info SRCS is $(SRCS))
%.o : %.c
	$(CC) $(CFLAGS) $(PIC) -c $< $(LIBS)
all : $(OBJS)
	gcc $(CLAGS) -o libtout.so $(SHARED) $(OBJS) $(LIBS)
	gcc $(CFLAGS) -o $(TARGET)  main.c -ltout

clean:
	rm -r *.o *.so $(TARGET)
rebuild: clean
	$(MAKE)
unitest: 
	cd $@ && $(MAKE)
