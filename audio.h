#ifndef AUDIO_H
#define AUDIO_H


class Audio
{
public:
    Audio();
    const QString& GetPath() const;
private:
    QString path;
};

#endif // AUDIO_H
