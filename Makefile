#
# Makefile
# nikbird, 2017-02-19 11:48
#

.PHONY: all clean

all: torrman

torrman: torrman.o ctrlc_signal.o
	g++ -o torrman torrman.o ctrlc_signal.o -pthread -ltorrent-rasterbar -lboost_system
	strip torrman

torrman.o: torrman.cpp torrman.hpp
	g++ -std=c++11 -c -o torrman.o torrman.cpp

ctrlc_signal.o: ctrlc_signal.cpp ctrlc_signal.hpp
	g++ -std=c++11 -c -o ctrlc_signal.o ctrlc_signal.cpp

clean:
	rm -rf torrman *.o

# vim:ft=make
#
