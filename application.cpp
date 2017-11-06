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

    return application.exec();
}
