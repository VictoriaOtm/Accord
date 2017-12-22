#include "playlist.h"


Playlist::Playlist() {
    name = "playlist";
    tracks.clear();
}

// далее во всех конструкторах должно гаранитироваться
// не пустое поле 'nameForPlaylist'
Playlist::Playlist(QString nameForPlaylist) {
    name = nameForPlaylist;
}

Playlist::Playlist(const protobuf::Playlist proto_playlist) {
    name = QString::fromStdString( proto_playlist.name() );

    for( int i = 0; i < proto_playlist.audio_size(); i++ ) {
        tracks.push_back( Audio(QString::fromStdString( proto_playlist.audio().Get(i).path() )) );
    }
}

Playlist::Playlist(QString nameForPlaylist, QVector<Audio> tracksForPlaylist) {
    name = nameForPlaylist;
    tracks = tracksForPlaylist;
}

 QString Playlist::getName() {
     return name;
 }

 void Playlist::setNamePlaylist(QString nameForPlaylist){
     if( !name.isEmpty() ){
         name = nameForPlaylist;
     }
 }

int Playlist::size() {
    return tracks.size();
}

// функция, необходимая для работы
// проверки корректной загрузки данных из protobuf
QString Playlist::get(int index) {
    if( 0 <= index && index < tracks.size() )
        return tracks[index].GetPath();
    else
        return "";
}

bool Playlist::Save( protobuf::Playlists& playlistsForSaving ) {
    if( name.isEmpty() ){
        return false;
    }

    protobuf::Playlist* playlistForSave = playlistsForSaving.add_playlist();
    playlistForSave->set_name(name.toLocal8Bit());

    foreach( Audio audio, tracks ) {
        protobuf::Playlist_Audio* tracksOfPlaylist = playlistForSave->add_audio();
        tracksOfPlaylist->set_path(audio.GetPath().toLocal8Bit());
    }

    return true;
}
