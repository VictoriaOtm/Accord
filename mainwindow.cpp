#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new QMediaPlayer(this);
    model = new QStringListModel(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete player;
}


void MainWindow::on_chooseDirButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                QString::fromUtf8("Выберите аудиофайлы"),
                                //QUrl::fromLocalFile(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first()),
                                QDir::homePath(),
                                "Music (*.mp3 *.mp4 *.wav);;All files (*.*)");

    QStringList namesSongs;
    foreach(QString str, files){
       ssize_t startIndexNameSong = str.lastIndexOf(QString::fromLocal8Bit("/"));
       namesSongs.push_back(str.mid(startIndexNameSong + 1, str.count() - 1));
       currentPath = str.mid(0, startIndexNameSong + 1);

       // информация о преобразовании имени песни
       // и пути к ней
       /*qDebug() << str;
       qDebug() << startIndexNameSong;
       qDebug() << str.size() - 1;
       qDebug() << str.mid(startIndexNameSong + 1, str.size() - 1);
       qDebug() << currentPath;*/
    }

    model->setStringList(namesSongs);
    ui->listView->setModel(model);
}

void MainWindow::on_playButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    std::string absPath = currentPath.toStdString() + model->stringList().at(index.row()).toStdString();
    player->setMedia(QUrl::fromLocalFile(QString(absPath.data())));
    player->play();
}
