#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtGui>
#include "audio.h"
#include <algorithm>


class Playlist
{
public:
    Playlist(QString nameForPlaylist);
    Playlist(QString nameForPlaylist, QVector<Audio>& tracksToPlaylist);
    void setNamePlaylist(QString nameForPlaylist);
    void addTrack();
    void Save();
    void Load();

private:
    QString path;
    QString name;
    QVector<Audio> tracks;
};

#endif // PLAYLIST_H
