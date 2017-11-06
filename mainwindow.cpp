#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);

    QObject::connect(ui->play_button, SIGNAL(clicked()),
                     this, SIGNAL(play()));

    QObject::connect(ui->next_button, SIGNAL(clicked()),
                     this, SIGNAL(next()));

    QObject::connect(ui->prev_button, SIGNAL(clicked()),
                     this, SIGNAL(prev()));

    QObject::connect(ui->cur_audiolist_view, SIGNAL(currentRowChanged(int)),
                     this, SIGNAL(audioSwitched(int)));

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
    ui->cur_audiolist_view->addItems(tracks);
    //ui->cur_audiolist_view->setModel(audioListModel);
}
