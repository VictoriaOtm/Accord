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
        return currentPlaylists[index].getAudio();
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

Playlist& Playlists::operator [](const int i) {
   // if( 0 <= i && i <= currentPlaylists.size() ) {
        return currentPlaylists[i];
    //} else
    //    return NULL;
}

void Playlists::Load() {
    Playlist queue_playing("Очередь воспроизведения");
    currentPlaylists.push_back(queue_playing);

    std::fstream finBinaryPlaylists("playlists.bin", std::ios::in | std::ios::binary);
    if( !finBinaryPlaylists.is_open() ) {
        //emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
        // выведем на экран пользователю
        // все считанные плейлисты
        emit PrintPlaylists();
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

    // выведем на экран пользователю
    // все считанные плейлисты
    emit PrintPlaylists();
}

void Playlists::Save() {
    if( currentPlaylists.isEmpty() )
        return;

    protobuf::Playlists proto_playlistsForSaving;
    for( int i = 1; i < currentPlaylists.size(); i++ ) {
        if( !currentPlaylists[i].Save(proto_playlistsForSaving) ) {
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
