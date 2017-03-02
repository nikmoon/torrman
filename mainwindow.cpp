#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QTableWidgetItem>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), ses(new lt::session), timer(new QTimer(this))
{
    ui->setupUi(this);

    // инициализируем здесь, потому что нельзя этого делать раньше вызова предыдущей функции
    torrentView = new TorrentView(ui->tableWidget);

//    ses = new lt::session();
    ses->set_alert_mask(lt::alert::status_notification);
    ses->post_torrent_updates();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openTorrentFile()));

//    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(800);
}


MainWindow::~MainWindow()
{
    delete timer;
    delete ses;
    delete ui;
}


void MainWindow::updateView()
{
    static std::deque<lt::alert *> alerts;

    ses->pop_alerts(&alerts);
    ses->post_torrent_updates();
    torrentView->update(alerts);
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

