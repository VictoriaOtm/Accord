#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <memory>
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
    ~MainWindow();
    void setAudioListModel(QStringList tracks);
    void setPlaylistsModel(QStringList playlists);


signals:
    void play();
    void pause();
    void next();
    void prev();
    void settings();
    void audioSwitched(int);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

private slots:
    void addButtonPushed();
    void setVolumeSlider();
    void setPlayPause();

private:
    std::shared_ptr<Ui::MainWindow> ui;
    std::shared_ptr<QStringListModel> audioListModel;
    std::shared_ptr<QStringListModel> playlistModel;

    std::shared_ptr<QSlider> volumeSlider;
    bool volumeSliderStatus;
    std::shared_ptr<QPushButton> playButton;
    std::shared_ptr<QPushButton> pauseButton;
    bool playButtonStatus;
};

#endif // MAINWINDOW_H
