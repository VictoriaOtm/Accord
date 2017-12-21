#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtGui>
#include "audio.h"
#include "playlist.pb.h"
#include <fstream>
#include <string>


class Playlist
{    
public:
    Playlist(QString nameForPlaylist);
    Playlist(QString nameForPlaylist, QVector<Audio>& tracksToPlaylist);
    QString getName();
    void setNamePlaylist(QString nameForPlaylist);
    void addTrack();
    bool Save( protobuf::Playlists& playlistsForSaving );
    //void Load();

private:
    //QString path;
    QString name;
    QVector<Audio> tracks;
};

#endif // PLAYLIST_H
