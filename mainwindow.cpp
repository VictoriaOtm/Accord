#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <iostream>


void MainWindow::ShowContextMenu(const QPoint& pos)
{
   QMenu contextMenu(tr("Доступные действия"), this);

   QAction action1("Сохранить как плейлист", this);
   //QObject::connect(&action1, SIGNAL(triggered()), this, SLOT(saveAsPlaylist()));
   QObject::connect(&action1, SIGNAL(triggered()), this, SIGNAL(saveAsPlaylist()));
   contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}

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
    playPauseButton->setObjectName("playPauseButton");
    playPauseButton->setStyleSheet(styleSheet);
    playPauseButton->setFocusPolicy(Qt::NoFocus);

    file.close();

    // добавим контекстное меню
    ui->curAudioListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->curAudioListWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint&)));
    //

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

    QObject::connect(ui->playListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClickedLeftColumn(QListWidgetItem*)));

    QObject::connect(ui->curAudioListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClicked(QListWidgetItem*)));

    QObject::connect(ui->curAudioListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     this, SLOT(itemDoubleClicked(QListWidgetItem*)));

    QObject::connect(ui->volumeButton, SIGNAL(clicked()),
            this, SLOT(setVolumeSlider()));

    QObject::connect(ui->plusButton, SIGNAL(clicked()),
                     this, SLOT(addButtonPushed()));

    QObject::connect(ui->loopPlaylistButton, SIGNAL(clicked(bool)), this, SIGNAL(loopPlaylist(bool)));

    QObject::connect(ui->minusButton, SIGNAL(clicked()),
                     this, SLOT(removeButtonPushed()));


    // loadRightColumn();

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

void MainWindow::setAudioListModelForPlaylist(QStringList tracks) {
    qDebug() << tracks;
    // сначала удалим все отоброжаемые треки
    // в правой части
    int previousCount = ui->curAudioListWidget->count();
    for(int i = 0; i <  previousCount; i++) {
        ui->curAudioListWidget->model()->removeRow(0);
    }

    audioListModel->setStringList(tracks);
    ui->curAudioListWidget->addItems(tracks);
}

void MainWindow::setPlaylistsModel(QStringList playlists) {
    if( !playlists.isEmpty() ) {
        if(ui->playListWidget->count() == 0 ) {
            playlistModel->setStringList(playlists);
            ui->playListWidget->addItems(playlists);
        } else {
            int previousCount = ui->playListWidget->count();
            for(int i = 0; i <  previousCount; i++) {
                ui->playListWidget->model()->removeRow(0);
            }

            playlistModel->setStringList(playlists);
            ui->playListWidget->addItems(playlists);
        }
    }
}


void MainWindow::removeButtonPushed(){
    if (ui->curAudioListWidget->count() > 0){
        emit removeAudio();
    }
}

void MainWindow::addButtonPushed() {
    emit addAudioFromDisk(this);
}

void MainWindow::errorMessage(QString textOfError) {
    showErrorMessage(textOfError);
}

void MainWindow::audioRemoveFromList(int position) {
    ui->curAudioListWidget->model()->removeRow(position);
}

void MainWindow::itemClicked(QListWidgetItem *item){
    int position = item->listWidget()->currentRow();
    emit audioSelected(position);
}

void MainWindow::itemClickedLeftColumn(QListWidgetItem *item){
    int position = item->listWidget()->currentRow();
    qDebug() << "Cath click on left column";
    qDebug() << "Send signal 'playlistSelected', " << position;
    emit playlistSelected(position);
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
        volumeSlider->setRange(0,100);
        volumeSlider->setFocusPolicy(Qt::NoFocus);
        volumeSlider->show();
        volumeSliderStatus = true;
    }
    else {
        delete volumeSlider;
        volumeSliderStatus = false;

    }
}

void MainWindow::showErrorMessage(QString textOfError){
    QMessageBox::warning(this, "Ошибка", textOfError, QMessageBox::Ok);
    /*QErrorMessage errorMessage;
    errorMessage.showMessage(textOfError);
    errorMessage.exec();*/
}

bool MainWindow::getLineOfText(const QString title, const QString message, QString& result){
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
