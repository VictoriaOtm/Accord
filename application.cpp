#include "application.h"

Application::Application() {

}


int Application::run(int argc, char *argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    QApplication application(argc, argv);
    application.setWindowIcon(QIcon(QDir::currentPath() + "/icon.ico"));
    MainController mainController;
    Playlists::instance();
    UploadWinController uploadWinController;

    // мои новые сигналы: ошибки и введения данных
    QObject::connect(&Playlists::instance(), SIGNAL(Error(QString)),
                          &mainController.getMainWin(), SLOT(errorMessage(QString)));

    //

    // блок по работе с плейлистами
    QObject::connect(&mainController.getMainWin(), SIGNAL(saveAsPlaylist()),
                              &mainController, SLOT(CreatePlaylist()));

    QObject::connect(&mainController, SIGNAL(saveAsPlaylist(QString, QVector<Audio>&)),
                          &Playlists::instance(), SLOT(CreatePlaylist(QString, QVector<Audio>&)));

    QObject::connect(&mainController.getMainWin(), SIGNAL(playlistSelected(int)),
                              &mainController, SLOT( playlistSelected(int) ));

    QObject::connect(&Playlists::instance(), SIGNAL(PrintPlaylists()),
                          &mainController, SLOT( printPlaylists() ));

    QObject::connect(&mainController, SIGNAL(TracksAdded(QVector<Audio>)),
                     &Player::instance(), SLOT(addTracks(QVector<Audio>)));

    QObject::connect(&mainController, SIGNAL(LoadTracks(QVector<Audio>)),
                     &Player::instance(), SLOT(loadTracks(QVector<Audio>)));
    //

    Playlists::instance().Load();


    // блок по работе с uploadWinController
    QObject::connect(&mainController.getMainWin(), SIGNAL(addAudioFromDisk(MainWindow*)),
                             &uploadWinController, SLOT(Add(MainWindow*)));

    QObject::connect(&uploadWinController, SIGNAL(TracksAdded(QVector<Audio>)),
                     &Player::instance(), SLOT(addTracks(QVector<Audio>)));
    //


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

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return application.exec();
}
