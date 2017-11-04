#include "application.h"

Application::Application()
{}

int Application::run(int argc, char *argv[]){
    QApplication application(argc, argv);
    Player player;
    MainController mainController;

    mainController.start();

    return application.exec();
}
