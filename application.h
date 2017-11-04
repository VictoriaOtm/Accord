#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "maincontroller.h"
#include "player.h"

class Application
{
public:
    Application();
    run();

private:
    MainController mainController;
};

#endif // APPLICATION_H
