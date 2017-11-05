#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>


class Player : public QObject
{
    Q_OBJECT

public:
    Player();

public slots:
    void play();
    void pause();
    void next();
    void prev();

private:
    QMediaPlayer player;
    QMediaPlaylist mediaPlaylist;

};

#endif // PLAYER_H
