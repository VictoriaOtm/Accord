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
    MainController();
    ~MainController(){}
    void start();
    void openMainWin();
    MainWindow& getMainWin();

public slots:
    void NewTracksAdded(QVector<Audio> tracks);
    void trackRemovingFailed(int position);
    void playpause(bool);
    void FailedToAddTracks(QVector<Audio> failedTracks);
    void CreatePlaylist();

signals:
    void play();
    void pause();
    void saveAsPlaylist(QString, QVector<Audio>&);

private:
    MainWindow mainWin;
    QVector<Audio> currentList;
};

#endif // MAINCONTROLLER_H
