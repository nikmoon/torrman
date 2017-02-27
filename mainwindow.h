#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <map>
#include <deque>


#define BOOST_ASIO_SEPARATE_COMPILATION
#include <libtorrent/session.hpp>
#include <libtorrent/alert_types.hpp>

#include <QMainWindow>
#include <QTimer>


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

    QTimer *timer;
    lt::session *ses;
    std::map<std::string, int> torrentRow;
    std::deque<lt::alert *> alerts;
    int rowCount;

private slots:
    void updateView();
    void openTorrentFile();
};

#endif // MAINWINDOW_H
