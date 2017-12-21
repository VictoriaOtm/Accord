#ifndef PLAYLISTS_H
#define PLAYLISTS_H

#include "playlist.h"

class Playlists : public QObject
{
      Q_OBJECT

public:
    static Playlists& instance();
    void Load();
    void Save();

signals:
    void Error(QString);

private:
    Playlists();
    QVector<Playlist> currentPlaylists;
};

#endif // PLAYLISTS_H
