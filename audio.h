#ifndef AUDIO_H
#define AUDIO_H

#include <QtCore>

class Audio
{
public:
    Audio();
    const QString& GetPath() const;
private:
    QString path;
};

#endif // AUDIO_H
