#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "ui_mainwindow.h"
#include "qslider.h"
#include <QRadioButton>
#include <memory>



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
    void play(bool);
    void pause(bool);
    void next();
    void prev();
    void settings();
    void audioSwitched(int);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

private slots:
    void addButtonPushed();
    void setVolumeSlider();

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;
    
    QRadioButton *playPauseButton;
    QSlider *volumeSlider;
    bool volumeSliderStatus;
};

#endif // MAINWINDOW_H
