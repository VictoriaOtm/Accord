#ifndef PLAYLISTS_H
#define PLAYLISTS_H

#include "playlist.h"
#include "fstream"
#include "string.h"


class Playlists : public QObject
{
      Q_OBJECT

public:
    static Playlists& instance();
    ~Playlists();
    void Load();
    void Save();
    int Size();
    int SizeOfPlaylist(int);
    QString GetNameAudioOfPlaylist(int, int);
    QString GetNameOfPlaylist(int);
    QVector<Audio> GetAudioFiles(int);
    Playlist& operator [](const int i);

signals:
    void Error(QString);
    void PrintPlaylists();

public slots:
    void CreatePlaylist(QString, QVector<Audio>&);

private:
    Playlists();
    QVector<Playlist> currentPlaylists;
};

#endif // PLAYLISTS_H
