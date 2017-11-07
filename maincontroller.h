#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "audio.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController(){};
    ~MainController(){};
    void start();
    void openMainWin();
    MainWindow& getMainWin();

public slots:
    void NewTracksAdded(QVector<Audio> tracks);

private:
    MainWindow mainWin;
    QVector<Audio> currentList;
};

#endif // MAINCONTROLLER_H
