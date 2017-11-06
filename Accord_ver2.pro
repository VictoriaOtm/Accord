#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T14:02:04
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Accord_ver2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        application.cpp\
        maincontroller.cpp\
        player.cpp\
        uploadwincontroller.cpp\
        playlists.cpp\
        playlist.cpp\
        audio.cpp\
        uploadwindow.cpp

HEADERS  += mainwindow.h\
        application.h\
        maincontroller.h\
        player.h\
        uploadwincontroller.h\
        playlists.h\
        playlist.h\
        audio.h \
    uploadwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
