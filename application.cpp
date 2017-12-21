#include "application.h"

Application::Application()
{

}

void Application::connectPlayerWithController(MainController &mainController){

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

    QObject::connect(&mainController, SIGNAL(play()),
                     &Player::instance(), SLOT(play()));

    QObject::connect(&mainController, SIGNAL(pause()),
                     &Player::instance(), SLOT(pause()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(removeAudio()),
                     &Player::instance(), SLOT(removeTrack()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(next()),
                     &Player::instance(), SLOT(next()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(prev()),
                     &Player::instance(), SLOT(prev()));

    QObject::connect(&mainController.getMainWin(), SIGNAL(loopPlaylist(bool)),
                     &Player::instance(), SLOT(loopPlaylist(bool)));

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

}

void Application::connectUploadWithController(MainController &mainController, UploadWinController &uploadWinController){
    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                          &mainController, SLOT(NewTracksAdded(QVector<Audio>)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(addAudioFromDisk(MainWindow*)),
                          &uploadWinController, SLOT(Add(MainWindow*)));
}

void Application::connectPlayerWithUpload(UploadWinController &uploadWinController){
    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                     &Player::instance(), SLOT(addTracks(QVector<Audio>)));
}

int Application::run(int argc, char *argv[]){
    QApplication application(argc, argv);
    UploadWinController uploadWinController;
    MainController mainController;

    connectPlayerWithController(mainController);
    connectPlayerWithUpload(uploadWinController);
    connectUploadWithController(mainController, uploadWinController);

    mainController.start();

    return application.exec();
}
