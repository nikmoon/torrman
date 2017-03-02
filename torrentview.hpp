#ifndef TORRENTVIEW_HPP
#define TORRENTVIEW_HPP


#include <map>
#include <string>
#include <deque>

#include <QTableWidget>
#include <QTableWidgetItem>

#define BOOST_ASIO_SEPARATE_COMPILATION
#include <libtorrent/session.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/torrent_handle.hpp>

namespace lt = libtorrent;


class MainWindow;


struct TorrentRow
{
    enum column_t
    {
        name = 0,
        state,
        dl_rate,
        up_rate,
        progress,
        column_count
    };

    QTableWidget *tableWidget;
    lt::torrent_handle handle;
    QTableWidgetItem *items[column_count];

    TorrentRow(lt::torrent_handle *h = nullptr, QTableWidget *w = nullptr)
    {
        if (h)
            handle = *h;
        tableWidget = w;
    }
};


class TorrentView : public QObject
{
    Q_OBJECT

    friend class MainWindow;

    QTableWidget *tableWidget;
    std::map<std::string, TorrentRow> torrentRows;


public:
    TorrentView(QTableWidget *tw = nullptr);
    void setWidget(QTableWidget *tw);

private slots:
    void update(const std::deque<lt::alert *> &alerts);
    void addTorrent(lt::torrent_handle handle);
    void updateTorrent(const lt::torrent_status &);
    void updateTorrent(lt::torrent_handle, lt::torrent_status::state_t);

public:
    QString rate2string(int rate);
};

#endif // TORRENTVIEW_HPP
