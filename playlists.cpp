#include "playlists.h"

Playlists& Playlists::instance(){
    static Playlists playlistsSingletone;
    return playlistsSingletone;
}

Playlists::Playlists() {
    currentPlaylists.clear();

    // сначала считать данные из конфиг файла
    // и в зависимости от результата либо подгружать
    // либо нет плейлисты
    this->Load();
}

Playlists::~Playlists() {
    qDebug() << "Save playlists";
    this->Save();
    this->currentPlaylists.clear();
}

void Playlists::Load() {
    std::fstream finBinaryPlaylists("playlists.bin", std::ios::in | std::ios::binary);
    if( !finBinaryPlaylists.is_open() ) {
        emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
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


void Playlists::CreatePlaylist(QString playlistName, QVector<Audio>& playlistTracks) {
    Playlist newPlaylist(playlistName, playlistTracks);
    currentPlaylists.push_back(newPlaylist);
}
