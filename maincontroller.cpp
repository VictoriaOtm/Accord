#include "maincontroller.h"

MainController::MainController(){

}

void MainController::openMainWin(){
    mainWin.show();
}

void MainController::start(){
    openMainWin();
}

void MainController::NewTracksAdded(QVector<Audio> tracks){
    QStringList modelNames;
    for(auto iter = tracks.begin() ; iter != tracks.end() ; ++iter){
        QString authors;
        for(QString author: iter->GetAuthors()){
            authors += author + " ";
        }
        modelNames.append(iter->GetFilename() + ": " + iter->GetTitle() + ", " + authors);
    }
    mainWin.setAudioListModel(modelNames);
}

MainWindow& MainController::getMainWin(){
    return mainWin;
}

MainController::~MainController(){

}
