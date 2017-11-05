#include <iostream>
#include "player.h"

static Player& Player::Instance(){
    static Player p;
    return p;
}

Player::Player(){
    player.setPlaylist(new QMediaPlaylist(&player));
    QObject::connect(&player, &QMediaPlayer::audioAvailableChanged, &Player::AudioAvailableChanged);
    QObject::connect(&player, &QMediaPlayer::posititionChanged, &Player::PositionChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentMediaChanged, &Player::MediaChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentIndexChanged, &Player::CurrentIndexChanged);
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

void Player::SetPosition(qint64 position){
    player.setPosition(position);
}

void Player::AddTracks(const QVector<Audio>& newTracks){
    QList<QMediaContent> tracks;
    for(auto i = newTracks.begin() ; i != newTracks.end() ; ++i){
        QMediaContent track(QMediaResource( QUrl::fromLocalFile(i->GetPath()) )); //create a QT media object by track path
        tracks.append(track);
    }
    if(!player.playlist()->addMedia(tracks)){
        std::cerr << "Error while adding media to playlist in player" << std::endl;
        std::cerr << player.playlist()->errorString().toStdString() << std::endl;
        emit AddTracksFailed();
    }else{
        emit AddedTracksSuccessfully();
    }
}

void Player::RemoveTracks(int start, int end){
    if(!player.playlist()->removeMedia(start, end)){
        emit RemoveTracksFailed();
    }else{
        emit RemovedTracksSuccessfully();
    }
}

void Player::AddTrack(const Audio &newTrack){
    QMediaContent track(QMediaResource( QUrl::fromLocalFile(newTrack.GetPath()) ));
    if(!player.playlist()->addMedia(track)){
        std::cerr << "Error while adding media to playlist in player" << std::endl;
        std::cerr << player.playlist()->errorString().toStdString() << std::endl;
        emit AddTracksFailed();
    }else{
        emit AddedTracksSuccessfully();
    }
}

void Player::RemoveTrack(int trackNum){
    if(!player.playlist()->removeMedia(trackNum)){
        emit RemoveTracksFailed();
    }else{
        emit RemovedTracksSuccessfully();
    }
}
