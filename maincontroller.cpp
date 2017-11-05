#include "maincontroller.h"


void MainController::openMainWin(){
    mainWin.show();
}

void MainController::start(){
    openMainWin();
}

void MainController::NewTracksAdded(QStringList tracks){
    mainWin.setAudioListModel(tracks);
}

MainWindow& MainController::getMainWin(){
    return mainWin;
}
