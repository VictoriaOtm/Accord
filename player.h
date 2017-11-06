#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <iostream>


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
};

#endif // PLAYER_H
