#include "application.h"

Application::Application()
{

}

int Application::run(int argc, char *argv[]){
    QApplication application(argc, argv);
    Player player;
    MainController mainController;
    UploadWinController uploadWinController;

    QObject::connect(&mainController.getMainWin(), SIGNAL(addAudioFromDisk(MainWindow*)),
                          &uploadWinController, SLOT(Add(MainWindow*)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QStringList)),
                          &mainController, SLOT(NewTracksAdded(QStringList)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(play()),
                    &player, SLOT(play()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(pause()),
                     &player, SLOT(pause()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &player, SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &player, SLOT(prev()));

    mainController.start();

    return application.exec();
}
