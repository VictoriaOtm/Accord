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
    Playlist();
    Playlist(const protobuf::Playlist proto_playlist);
    Playlist(QString nameForPlaylist);
    Playlist(QString nameForPlaylist, QVector<Audio> tracksToPlaylist);

    QString getName();
    int size();
    QString get(int index);

    void setNamePlaylist(QString nameForPlaylist);
    void addTrack();
    bool Save( protobuf::Playlists& playlistsForSaving );

private:
    QString name;
    QVector<Audio> tracks;
};

#endif // PLAYLIST_H
