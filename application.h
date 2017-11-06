#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "maincontroller.h"
#include "uploadwincontroller.h"
#include "player.h"
#include "audio.h"

class Application
{
public:
    explicit Application();
    int run(int argc, char* argv[]);

private:

};

#endif // APPLICATION_H
