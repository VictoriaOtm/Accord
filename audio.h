#ifndef AUDIO_H
#define AUDIO_H

#include <QtCore>

class Audio
{
public:
    Audio() = default;
    Audio(QString path);
    static QVector<Audio> fromAudioPaths(const QStringList& paths);
    const QString& GetPath() const;
    const QString& GetFilename() const;
    const QString& GetTitle() const;
    const QStringList& GetAuthors() const;
    const QString& GetAlbumTitle() const;
    bool operator == (const Audio& other) const;
private:
    QString path;
    QString filename;
    QString title;
    QStringList authors;
    QString album;
    void LoadMetaData();
};

#endif // AUDIO_H
