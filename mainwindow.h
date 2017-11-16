#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
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


signals:
    void play();
    void pause();
    void next();
    void prev();
    void settings();
    void itemClicked(int);
    void audioSwitched(int);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

private slots:
    void addButtonPushed();
    void setVolumeSlider();
    void setPlayPause();
    void itemDoubleClicked(QListWidgetItem*);

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;

    QSlider *volumeSlider;
    bool volumeSliderStatus;
    QPushButton *playButton;
    QPushButton *pauseButton;
    bool playButtonStatus;
};

#endif // MAINWINDOW_H
