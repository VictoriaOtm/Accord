#include "mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    volumeSliderStatus(false),
    playButtonStatus(true)
{
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);

    playButton = new QPushButton(ui->playPauseBox);
    playButton->setObjectName("playButton");
    playButton->setStyleSheet(styleSheet);
    playButton->show();

    file.close();

    QObject::connect(playButton, SIGNAL(clicked()),
                     this, SIGNAL(play()));

    QObject::connect(playButton, SIGNAL(clicked()),
            this, SLOT(setPlayPause()));

    QObject::connect(ui->nextButton, SIGNAL(clicked()),
                     this, SIGNAL(next()));

    QObject::connect(ui->prevButton, SIGNAL(clicked()),
                     this, SIGNAL(prev()));

    QObject::connect(ui->settingsButton, SIGNAL(clicked()),
                     this, SIGNAL(settings()));

    QObject::connect(ui->curAudioListWidget, SIGNAL(currentRowChanged(int)),
                     this, SIGNAL(audioSwitched(int)));

    QObject::connect(ui->volumeButton, SIGNAL(clicked()),
            this, SLOT(setVolumeSlider()));

    QObject::connect(ui->plusButton, SIGNAL(clicked()),
                     this, SLOT(addButtonPushed()));

}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::setAudioListModel(QStringList tracks) {
    // TODO
    // необходимо добавлять tracks в audioListModel
    // а не заменять их, как сейчас
    // т.к. tracks содержат только новые песни, которые
    // только были добавлены
    audioListModel->setStringList(tracks);
    ui->curAudioListWidget->addItems(tracks);
}

void MainWindow::addButtonPushed() {
    emit addAudioFromDisk(this);
}

void MainWindow::setVolumeSlider() {
        if(!volumeSliderStatus){
        volumeSlider = new QSlider(Qt::Horizontal, ui->volumeBox);
        volumeSlider->setRange(0,100);
        volumeSlider->show();
        volumeSliderStatus = true;
    }
    else {
        delete volumeSlider;
        volumeSliderStatus = false;
    }
}

void MainWindow::setPlayPause() {
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    if(playButtonStatus){
        delete playButton;
        pauseButton = new QPushButton(ui->playPauseBox);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setStyleSheet(styleSheet);
        pauseButton->show();
        playButtonStatus = false;

        QObject::connect(pauseButton, SIGNAL(clicked()),
                this, SIGNAL(pause()));

        QObject::connect(pauseButton, SIGNAL(clicked()),
                this, SLOT(setPlayPause()));

    }
    else {
        delete pauseButton;
        playButton = new QPushButton(ui->playPauseBox);
        playButton->setObjectName("playButton");
        playButton->setStyleSheet(styleSheet);
        playButton->show();
        playButtonStatus = true;

        QObject::connect(playButton, SIGNAL(clicked()),
                this, SIGNAL(play()));

        QObject::connect(playButton, SIGNAL(clicked()),
                this, SLOT(setPlayPause()));
    }
    file.close();
}
