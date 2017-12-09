#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include <QtGui>
#include <QErrorMessage>
#include <QInputDialog>
#include <QLineEdit>

#include "ui_mainwindow.h"
#include "qslider.h"
#include <QRadioButton>
#include <memory>

#include "audio.h"


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
    void showErrorMessage(QString textOfError);
    bool getLineOfText(QString& title, QString& message, QString& result);

signals:
    void play(bool);
    void pause(bool);
    void next();
    void prev();

    void settings();

    void audioSelected(int);
    void audioSwitched(int);

    void addAudioFromDisk(MainWindow*);

    void saveAsPlaylist(QString, QVector<Audio>&);

public slots:
    void sliderPositionChanged(qint64);
    void curAudioDurationChanged(qint64);
    void itemIndexChanged(int);

    void removeAudio();
    void saveAsPlaylist(const QStringListModel* audioListModel);
    void loopPlaylist(bool);


public slots:
    void sliderPositionChanged(qint64);
    void curAudioDurationChanged(qint64);
    void itemIndexChanged(int);

    void audioRemoveFromList(int);

private slots:
    void addButtonPushed();
    void removeButtonPushed();

    void setVolumeSlider();

    void itemClicked(QListWidgetItem*);
    void itemDoubleClicked(QListWidgetItem*);
    void setPrevRow();
    void setNextRow();
    
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
