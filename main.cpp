#include "mainwindow.h"

#include <QApplication>


namespace lt = libtorrent;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
