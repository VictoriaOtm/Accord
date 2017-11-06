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

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                          &mainController, SLOT(NewTracksAdded(QVector<Audio>)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                        &Player::instance(), SLOT(addTracks(QVector<Audio>)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(play()),
                    &player, SLOT(play()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(pause()),
                     &player, SLOT(pause()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &player, SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &player, SLOT(prev()));

    /*QObject::connect(&mainController.getMainWin(), SIGNAL(audioSwitched(int)),
                    &player, SLOT(curAudioPosChanged(int)));*/

    mainController.start();

    return application.exec();
}
