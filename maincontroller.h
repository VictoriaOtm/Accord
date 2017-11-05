#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainwindow.h"


class MainController
{
public:
    MainController();

    void start();
    void openMainWin();
    MainWindow& getMainWin();

private:
    MainWindow mainWin;
};

#endif // MAINCONTROLLER_H
