#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T01:26:53
#
#-------------------------------------------------

# чтобы qt не ругался на multimedia выполнить команду ниже
#sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5

QT       += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI_exampels
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    working_directory.cpp

HEADERS  += mainwindow.h \
    working_directory.h

FORMS    += mainwindow.ui
