#include "uploadwincontroller.h"

UploadWinController::UploadWinController()
{

}

void UploadWinController::Add(MainWindow* mainWin){
    QStringList files = QFileDialog::getOpenFileNames(mainWin,
                                QString::fromUtf8("Выберите аудиофайлы"),
                                QDir::homePath(),
                                "Music (*.mp3 *.mp4 *.wav);;All files (*.*)");

    QStringList namesSongs;
    foreach(QString str, files){
       ssize_t startIndexNameSong = str.lastIndexOf(QString::fromLocal8Bit("/"));
       namesSongs.push_back(str.mid(startIndexNameSong + 1, str.count() - 1));
       //currentPath = str.mid(0, startIndexNameSong + 1);

       // информация о преобразовании имени песни
       // и пути к ней
       /*qDebug() << str;
       qDebug() << startIndexNameSong;
       qDebug() << str.size() - 1;
       qDebug() << str.mid(startIndexNameSong + 1, str.size() - 1);
       qDebug() << currentPath;*/
    }

    tracksToAdd = namesSongs;
    emit TracksAdded(tracksToAdd);
}
