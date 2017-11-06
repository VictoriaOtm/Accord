#include "maincontroller.h"


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
    QStringList modelNames;

    // добавим только новые треки в currentList
    foreach(Audio song, tracks){
        if( !currentList.contains(song) ){
            currentList += song;

            // в этом блоке мы будем переводить QVector<Audio>
            // в формат QStringList, который может отображать mainWin
            QString authors;
            for(QString author: song.GetAuthors()){
                authors += author + " ";
            }
            modelNames.append(song.GetFilename());
            //+ ": " + iter->GetTitle() + ", " + authors);
            // блок закончился
        }

        mainWin.setAudioListModel(modelNames);
    }
}
