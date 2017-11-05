#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <vector>
#include "audio.h"

class Player: public QObject
{
    Q_OBJECT

public:
    static Player& Instance();
    Player(const Player& other) = delete;
    Player& operator = (const Player& other) = delete;

private:
    QMediaPlayer player;
    Player();
    ~Player() = default;

public slots:
    void Play();
    void Pause();
    void Stop();
    void Prev();
    void Next();
    void SetVolume(int volume);
    void SetPosition(qint64 position);
    void AddTracks(const QVector<Audio>& newTracks);
    void RemoveTracks(int start, int end);
    void AddTrack(const Audio& newTrack);
    void RemoveTrack(int trackNum);

signals:
    //PASSED FURTHER FROM QMEDIAPLAYER
    void AudioAvailableChanged(bool available);
    void PositionChanged(qint64 position);
    void MediaChanged(const QMediaContent& media);
    void CurrentIndexChanged(int position);
    void MediaStatusChanged(QMediaPlayer::MediaStatus);
    //EMITTED BY PLAYER ITSELF
    void AddedTracksSuccessfully();
    void AddTracksFailed();
    void RemovedTracksSuccessfully();
    void RemoveTracksFailed();
};

#endif // PLAYER_H
