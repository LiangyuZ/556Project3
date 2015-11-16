CC = g++ -std=gnu++11
COPTS = -Wall -Wno-deprecated
LKOPTS = 

OBJS =\
HEADRES =\

all:	ex1 ex2 ex3 ex4 threads

ex1: mapExample.cc
	$(CC) $(DEFS) $(CFLAGS) $(LIB) -o ex1 mapExample.cc

ex2: mapExample2.cc
	$(CC) $(DEFS) $(CFLAGS) $(LIB) -o ex2 mapExample2.cc

ex3: mapExample3.cc
	$(CC) $(DEFS) $(CFLAGS) $(LIB) -o ex3 mapExample3.cc

ex4: mapExample4.cc
	$(CC) $(DEFS) $(CFLAGS) $(LIB) -o ex4 mapExample4.cc

threads: threads.cc
	$(CC) $(DEFS) $(CFLAGS) $(LIB) -o threads threads.cc


clean:
	rm -f *.o
	rm -f *~
	rm -f core.*.*
