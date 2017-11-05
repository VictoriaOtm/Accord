#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QApplication>
#include "maincontroller.h"
#include "player.h"

class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application();
    int run(int argc, char* argv[]);

private:

};

#endif // APPLICATION_H
