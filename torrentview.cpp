#include "torrentview.hpp"

#include <QStringList>



TorrentView::TorrentView(QTableWidget *tw) : tableWidget(tw)
{
    setWidget(tw);
}


void TorrentView::setWidget(QTableWidget *tw)
{
    if (tw)
    {
        tableWidget = tw;

        /*
         *  Во-первых - наглядность.
         *  Во-вторых - независимость от порядка расположения полей TorrentRow::column_t
         */
        QString header[TorrentRow::column_count];
        header[TorrentRow::name] = "Название";
        header[TorrentRow::state] = "Состояние";
        header[TorrentRow::dl_rate] = "Загрузка";
        header[TorrentRow::up_rate] = "Отдача";
        header[TorrentRow::progress] = "Прогресс";
        QStringList headerList;
        for(QString &s: header)
            headerList << s;
        tableWidget->setColumnCount(TorrentRow::column_count);
        tableWidget->setHorizontalHeaderLabels(headerList);
    }
}


void TorrentView::update(const std::deque<lt::alert *> &alerts)
{
    for(lt::alert * alert: alerts)
    {
        switch (alert->type())
        {
            case lt::torrent_added_alert::alert_type:
                addTorrent(static_cast<lt::torrent_added_alert*>(alert)->handle);
                break;
            case lt::state_update_alert::alert_type:
                for (auto st: static_cast<lt::state_update_alert*>(alert)->status)
                {
                    updateTorrent(st);
                }
                break;
            case lt::state_changed_alert::alert_type:
                updateTorrent(static_cast<lt::state_changed_alert*>(alert)->handle,
                              static_cast<lt::state_changed_alert*>(alert)->state);
                break;
            default:
                break;
        }
    }
}


void TorrentView::addTorrent(libtorrent::torrent_handle handle)
{
    TorrentRow row(&handle, tableWidget);
    int insertIndex = tableWidget->rowCount();

    tableWidget->insertRow(insertIndex);

    for (int i = 0; i < TorrentRow::column_count; i++)
    {
        auto item = new QTableWidgetItem();
        tableWidget->setItem(insertIndex, i, item);
        row.items[i] = item;
    }

    row.items[TorrentRow::name]->setText(QString::fromStdString(handle.name()));
    torrentRows[handle.name()] = row;
}


void TorrentView::updateTorrent(const lt::torrent_status &st)
{
    auto &items = torrentRows[st.handle.name()].items;
    auto dlItem = items[TorrentRow::dl_rate];
    auto upItem = items[TorrentRow::up_rate];
    auto progressItem = items[TorrentRow::progress];

    dlItem->setText(st.download_payload_rate ? rate2string(st.download_payload_rate) : "");
    upItem->setText(st.upload_payload_rate ? rate2string(st.upload_payload_rate) : "");
    progressItem->setText(QString::number(st.progress * 100, 'f', 2) + " %");
}


void TorrentView::updateTorrent(lt::torrent_handle handle, lt::torrent_status::state_t state)
{
    auto item = torrentRows[handle.name()].items[TorrentRow::state];
    switch (state)
    {
        case lt::torrent_status::downloading:
            item->setText(QString("downloading"));
            break;
        case lt::torrent_status::seeding:
            item->setText(QString("seeding"));
            break;
        case lt::torrent_status::checking_files:
            item->setText(QString("checking"));
            break;
        default:
            item->setText(QString::number(state));
            break;
    }
}

QString TorrentView::rate2string(int rate)
{
    double drate = rate;
    const double rateKiB = 1024.0;
    const double rateMiB = 1024.0 * 1024.0;
    const char *s;

    if (drate >= rateMiB)
    {
        drate = drate / rateMiB;
        s = " MiB/s";
    }
    else
    {
        drate = drate / rateKiB;
        s = " KiB/s";
    }
    return QString::number(drate, 'f', 2) + s;
}
