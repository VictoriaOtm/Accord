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
    void audioSelected(int);
    void audioSwitched(int);
    void addAudioFromDisk(MainWindow*);
    void saveAsPlaylist(const QStringListModel* audioListModel);

public slots:
    void sliderPositionChanged(qint64);
    void curAudioDurationChanged(qint64);
    void itemIndexChanged(int);

private slots:
    void addButtonPushed();
    void setVolumeSlider();
    void itemClicked(QListWidgetItem*);
    void itemDoubleClicked(QListWidgetItem*);
    void setPrevRow();
    void setNextRow();

private:
    Ui::MainWindow *ui;
    QStringListModel *audioListModel;
    QStringListModel *playlistModel;
    
    QRadioButton *playPauseButton;
    QSlider *volumeSlider;
    bool volumeSliderStatus;
    qint64 curAudioDuration;
};

#endif // MAINWINDOW_H
