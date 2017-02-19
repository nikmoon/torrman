#
# Makefile
# nikbird, 2017-02-19 11:48
#

.PHONY: all clean

all: torrman

torrman: torrman.o
	g++ -o torrman torrman.o -pthread -ltorrent-rasterbar -lboost_system
	strip torrman

torrman.o: torrman.cpp torrman.hpp
	g++ -std=c++11 -c -o torrman.o torrman.cpp

clean:
	rm -rf torrman *.o

# vim:ft=make
#
