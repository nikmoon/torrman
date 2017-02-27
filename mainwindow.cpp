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
    //ui->tableWidget->setRowCount(10);
    ses = new lt::session();
    ses->set_alert_mask(lt::alert::all_categories);
    rowCount = 0;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openTorrentFile()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete ses;
    delete timer;
    delete ui;
}

void MainWindow::updateView()
{
    //int rowCount = ui->tableWidget->rowCount();

    ses->pop_alerts(&alerts);

    for(const lt::alert *alert: alerts)
    {
        //rowCount++;
        ui->tableWidget->insertRow(rowCount);
        QString s = QString::fromStdString(alert->message());
        QTableWidgetItem *item = new QTableWidgetItem(s);
        ui->tableWidget->setItem(rowCount, 0, item);
        rowCount++;
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
