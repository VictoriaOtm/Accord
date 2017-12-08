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

    // сначала скормить новый список песен в плеер
    // проверить его на валидность, а потом уже
    // показывать в интерфейсе юзеру
    /*QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                          &mainController, SLOT(NewTracksAdded(QVector<Audio>)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                        &Player::instance(), SLOT(addTracks(QVector<Audio>)));*/

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                     &Player::instance(), SLOT(addTracks(QVector<Audio>)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(play(bool)),
                     &Player::instance(), SLOT(play(bool)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(pause(bool)),
                     &Player::instance(), SLOT(pause(bool)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &Player::instance(), SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &Player::instance(), SLOT(prev()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(audioSwitched(int)),
                    &Player::instance(), SLOT(setPlayingPosition(int)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(audioSelected(int)),
                     &Player::instance(), SLOT(setSelectedAudioPosition(int)));

    QObject::connect(&Player::instance(), SIGNAL(currentIndexChanged(int)),
                     &mainController.getMainWin(), SLOT(itemIndexChanged(int))),

    QObject::connect(&Player::instance(), SIGNAL(audioDurationChanged(qint64)),
                     &mainController.getMainWin(), SLOT(curAudioDurationChanged(qint64)));

    QObject::connect(&Player::instance(), SIGNAL(positionChanged(qint64)),
                     &mainController.getMainWin(), SLOT(sliderPositionChanged(qint64)));


    mainController.start();

    return application.exec();
}
