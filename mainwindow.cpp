#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qslider.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    volumeSliderStatus(false),
    playButtonStatus(true)
{
    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);
    setMinimumWidth(562);
    setMaximumWidth(562);
    setMinimumHeight(400);
    setMaximumHeight(400);
    playButton = new QPushButton(ui->groupBox);
    playButton->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "border-image: url(:images/play.png);"
                                "background: none;"
                                "border: none;"
                                "background-repeat: none;"
                                "height: 50px;"
                                "width: 50px;"
                               "}");
    playButton->move(50, 0);
    playButton->show();

    ui->listWidget->addItem("Add Audio From Disk");

    connect(playButton, SIGNAL(clicked()),
            this, SIGNAL(play()));

    connect(playButton, SIGNAL(clicked()),
            this, SLOT(setPlayPause()));

    connect(ui->nextButton, SIGNAL(clicked()),
            this, SIGNAL(next()));

    connect(ui->prevButton, SIGNAL(clicked()),
            this, SIGNAL(prev()));

    connect(ui->settingsButton, SIGNAL(clicked()),
            this, SIGNAL(settings()));

    connect(ui->volumeButton, SIGNAL(clicked()),
            this, SLOT(setVolumeSlider()));

    connect(ui->listWidget, SIGNAL(clicked(QModelIndex)),
            this, SLOT(openPlaylist(QModelIndex)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openPlaylist(QModelIndex index) {
    if(!index.row()){
        emit addAudioFromDisk(this);
    }
}

void MainWindow::setAudioListModel(QStringList tracks) {
    audioListModel->setStringList(tracks);
    ui->listView->setModel(audioListModel);
}


void MainWindow::setVolumeSlider() {
    if(!volumeSliderStatus){
        volumeSlider = new QSlider(Qt::Vertical, ui->centralWidget);
        volumeSlider->setRange(0,100);
        volumeSlider->show();
        volumeSliderStatus = true;
        volumeSlider->move(495,220);
    }
    else {
        delete volumeSlider;
        volumeSliderStatus = false;
    }
}

void MainWindow::setPlayPause() {
    if(playButtonStatus){
        delete playButton;
        pauseButton = new QPushButton(ui->groupBox);
        pauseButton->setStyleSheet("QPushButton {"
                                    "background-color: transparent;"
                                    "border-image: url(:images/pause.png);"
                                    "background: none;"
                                    "border: none;"
                                    "background-repeat: none;"
                                    "height: 50px;"
                                    "width: 50px;"
                                   "}");
        playButton->move(50, 0);
        pauseButton->show();
        playButtonStatus = false;

        connect(pauseButton, SIGNAL(clicked()),
                this, SIGNAL(pause()));

        connect(pauseButton, SIGNAL(clicked()),
                this, SLOT(setPlayPause()));

    }
    else {
        delete pauseButton;
        playButton = new QPushButton(ui->groupBox);
        playButton->setStyleSheet("QPushButton {"
                                    "background-color: transparent;"
                                    "border-image: url(:images/play.png);"
                                    "background: none;"
                                    "border: none;"
                                    "background-repeat: none;"
                                    "height: 50px;"
                                    "width: 50px;"
                                   "}");
        playButton->move(50, 0);
        playButton->show();
        playButtonStatus = true;

        connect(playButton, SIGNAL(clicked()),
                this, SIGNAL(play()));

        connect(playButton, SIGNAL(clicked()),
                this, SLOT(setPlayPause()));

    }
}
