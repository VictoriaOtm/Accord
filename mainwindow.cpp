#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    volumeSliderStatus(false),
    curAudioDuration(0)
{
    QFile file(":/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();

    audioListModel = new QStringListModel(this);
    playlistModel = new QStringListModel(this);
    ui->setupUi(this);
    
    playPauseButton = new QRadioButton(ui->playPauseBox);
    playPauseButton->setFocusPolicy(Qt::NoFocus);
    playPauseButton->setObjectName("playPauseButton");
    playPauseButton->setStyleSheet(styleSheet);

    file.close();

    QObject::connect(playPauseButton, SIGNAL(toggled(bool)),
                     this, SIGNAL(play(bool)));

    QObject::connect(ui->nextButton, SIGNAL(clicked()),
                     this, SIGNAL(next()));
    
    QObject::connect(ui->prevButton, SIGNAL(clicked()),
                     this, SIGNAL(prev()));
    
    QObject::connect(ui->nextButton, SIGNAL(clicked()),
                     this, SLOT(setNextRow()));
    

    QObject::connect(ui->prevButton, SIGNAL(clicked()),
                     this, SLOT(setPrevRow()));

    QObject::connect(ui->settingsButton, SIGNAL(clicked()),
                     this, SIGNAL(settings()));

    QObject::connect(ui->curAudioListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClicked(QListWidgetItem*)));

    QObject::connect(ui->curAudioListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     this, SLOT(itemDoubleClicked(QListWidgetItem*)));

    QObject::connect(ui->volumeButton, SIGNAL(clicked()),
            this, SLOT(setVolumeSlider()));

    QObject::connect(ui->plusButton, SIGNAL(clicked()),
                     this, SLOT(addButtonPushed()));

    QObject::connect(ui->loopPlaylistButton, SIGNAL(toggled(bool)), this, SIGNAL(loopPlaylist(bool)));
    
    QObject::connect(ui->minusButton, SIGNAL(clicked()),
                     this, SLOT(removeButtonPushed()));

}

MainWindow::~MainWindow() {
    delete audioListModel;
    delete playlistModel;

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

void MainWindow::removeButtonPushed(){
    if (ui->curAudioListWidget->count() > 0){
        emit removeAudio();
    }
}

void MainWindow::addButtonPushed() {
    emit addAudioFromDisk(this);
}


void MainWindow::itemClicked(QListWidgetItem *item){
    int position = item->listWidget()->currentRow();
    emit audioSelected(position);
}

void MainWindow::itemDoubleClicked(QListWidgetItem* item){
    int position = item->listWidget()->currentRow();
    emit audioSwitched(position);
}

void MainWindow::setPrevRow(){
    int curRow = ui->curAudioListWidget->currentRow();
    if (curRow > 0){
        --curRow;
    }
    ui->curAudioListWidget->setCurrentRow(curRow);
}

void MainWindow::setNextRow(){
    int curRow = ui->curAudioListWidget->currentRow();
    if (curRow < audioListModel->rowCount() - 1){
        ++curRow;
    }
    ui->curAudioListWidget->setCurrentRow(curRow);
}

void MainWindow::itemIndexChanged(int newRow){
    qDebug() << "Item index changed:";
    qDebug() << (qint64) newRow;
    //ui->curAudioListWidget->setCurrentRow(newRow, QItemSelectionModel::Current);
    ui->curAudioListWidget->setCurrentItem(ui->curAudioListWidget->item(newRow));
}

void MainWindow::curAudioDurationChanged(qint64 newDuration){
    curAudioDuration = newDuration;
    ui->timeSlider->setMaximum(newDuration);
}

void MainWindow::sliderPositionChanged(qint64 position){
    if (curAudioDuration != 0){
        ui->timeSlider->setSliderPosition(position);
        std::cout << "Slider position changed" << std::endl;
    }
}


void MainWindow::setVolumeSlider() {
    if(!volumeSliderStatus){
        volumeSlider = new QSlider(Qt::Horizontal, ui->volumeBox);
        volumeSlider->setFocusPolicy(Qt::NoFocus);
        volumeSlider->setRange(0,100);
        volumeSlider->show();
        volumeSliderStatus = true;
    }
    else {
        delete volumeSlider;
        volumeSliderStatus = false;

    }
}

void MainWindow::showErrorMessage(QString textOfError){
    QErrorMessage errorMessage;
    errorMessage.showMessage(textOfError);
    errorMessage.exec();
}

void MainWindow::audioRemoveFromList(int position) {
    ui->curAudioListWidget->model()->removeRow(position);
}

bool MainWindow::getLineOfText(QString& title, QString& message, QString& result){
    // будет отвечать за кнопнку
    // которую нажнем пользователь
    // true - если нажали 'ok'
    // false - если нажали 'cancel'
    bool ok;
    result = QInputDialog::getText(this,
                                     title,
                                     message,
                                     QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);

    return ok;
}
