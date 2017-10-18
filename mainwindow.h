#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QStringListModel>
#include <stdio.h>
#include "working_directory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chooseDirButton_clicked();

    void on_playButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QStringListModel *model;
    QString currentPath;
};

#endif // MAINWINDOW_H
