#include "mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    volumeSliderStatus(false)
{
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);

    
    playPauseButton = new QRadioButton(ui->playPauseBox);
    playPauseButton->setObjectName("playPauseButton");
    playPauseButton->setStyleSheet(styleSheet);

    file.close();

    QObject::connect(playPauseButton, SIGNAL(toggled(bool)),
                     this, SIGNAL(play(bool)));

    QObject::connect(playPauseButton, SIGNAL(toggled(bool)),
                     this, SIGNAL(pause(bool)));

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

void MainWindow::setPlaylistsModel(QStringList playlists) {
    // TODO
    // необходимо добавлять playlists в playlistModel
    // а не заменять их, как сейчас
    // т.к. playlists содержат только новые плейлисты, которые
    // только были добавлены
    if(ui->playListWidget->count() == 0 ) {
        playlistModel->setStringList(playlists);
        ui->playListWidget->addItems(playlists);
    }

    // пробный код добавления плейлистов
    /*QListWidgetItem *newItem = new QListWidgetItem;
    //newItem->setText("Текущий плейлист");
    ui->playListWidget->insertItem(0, newItem);*/
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
