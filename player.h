#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <vector>
#include "audio.h"

const int PREV_THRESHOLD = 3000; //позиция в песне, до которой при нажатии prev переключаемся на предыдущую песню

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
    void play(bool);
    void pause(bool);
    void stop();
    void prev();
    void next();
    void setVolume(int volume);
    void setPosition(qint64 position);
    void addTracks(const QVector<Audio>& newTracks);
    void removeTracks(int start, int end);
    void addTrack(const Audio& newTrack);
    void removeTrack(int trackNum);

signals:
    //PASSED FURTHER FROM QMEDIAPLAYER
    void audioAvailableChanged(bool available);
    void positionChanged(quint64 position);
    void durationChanged(quint64 duration);
    void mediaChanged(const QMediaContent& media);
    void currentIndexChanged(int position);
    void mediaStatusChanged(QMediaPlayer::MediaStatus);
    //EMITTED BY PLAYER ITSELF
    void addedTracksSuccessfully();
    void addTracksFailed();
    void removedTracksSuccessfully();
    void removeTracksFailed();
};

#endif // PLAYER_H
