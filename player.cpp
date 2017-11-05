#include "player.h"

static Player& Player::Instance(){
    static Player p;
    return p;
}

void Player::Play(){
    player.play();
}

void Player::Pause(){
    player.pause();
}

void Player::Stop(){
    player.stop();
}

void Player::Prev(){
    player.media().playlist()->previous();
}

void Player::Next(){
    player.media().playlist()->next();
}

void Player::SetVolume(int volume){
    player.setVolume(volume);
}
