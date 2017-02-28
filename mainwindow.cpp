#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    rowCount = 0;

    ses = new lt::session();
    ses->set_alert_mask(lt::alert::status_notification);
    ses->post_torrent_updates();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openTorrentFile()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWidget()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete ses;
    delete timer;
    delete ui;
}

void MainWindow::updateWidget()
{
    ses->pop_alerts(&alerts);

    for(lt::alert *alert: alerts)
    {
        ses->post_torrent_updates();
        switch (alert->type()) {
        case lt::torrent_added_alert::alert_type:
            addTorrent(static_cast<lt::torrent_added_alert*>(alert)->handle);
            break;
        case lt::state_update_alert::alert_type:
            updateTorrentsStatus(static_cast<lt::state_update_alert*>(alert));
            break;
        case lt::state_changed_alert::alert_type:
            updateTorrentState(static_cast<lt::state_changed_alert*>(alert));
            break;
        default:
            break;
        }
    }
}


void MainWindow::openTorrentFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        lt::add_torrent_params atp;
        atp.ti = new lt::torrent_info(fileName.toStdString());
        atp.save_path = ".";
        ses->async_add_torrent(atp);
    }
}


void MainWindow::addTorrent(lt::torrent_handle h)
{
    ui->tableWidget->insertRow(rowCount);
    torrentsRowMap[h.name()] = rowCount;
    QString s = QString::fromStdString(h.name());
    QTableWidgetItem *item = new QTableWidgetItem(s);
    ui->tableWidget->setItem(rowCount, 0, item);
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem());
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem());
    ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem());
    rowCount++;
}


void MainWindow::updateTorrentsStatus(lt::state_update_alert *alert)
{
    const double mb = 1024.0 * 1024.0;
    double rate;
    double progress;
    QString s;
    int rowNum;
    QTableWidgetItem *itemState, *itemDlRate, *itemUpRate, *itemProgress;;
    for(lt::torrent_status st: alert->status)
    {
        rowNum = torrentsRowMap[st.handle.name()];
        itemState = ui->tableWidget->item(rowNum, 1);
        itemDlRate = ui->tableWidget->item(rowNum, 2);
        itemUpRate = ui->tableWidget->item(rowNum, 3);
        itemProgress = ui->tableWidget->item(rowNum, 4);
        if (st.download_payload_rate >= mb)
        {
            rate = st.download_payload_rate / mb;
            s = QString::number(rate, 'f', 2) + QString(" MiB/s");
        }
        else
        {
            rate = st.download_payload_rate / 1024.0;
            s = QString::number(rate, 'f', 2) + QString(" KiB/s");
        }
        itemDlRate->setText(s);

        if (st.upload_payload_rate >= mb)
        {
            rate = st.upload_payload_rate / mb;
            s = QString::number(rate, 'f', 2) + QString(" MiB/s");
        }
        else
        {
            rate = st.upload_payload_rate / 1024.0;
            s = QString::number(rate, 'f', 2) + QString(" KiB/s");
        }
        itemUpRate->setText(s);
        itemProgress->setText(QString::number(st.progress, 'f', 2));
    }
}


void MainWindow::updateTorrentState(lt::state_changed_alert *alert)
{
    int rowNum = torrentsRowMap[alert->handle.name()];
    QTableWidgetItem *item = ui->tableWidget->item(rowNum, 1);

    switch (alert->state) {
    case lt::torrent_status::downloading:
        item->setText(QString("downloading"));
        break;
    case lt::torrent_status::seeding:
        item->setText(QString("seeding"));
        break;
    case lt::torrent_status::checking_files:
        item->setText(QString("cheking"));
        break;
    default:
        item->setText(QString("unknown"));
        break;
    }
}
