# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb: main.o cb.o
	$(CC) $(OPTFLAGS) $^ -o $@
main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
cb.o: src/cycle_removal.cpp src/cycle_removal.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o ./cb 

