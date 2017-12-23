#include "playlists.h"

Playlists& Playlists::instance(){
    static Playlists playlistsSingletone;
    return playlistsSingletone;
}

Playlists::Playlists() {
    currentPlaylists.clear();
}

Playlists::~Playlists() {
    qDebug() << "Save playlists";
    this->Save();
    this->currentPlaylists.clear();
}

int Playlists::SizeOfPlaylist(int index) {
    if( 0 <= index && index < currentPlaylists.size() )
        return currentPlaylists[index].size();
    else
        return -1;
}

QVector<Audio> Playlists::GetAudioFiles(int index) {
    QVector<Audio> result;
    result.clear();

   if( 0 <= index && index < currentPlaylists.size() )
        return currentPlaylists[index];
    else
        return result;
}

QString Playlists::GetNameAudioOfPlaylist(int playlistNumber, int audioNumber) {
    if( 0 <= playlistNumber && playlistNumber < currentPlaylists.size() ) {
        if( 0 <= audioNumber && audioNumber < currentPlaylists[playlistNumber].size() ) {
            return currentPlaylists[playlistNumber].get(audioNumber);
        }
    }

    return "";
}

QString Playlists::GetNameOfPlaylist(int index) {
    if( 0 <= index && index < currentPlaylists.size() ) {
        return currentPlaylists[index].getName();
    }

    return "";
}


void Playlists::Load() {
    std::fstream finBinaryPlaylists("playlists.bin", std::ios::in | std::ios::binary);
    if( !finBinaryPlaylists.is_open() ) {
        //emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
        return;
    }

    protobuf::Playlists proto_currentPlaylists;
    if( !proto_currentPlaylists.ParseFromIstream(&finBinaryPlaylists) ){
        finBinaryPlaylists.close();
        emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
        return;
    }

    // пример, как парсить protobuf
    /*
    qDebug() << proto_currentPlaylists.playlist_size();
    qDebug() << QString::fromStdString( proto_currentPlaylists.playlist().Get(0).audio().Get(0).path() );
    qDebug() << QString::fromStdString( proto_currentPlaylists.playlist().Get(0).audio().Get(1).path() );
   */

    for( int i = 0; i < proto_currentPlaylists.playlist_size(); i++ ) {
        Playlist loadedPlaylist( proto_currentPlaylists.playlist().Get(i) );
        currentPlaylists.push_back( loadedPlaylist );
    }
    finBinaryPlaylists.close();

    // проверочный вывод
    for( int i = 0; i < currentPlaylists.size(); i++ ){
        qDebug() << i;
        for( int j = 0; j < currentPlaylists[i].size(); j++ ){
            qDebug() << currentPlaylists[i].get(j);
        }
    }

    if( !currentPlaylists.isEmpty() ) {
        qDebug() << "Success send PrintPlaylists() signal";
        emit PrintPlaylists();
    }
}

void Playlists::Save() {
    if( currentPlaylists.isEmpty() )
        return;

    protobuf::Playlists proto_playlistsForSaving;
    foreach( Playlist playlist, currentPlaylists ) {
        if( !playlist.Save(proto_playlistsForSaving) ) {
            emit Error("Ошибка при сохранении плейлистов!\nЧто-то пошло не так!");
            return;
        }
    }

    // блок сохранения данных
    // непосредственно в файл
    std::fstream foutBinaryPlaylists("playlists.bin", std::ios::out | std::ios::binary | std::ios::trunc);
    if( !foutBinaryPlaylists.is_open() ) {
        emit Error("Ошибка при сохранении плейлистов!\nЧто-то пошло не так!");
        return;
    }
    proto_playlistsForSaving.SerializeToOstream(&foutBinaryPlaylists);
    foutBinaryPlaylists.close();
}

int Playlists::Size() {
    return currentPlaylists.size();
}

void Playlists::CreatePlaylist(QString playlistName, QVector<Audio>& playlistTracks) {
    Playlist newPlaylist(playlistName, playlistTracks);
    currentPlaylists.push_back(newPlaylist);

    emit PrintPlaylists();
}
