#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <iostream>
#include "ui_mainwindow.h"
#include "qslider.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setAudioListModel(QStringList tracks);
    ~MainWindow();

public slots:
    void sliderPositionChanged(qint64);
    void curAudioDurationChanged(qint64);
    void itemIndexChanged(int);

signals:
    void play();
    void pause();
    void next();
    void prev();
    void settings();
    void audioSelected(int);
    void audioSwitched(int);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

private slots:
    void addButtonPushed();
    void setVolumeSlider();
    void setPlayPause();
    void itemClicked(QListWidgetItem*);
    void itemDoubleClicked(QListWidgetItem*);
    void setPrevRow();
    void setNextRow();

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;

    QSlider *volumeSlider;
    bool volumeSliderStatus;
    QPushButton *playButton;
    QPushButton *pauseButton;
    bool playButtonStatus;

    qint64 curAudioDuration;
};

#endif // MAINWINDOW_H
