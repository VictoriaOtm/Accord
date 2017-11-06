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

    void curAudioPosChanged(int audioPosition);
};

#endif // PLAYER_H
