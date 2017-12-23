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

private:
    int currentPosition = 0;
    MainWindow mainWin;
    QVector<Audio> currentList;
};

#endif // MAINCONTROLLER_H
