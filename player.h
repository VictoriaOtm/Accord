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
    static Player& instance();
    Player(const Player& other) = delete;
    Player& operator = (const Player& other) = delete;

private:
    Player();
    ~Player() = default;
    QMediaPlayer player;
    int selectedAudioPosition;

public slots:
    void play();
    void pause();
    void stop();
    void prev();
    void next();

    void setVolume(int volume);

    void setPlayingPosition(int position);
    void setSelectedAudioPosition(int position);

    void addTracks(const QVector<Audio>& newTracks);
    void removeTracks(int start, int end);
    void addTrack(const Audio& newTrack);
    void removeTrack(int trackNum);

signals:
    //PASSED FURTHER FROM QMEDIAPLAYER
    void audioAvailableChanged(bool available);
    void positionChanged(int position);
    void mediaChanged(const QMediaContent& media);
    void currentIndexChanged(int);
    void mediaStatusChanged(QMediaPlayer::MediaStatus);
    void audioDurationChanged(qint64);

    //EMITTED BY PLAYER ITSELF
    void addedTracksSuccessfully();
    void addTracksFailed();

    void removedTracksSuccessfully();
    void removeTracksFailed();
};

#endif // PLAYER_H
