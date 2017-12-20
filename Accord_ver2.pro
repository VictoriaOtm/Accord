#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T14:02:04
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
CONFIG += c++11

#LIBS += /usr/local/lib/libprotobuf.so
#PROTOS += /home/yury/Qt_projects/a.proto
#PROTOS = a.proto b.proto
#include(protobuf.pri)

BITSIZE = $$system(getconf LONG_BIT)
 if (contains(BITSIZE, 64)) {
     LIBS += /usr/lib/x86_64-linux-gnu/libprotobuf.so
 }
 if (contains(BITSIZE, 32)) {
     LIBS += /usr/lib/libprotobuf.so
 }
 PROTOS = a.proto
 include(protobuf.pri)

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
    ui.qrc

OTHER_FILES += a.proto


