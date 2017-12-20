#include "maincontroller.h"
#include <QMessageBox>


void MainController::openMainWin(){
    mainWin.show();
}

void MainController::start(){
    openMainWin();
}


MainWindow& MainController::getMainWin(){
    return mainWin;
}

void MainController::NewTracksAdded(QVector<Audio> tracks){
    // формирование отображаемых плейлистов
    QStringList playlistsModel;
    playlistsModel.append("Текущий плейлист");
    mainWin.setPlaylistsModel(playlistsModel);

    // формирование отображаемых аудиофайлов
    QStringList tracksNames;

    // добавим только новые треки в currentList
    foreach(Audio song, tracks){
        if( !currentList.contains(song) ){
            currentList += song;

            // в этом блоке мы будем переводить QVector<Audio>
            // в формат QStringList, который может отображать mainWin
            /*QString authors;
            for(QString author: song.GetAuthors()){
                authors += author + " ";
            }

            tracksNames.append(song.GetFilename() + ": " + iter->GetTitle() + ", " + authors);*/
            tracksNames.append(song.GetFilename());
            // блок закончился
        }
    }
    mainWin.setAudioListModel(tracksNames);
}

void MainController::CreatePlaylist(QString nameForPlaylist, QVector<Audio>& tracksToPlaylist) {
    Playlist newPlaylist(nameForPlaylist, tracksToPlaylist);

}

void MainController::trackRemovingFailed(int position){
    qDebug() << "Printing errors ";
    QString message = "Не удалось удалить трек номер ";
    message.append(position + 1);
    QMessageBox::warning(&mainWin, "Ошибка", message, QMessageBox::Ok);
    qDebug() << "Printing errors: success";
}
