#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <map>
#include <deque>


#define BOOST_ASIO_SEPARATE_COMPILATION
#include <libtorrent/session.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/torrent_handle.hpp>

#include <QMainWindow>
#include <QTimer>

#include "torrentview.hpp"

namespace lt = libtorrent;


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    TorrentView *torrentView;

    QTimer *timer;
    lt::session *ses;

private slots:
    void updateView();
    void openTorrentFile();
};

#endif // MAINWINDOW_H
