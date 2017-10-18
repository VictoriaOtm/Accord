#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>

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
    QString path = ui->lineEdit->text();
    WorkingDir::WorkingDirectory dir(path);
    if(!dir.IsValidDir()){
        QMessageBox::critical(this, "Error", "Invalid directory");
    }else{
        currentPath = path;
        dir.CreateListOfSongs(WorkingDir::ALPHABET);
        int size = dir.Size();
        QStringList list;

        for(int i = 1 ; i <= size ; ++i){
           std::cout <<  dir.GetSong(i).toStdString() << std::endl;
           list << dir.GetSong(i);
        }

        model->setStringList(list);

        ui->listView->setModel(model);


    }
}

void MainWindow::on_playButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    std::string absPath = currentPath.toStdString() + "/" + model->stringList().at(index.row()).toStdString();
    player->setMedia(QUrl::fromLocalFile(QString(absPath.data())));
    player->play();
}
