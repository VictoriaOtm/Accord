#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "playlist.pb.h"
#include "maincontroller.h"
#include "uploadwincontroller.h"
#include "player.h"
#include "playlists.h"


class Application
{
public:
    explicit Application();
    int run(int argc, char* argv[]);

private:

};

#endif // APPLICATION_H
