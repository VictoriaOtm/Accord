#ifndef WORKINGDIRECTORY_H
#define WORKINGDIRECTORY_H
#include <QDir>
#include <QtCore>
#include <iostream>
#include <assert.h>

namespace WorkingDir{

    enum TypeOfSort{
        ALPHABET,   // песни сортируются по алфавиту
        RANDOM      // песни не сортируются
    };


    class WorkingDirectory
    {
    public:
        WorkingDirectory(QString _path);
        ~WorkingDirectory() = default;

        static bool IsValidDir(QString _path);

        bool IsValidDir(void);

        QString CreateListOfSongs(TypeOfSort typeOfSort);

        int Size();

        QString GetSong(const unsigned int i);

    private:
        QString path;
        std::vector<QString> namesOfSongs;
    };

};
#endif // WORKINGDIRECTORY_H
