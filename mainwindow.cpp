#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    //qDebug() << QString::fromLocal8Bit("1");
    emit addAudioFromDisk(this);
}

void MainWindow::setAudioListModel(QStringList tracks) {
    audioListModel->setStringList(tracks);
    ui->listView->setModel(audioListModel);
}
