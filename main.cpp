#include <QDir>
#include <QtCore>
#include <QtMultimedia/QMediaPlayer>
#include <iostream>
#include <assert.h>
#include "working_directory.h"

QTextStream cin(stdin);
QTextStream Qcout(stdout);



int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "Usage: Accord [path-to-music-folder]" << std::endl;
        return -1;
    }
    QString path = argv[1];

    // будущее считывание пути к папке из терминала
    /*QString path;
       std::cout << "Enter a root to the music: ";
       path = cin.readLine();
       Qcout << "Here is your path: " << path << endl;*/

    WorkingDir::WorkingDirectory dir(path);
    if( !dir.IsValidDir() ){
        std::cout << "Bad directory!" << std::endl;
    }

    int numOfSong = -1;
    QString listOfSongs = dir.CreateListOfSongs(WorkingDir::ALPHABET);
    Qcout << listOfSongs << endl;

    std::cout << "\nEnter a number of song to play: ";
    std::cin >> numOfSong;
    assert( (0 < numOfSong) && (numOfSong <= dir.Size()) );
    //Qcout << endl << dir.GetSong(numOfSong) << endl;

    QString songName = path + "//" + dir.GetSong(numOfSong);
    Qcout << endl << songName << endl;


    return 0;
}
