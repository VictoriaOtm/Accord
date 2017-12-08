#include <iostream>
#include "player.h"

Player& Player::instance(){
    static Player p;
    return p;
}


Player::Player(): selectedAudioPosition(0){
    player.setPlaylist(new QMediaPlaylist(&player));
    QObject::connect(&player, &QMediaPlayer::audioAvailableChanged, this, &Player::audioAvailableChanged);
    QObject::connect(&player, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentMediaChanged, this, &Player::mediaChanged);
    QObject::connect(player.playlist(), &QMediaPlaylist::currentIndexChanged, this, &Player::currentIndexChanged);
    QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, this, &Player::mediaStatusChanged);
    QObject::connect(&player, &QMediaPlayer::durationChanged, this, &Player::audioDurationChanged);
}


void Player::play(bool playPauseStatus){
    //player.setVolume(100);
    if(playPauseStatus)
        player.play();
}

void Player::pause(bool playPauseStatus){
    if(!playPauseStatus)
        player.pause();
}


void Player::stop(){
    player.stop();
}

void Player::prev(){
    player.media().playlist()->previous();
    selectedAudioPosition = player.playlist()->currentIndex();
}

void Player::next(){
    player.media().playlist()->next();
    selectedAudioPosition = player.playlist()->currentIndex();
}

void Player::setVolume(int volume){
    player.setVolume(volume);
}


void Player::setPlayingPosition(int position){
    player.playlist()->setCurrentIndex(position);
    if (player.state() == QMediaPlayer::PausedState){
        player.play();
        //emit mediaStatusChanged(QMediaPlayer::MediaStatus);
    }
}

void Player::setSelectedAudioPosition(int position){
    selectedAudioPosition = position;
}

void Player::addTracks(const QVector<Audio>& newTracks){
    QList<QMediaContent> tracks;  //готовим массив для добавления в плейлист
    QList<QString> errors; //массив для возврата непринятых файлов в интерфейс
    QMimeDatabase db;       //инициализируем базу данных MIME типов для проверки типа файла
    for(Audio& audio: newTracks){
        QMimeType type = db.mimeTypeForFile(audio.GetPath(), QMimeDatabase::MatchContent); //получаем MIME тип файла на основе его контента
        if(SUPPORTED_FORMATS.contains(type)){ //если такой тип поддерживается
            QMediaContent track(QUrl::fromLocalFile(audio.GetPath())); //то конструируем MediaContent на его основе
            qDebug() << "Adding track " << audio.GetPath();
            qDebug() << type.name();
            qDebug() << type.parentMimeTypes();
            tracks.append(track); //добавляем к трекам, которые пойдут в плейлист
        }else{
            //добавляем имя файла к массиву ошибок
            errors.append(audio.GetPath());
        }
    }
    if(!player.playlist()->addMedia(tracks)){
        std::cerr << "Error while adding media to playlist in player" << std::endl;
        std::cerr << player.playlist()->errorString().toStdString() << std::endl;
        emit addTracksFailed();
    }else{
        if(!errors.empty()){
            //подать сигнал о непринятых файлах
        }
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
