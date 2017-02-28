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


    void addTorrent(lt::torrent_handle h);
    void updateTorrentsStatus(lt::state_update_alert *a);
    void updateTorrentState(lt::state_changed_alert *a);

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    lt::session *ses;
    std::map<std::string, int> torrentsRowMap;
    std::deque<lt::alert *> alerts;
    int rowCount;

private slots:
    void updateWidget();
    void openTorrentFile();
};

#endif // MAINWINDOW_H
