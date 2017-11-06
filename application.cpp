#include "application.h"

Application::Application()
{

}

int Application::run(int argc, char *argv[]){
    QApplication application(argc, argv);
    MainController mainController;
    UploadWinController uploadWinController;

    QObject::connect(&mainController.getMainWin(), SIGNAL(addAudioFromDisk(MainWindow*)),
                          &uploadWinController, SLOT(Add(MainWindow*)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QStringList)),
                          &mainController, SLOT(NewTracksAdded(QStringList)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(play()),
                     &Player::instance(), SLOT(play()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(pause()),
                     &Player::instance(), SLOT(pause()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &Player::instance(), SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &Player::instance(), SLOT(prev()));

    mainController.start();

    return application.exec();
}
