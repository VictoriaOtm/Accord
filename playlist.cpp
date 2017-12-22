#include "playlist.h"


Playlist::Playlist() {
    name = "playlist";
    tracks.clear();
}

// во всех конструкторах должно гаранитироваться
// не пустое поле 'nameForPlaylist'
Playlist::Playlist(QString nameForPlaylist) {
    name = nameForPlaylist;
}

Playlist::Playlist(QString nameForPlaylist, QVector<Audio> tracksForPlaylist) {
    name = nameForPlaylist;
    tracks = tracksForPlaylist;

    /*if( tracksToPlaylist.isEmpty() ){
        QErrorMessage errorMessage;
        errorMessage.showMessage("This collections is empty");
        errorMessage.exec();
    } else {
        // вызовем функцию qCopy
        // чтобы не париться из-за передаваемого вектора
        qCopy(tracksForPlaylist.begin(), tracksForPlaylist.end(), tracks.begin());
    }*/
}

 QString Playlist::getName() {
     return name;
 }

 void Playlist::setNamePlaylist(QString nameForPlaylist){
     if( !name.isEmpty() ){
         name = nameForPlaylist;
     }
 }

/*void Playlist::Load() {
    if( name.isEmpty() ){
        return;
    }

    // в процессе разработки
}*/


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
