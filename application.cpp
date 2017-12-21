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

    QObject::connect(&mainController.getMainWin(), SIGNAL(saveAsPlaylist(QString, QVector<Audio>&)),
                          &mainController, SLOT(CreatePlaylist(QString, QVector<Audio>&)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                          &mainController, SLOT(NewTracksAdded(QVector<Audio>)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                     &Player::instance(), SLOT(addTracks(QVector<Audio>)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(removeAudio()),
                     &Player::instance(), SLOT(removeTrack()));

    QObject::connect(&Player::instance(), SIGNAL(removedTrackSuccessfully(int)),
                     &mainController.getMainWin(), SLOT(audioRemoveFromList(int)));

    QObject::connect(&Player::instance(), SIGNAL(removedTrackFailed(int)),
                     &mainController, SLOT(trackRemovingFailed(int)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(removeAudio()),
                     &Player::instance(), SLOT(removeTrack()));

    QObject::connect(&Player::instance(), SIGNAL(removedTrackSuccessfully(int)),
                     &mainController.getMainWin(), SLOT(audioRemoveFromList(int)));

    QObject::connect(&Player::instance(), SIGNAL(removedTrackFailed(int)),
                     &mainController, SLOT(trackRemovingFailed(int)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(play(bool)),
                     &Player::instance(), SLOT(play(bool)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(pause(bool)),
                     &Player::instance(), SLOT(pause(bool)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &Player::instance(), SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &Player::instance(), SLOT(prev()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(loopPlaylist(bool)), &Player::instance(), SLOT(loopPlaylist(bool)));
  
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

    QObject::connect(&Player::instance(), SIGNAL(addedTracksSuccessfully(QVector<Audio>)),
                     &mainController, SLOT(NewTracksAdded(QVector<Audio>)));

    QObject::connect(&Player::instance(), SIGNAL(addTracksFailed(QVector<Audio>)),
                     &mainController, SLOT(FailedToAddTracks(QVector<Audio>)));


    mainController.start();

    return application.exec();
}
