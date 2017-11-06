#ifndef AUDIO_H
#define AUDIO_H

#include <QtCore>

class Audio
{
public:
    Audio(QString path);
    static QVector<Audio> fromAudioPaths(const QStringList& paths);
    const QString& GetPath() const;
private:
    QString path;
    QString title;
    QStringList authors;
    QString album;
    void LoadMetaData();
};

#endif // AUDIO_H
