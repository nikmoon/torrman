#
# Makefile
# nikbird, 2017-02-19 11:48
#

.PHONY: all clean

all: torrman

torrman: torrman.o main.o mainwindow.o torrentview.o
	g++ -o torrman torrman.o main.o mainwindow.o mainwindow.h.o torrentview.o torrentview.h.o \
		-pthread -ltorrent-rasterbar -lboost_system `pkg-config --libs Qt5Widgets`
	strip torrman

torrman.o: torrman.cpp torrman.hpp
	g++ -std=c++11 -c -o torrman.o torrman.cpp `pkg-config --cflags Qt5Widgets`  -fPIC

main.o: main.cpp mainwindow.h ui_mainwindow.h
	g++ -std=c++11 -c -o main.o main.cpp `pkg-config --cflags Qt5Widgets` -fPIC

mainwindow.o: mainwindow.cpp mainwindow.h ui_mainwindow.h
	moc -omainwindow.h.cpp mainwindow.h
	g++ -std=c++11 -c -o mainwindow.o mainwindow.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	g++ -std=c++11 -c -o mainwindow.h.o mainwindow.h.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	rm mainwindow.h.cpp

torrentview.o: torrentview.cpp torrentview.hpp
	moc -otorrentview.h.cpp torrentview.hpp
	g++ -std=c++11 -c -o torrentview.o torrentview.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	g++ -std=c++11 -c -o torrentview.h.o torrentview.h.cpp `pkg-config --cflags Qt5Widgets` -fPIC
	rm torrentview.h.cpp

ui_mainwindow.h: mainwindow.ui
	uic mainwindow.ui -o ui_mainwindow.h

clean:
	rm -rf torrman *.o *.moc.cpp ui_mainwindow.h

# vim:ft=make
#
