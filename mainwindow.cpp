#include "mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    volumeSliderStatus(false),
    playButtonStatus(true)
{
    ui.reset(new Ui::MainWindow);
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    audioListModel.reset(new QStringListModel(this));
    playlistModel.reset(new QStringListModel(this));
    ui->setupUi(this);

    setMinimumWidth(562);
    setMaximumWidth(562);
    setMinimumHeight(400);
    setMaximumHeight(400);

    playButton.reset(new QPushButton(ui->playPauseBox));
    playButton->setObjectName("playButton");
    playButton->setStyleSheet(styleSheet);
    playButton->show();

    file.close();

    QObject::connect(playButton.get(), SIGNAL(clicked()),
                     this, SIGNAL(play()));

    QObject::connect(playButton.get(), SIGNAL(clicked()),
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
    ui.~__shared_ptr();
}

void MainWindow::setAudioListModel(QStringList tracks) {
    // TODO
    // необходимо добавлять tracks в audioListModel
    // а не заменять их, как сейчас
    // т.к. tracks содержат только новые песни, которые
    // только были добавлены
    //audioListModel.get()->
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
        volumeSlider.reset( new QSlider(Qt::Vertical, ui->centralWidget) );
        volumeSlider->setRange(0,100);
        volumeSlider->show();
        volumeSliderStatus = true;
        volumeSlider->move(495,220);
    }
    else {
        volumeSlider.~__shared_ptr();
        volumeSliderStatus = false;
    }
}

void MainWindow::setPlayPause() {
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    if(playButtonStatus){
        playButton.~__shared_ptr();
        pauseButton.reset( new QPushButton(ui->playPauseBox) );
        pauseButton->setObjectName("pauseButton");
        pauseButton->setStyleSheet(styleSheet);
        pauseButton->show();
        playButtonStatus = false;

        QObject::connect(pauseButton.get(), SIGNAL(clicked()),
                this, SIGNAL(pause()));

        QObject::connect(pauseButton.get(), SIGNAL(clicked()),
                this, SLOT(setPlayPause()));

    }
    else {
        pauseButton.~__shared_ptr();
        playButton.reset(new QPushButton(ui->playPauseBox));
        playButton->setObjectName("playButton");
        playButton->setStyleSheet(styleSheet);
        playButton->show();
        playButtonStatus = true;

        QObject::connect(playButton.get(), SIGNAL(clicked()),
                this, SIGNAL(play()));

        QObject::connect(playButton.get(), SIGNAL(clicked()),
                this, SLOT(setPlayPause()));
    }
    file.close();
}
