#include "playlists.h"

Playlists::Playlists() {
    currentPlaylists.clear();
    this->Load();
}

void Playlists::Load() {
    std::fstream finBinaryPlaylists("playlists.bin", std::ios::in | std::ios::binary);
    if( !finBinaryPlaylists.is_open() ) {
        emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
    }

    protobuf::Playlists currentPlaylists;
    if( !currentPlaylists.ParseFromIstream(finBinaryPlaylists) ){
        emit Error("Ошибка при открытии плейлистов!\nЧто-то пошло не так!");
    }

    currentPlaylists.DebugString();
    /*foreach(protobuf::Playlist playlist, currentPlaylists) {
        Playlist* ptrPlaylist = new Playlist(playlist.mutable_name(), vector<Audio>);
    }*/

    finBinaryPlaylists.close();
}

void Playlists::Save() {
    protobuf::Playlists playlistsForSaving;
    foreach( Playlist playlist, currentPlaylists ) {
        if( !playlist.Save(&playlistsForSaving) )
            emit Error("Ошибка при сохранении плейлистов!\nЧто-то пошло не так!");
    }

    // блок сохранения данных
    // непосредственно в файл
    std::fstream foutBinaryPlaylists("playlists.bin", std::ios::out | std::ios::binary | std::ios::trunc);
    if( !foutBinaryPlaylists.is_open() ) {
        emit Error("Ошибка при сохранении плейлистов!\nЧто-то пошло не так!");
    }
    playlistsForSaving.SerializeToOstream(foutBinaryPlaylists);
    foutBinaryPlaylists.close();
}

Playlists& Playlists:instance(){
    static Playlists playlistsSingletone;
    return playlistsSingletone;
}
