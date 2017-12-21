#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "maincontroller.h"
#include "uploadwincontroller.h"
#include "player.h"

class Application
{
public:
    explicit Application();
    int run(int argc, char* argv[]);

private:
    void connectPlayerWithController(MainController &mainController);
    void connectUploadWithController(MainController &mainController, UploadWinController &uploadWinController);
    void connectPlayerWithUpload(UploadWinController &uploadWinController);

};

#endif // APPLICATION_H
