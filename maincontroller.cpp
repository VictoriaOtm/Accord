#include <QMessageBox>
#include "maincontroller.h"
#include <QMessageBox>


MainController::MainController(){
    currentPosition = 0;
    QObject::connect(&mainWin, SIGNAL(play(bool)),
                     this, SLOT(playpause(bool)));
}

void MainController::CreatePlaylist() {
    QString nameOfPlaylist;
    while( nameOfPlaylist.isEmpty() ) {
        if( !mainWin.getLineOfText("Cоздание плейлиста", "Введите название плейлиста", nameOfPlaylist) )
            return;
    }

    if( currentList.isEmpty() ) {
        mainWin.showErrorMessage("Нет треков для добавления!");
        return;
    }

     emit saveAsPlaylist(nameOfPlaylist, currentList);
}

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
    // нужно было в старой версии
    //playlistsModel.append("Текущий плейлист");
    //mainWin.setPlaylistsModel(playlistsModel);

    // формирование отображаемых аудиофайлов
    QStringList tracksNames;

    // добавим только новые треки в currentList
    foreach(Audio song, tracks){
        qDebug() << "Adding track to UI " << song.GetFilename();
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
    qDebug() << "Setting audio list model - success";
}


void MainController::printPlaylists() {
    qDebug() << "Success full cath signal";
    QStringList playlistsModel;
    playlistsModel.append("Текущий плейлист");

    for( int i = 0; i < Playlists::instance().Size(); i++ ) {
        playlistsModel.append( Playlists::instance().GetNameOfPlaylist(i) );
    }

    qDebug() << playlistsModel;
    mainWin.setPlaylistsModel(playlistsModel);
}


void MainController::playlistSelected(int position) {
    qDebug() << "New cath, " << position;
    if( position == 0 ){
        currentPosition = position;
        QStringList audioListModel;

        for( int i = 0; i < currentList.size(); i++ ) {
            audioListModel.append( currentList[i].GetFilename() );
        }

        emit TracksAdded(currentList);
        mainWin.setAudioListModelForPlaylist( audioListModel );
        return;
    }

    // т.к. еще существует currentList
    // который идет под '0' номером
    position--;
    if( 0 <= position && position < Playlists::instance().Size() ) {
        currentPosition = position + 1;
        QStringList audioListModel;

        for( int i = 0; i < Playlists::instance().SizeOfPlaylist( currentPosition ); i++ ) {
            audioListModel.append( Playlists::instance().GetNameAudioOfPlaylist(currentPosition, i) );
        }

        emit TracksAdded(Playlists::instance().GetAudioFiles(position));
        mainWin.setAudioListModelForPlaylist( audioListModel );
    }
}

void MainController::FailedToAddTracks(QVector<Audio> failedTracks){
    //вывод окна с ошибками
    qDebug() << "Printing errors";
    QString message = "Не удалось добавить следующие треки: ";
    for(auto track = failedTracks.constBegin() ; track != failedTracks.constEnd() ; ++track){
        message.append(track->GetFilename());
        if(track != failedTracks.constEnd()-1)
            message.append(", ");
    }
    QMessageBox::warning(&mainWin, "Ошибка", message, QMessageBox::Ok);
    qDebug() << "Printing errors: success";
}

void MainController::trackRemovingFailed(int position){
    qDebug() << "Printing errors ";

    QString message = "Не удалось удалить трек";
    QMessageBox::warning(&mainWin, "Ошибка", message, QMessageBox::Ok);
    qDebug() << "Printing errors: success";
}

void MainController::playpause(bool playOrPause){
    if(playOrPause){
        emit play();
    }else{
        emit pause();
    }
}


