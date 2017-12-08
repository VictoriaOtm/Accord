#include "playlist.h"

void Playlist::setNamePlaylist(QString nameForPlaylist){
    if( !name.isEmpty() ){
        name = nameForPlaylist;
    }
}


// во всех конструкторах должно гаранитироваться
// не пустое поле 'nameForPlaylist'
Playlist::Playlist(QString nameForPlaylist) {
    name = nameForPlaylist;
}

Playlist::Playlist(QString nameForPlaylist, QVector<Audio>& tracksForPlaylist) {
    name = nameForPlaylist;

    /*if( tracksToPlaylist.isEmpty() ){
        QErrorMessage errorMessage;
        errorMessage.showMessage("This collections is empty");
        errorMessage.exec();
    } else {*/
        // вызовем функцию qCopy
        // чтобы не париться из-за передаваемого вектора
            qCopy(tracksForPlaylist.begin(), tracksForPlaylist.end(), tracks.begin());
    //}
}

void Playlist::Load() {
    if( name.isEmpty() ){
        return;
    }

    // в процессе разработки
}

void Playlist::Save() {
    if( name.isEmpty() ){
        return;
    }

    // в процессе разработки
    return;
}
