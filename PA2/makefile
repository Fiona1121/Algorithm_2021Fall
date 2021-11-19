# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps: main.o mps.o
	$(CC) $(OPTFLAGS) $^ -o $@
main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
mps.o: src/max_planar_subset.cpp src/max_planar_subset.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o ./mps outputs/*

