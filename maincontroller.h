#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "audio.h"
#include "playlists.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController();
    ~MainController(){}
    void start();
    void openMainWin();
    MainWindow& getMainWin();
    void showPlaylists();
    void showAudioForCurrentPlaylist(int position);

public slots:
    void NewTracksAdded(QVector<Audio>);
    void trackRemovingFailed(int);
    void playpause(bool);
    void FailedToAddTracks(QVector<Audio>);
    void CreatePlaylist();
    void playlistSelected(int);
    void printPlaylists();

signals:
    void play();
    void pause();
    void saveAsPlaylist(QString, QVector<Audio>&);
    void TracksAdded(QVector<Audio>);
    void LoadTracks(QVector<Audio>);

private:
    MainWindow mainWin;
    int currentPosition = 0;
    //QVector<Audio> currentList;
};

#endif // MAINCONTROLLER_H
