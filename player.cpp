#include <iostream>
#include "player.h"

static Player& Player::instance(){
    static Player p;
    return p;
}

Player::Player(){
    player.setPlaylist(new QMediaPlaylist(&player));
    QObject::connect(&player, &QMediaPlayer::audioAvailableChanged, &Player::AudioAvailableChanged);
    QObject::connect(&player, &QMediaPlayer::posititionChanged, &Player::PositionChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentMediaChanged, &Player::MediaChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentIndexChanged, &Player::CurrentIndexChanged);
    QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, &Player::MediaStatusChanged);
}

void Player::play(){
    player.play();
}

void Player::pause(){
    player.pause();
}

void Player::stop(){
    player.stop();
}

void Player::prev(){
    player.media().playlist()->previous();
}

void Player::next(){
    player.media().playlist()->next();
}

void Player::setVolume(int volume){
    player.setVolume(volume);
}

void Player::setPosition(qint64 position){
    player.setPosition(position);
}

void Player::addTracks(const QVector<Audio>& newTracks){
    QList<QMediaContent> tracks;
    for(auto i = newTracks.begin() ; i != newTracks.end() ; ++i){
        QMediaContent track(QMediaResource( QUrl::fromLocalFile(i->GetPath()) )); //create a QT media object by track path
        tracks.append(track);
    }
    if(!player.playlist()->addMedia(tracks)){
        std::cerr << "Error while adding media to playlist in player" << std::endl;
        std::cerr << player.playlist()->errorString().toStdString() << std::endl;
        emit addTracksFailed();
    }else{
        emit addedTracksSuccessfully();
    }
}

void Player::removeTracks(int start, int end){
    if(!player.playlist()->removeMedia(start, end)){
        emit removeTracksFailed();
    }else{
        emit removedTracksSuccessfully();
    }
}

void Player::addTrack(const Audio &newTrack){
    QMediaContent track(QMediaResource( QUrl::fromLocalFile(newTrack.GetPath()) ));
    if(!player.playlist()->addMedia(track)){
        std::cerr << "Error while adding media to playlist in player" << std::endl;
        std::cerr << player.playlist()->errorString().toStdString() << std::endl;
        emit addTracksFailed();
    }else{
        emit addedTracksSuccessfully();
    }
}

void Player::removeTrack(int trackNum){
    if(!player.playlist()->removeMedia(trackNum)){
        emit removeTracksFailed();
    }else{
        emit removedTracksSuccessfully();
    }
}
