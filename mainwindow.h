#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <ui_mainwindow.h>

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

private slots:
     void openPlaylist(QModelIndex);
     void setVolumeSlider();
     void setPlayPause();

signals:
    void play();
    void pause();
    void next();
    void prev();
    void settings();
    void audioSwitched(size_t audioPosition);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

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
