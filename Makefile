#
# Makefile
# nikbird, 2017-02-19 11:48
#

.PHONY: all clean

all: torrman
#all: mainwindow.o

torrman: torrman.o main.o mainwindow.o mainwindow.h.o
	g++ -o torrman torrman.o main.o mainwindow.o mainwindow.h.o \
		-pthread -ltorrent-rasterbar -lboost_system `pkg-config --libs Qt5Widgets`
	strip torrman

torrman.o: torrman.cpp torrman.hpp
	g++ -std=c++11 -c -o torrman.o torrman.cpp `pkg-config --cflags Qt5Widgets`  -fPIC

main.o: main.cpp mainwindow.h ui_mainwindow.h
	g++ -std=c++11 -c -o main.o main.cpp `pkg-config --cflags Qt5Widgets` -fPIC

mainwindow.o: mainwindow.cpp mainwindow.h ui_mainwindow.h
	moc -omainwindow.h.moc.cpp mainwindow.h
	g++ -std=c++11 -c -o mainwindow.h.o mainwindow.h.moc.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	g++ -std=c++11 -c -o mainwindow.o mainwindow.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	rm mainwindow.h.moc.cpp

ui_mainwindow.h: mainwindow.ui
	uic mainwindow.ui -o ui_mainwindow.h

clean:
	rm -rf torrman *.o

# vim:ft=make
#
