#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
class MainController : public QObject
{
    Q_OBJECT

public:
    MainController();
    ~MainController();
    void start();
    void openMainWin();
    MainWindow& getMainWin();

public slots:
    void NewTracksAdded(QStringList tracks);

private:
    MainWindow mainWin;
};

#endif // MAINCONTROLLER_H
