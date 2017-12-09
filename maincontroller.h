#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "audio.h"
#include "playlist.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController(){}
    ~MainController(){}
    void start();
    void openMainWin();
    MainWindow& getMainWin();

public slots:
    void NewTracksAdded(QVector<Audio> tracks);
    void FailedToAddTracks(QVector<Audio> failedTracks);

    void CreatePlaylist(QString nameForPlaylist, QVector<Audio>& tracksToPlaylist);

    void trackRemovingFailed(int position);

private:
    MainWindow mainWin;
    QVector<Audio> currentList;
    // пока что такая реализация
    // потом будет переписано под класс Playlists
    QVector<Playlist> currentPlaylists;
};

#endif // MAINCONTROLLER_H
