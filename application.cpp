#include "application.h"

Application::Application()
{

}

Application::run(){
    QApplication a(argc, argv);
    Player player;

    return a.exec();
}
