#include "mainwindow.h"

#include <iostream>
#include <libtorrent/torrent_handle.hpp>

#include <QApplication>

void start_client();

namespace lt = libtorrent;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    cout << lt::torrent_status::checking_files << endl;

    return a.exec();
}
