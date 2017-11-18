#include "uploadwincontroller.h"

UploadWinController::UploadWinController()
{

}

void UploadWinController::Add(MainWindow* mainWin){
    QStringList files = QFileDialog::getOpenFileNames(mainWin,
                                QString::fromUtf8("Выберите аудиофайлы"),
                                QDir::homePath(),
                                "Music (*.mp3 *.mp4 *.wav)");

    QVector<Audio> tracks;
    foreach(QString str, files){
       tracks.append(Audio(str));
       //currentPath = str.mid(0, startIndexNameSong + 1);

       // информация о преобразовании имени песни
       // и пути к ней
       /*qDebug() << str;
       qDebug() << startIndexNameSong;
       qDebug() << str.size() - 1;
       qDebug() << str.mid(startIndexNameSong + 1, str.size() - 1);
       qDebug() << currentPath;*/
    }

    tracksToAdd = tracks;
    emit TracksAdded(tracksToAdd);
}
