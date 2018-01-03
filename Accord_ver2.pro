#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T14:02:04
#
#-------------------------------------------------

QT += core gui
QT += multimedia
CONFIG += c++11


BITSIZE = $$system(getconf LONG_BIT)
if (contains(BITSIZE, 64)) {
     LIBS += /usr/lib/x86_64-linux-gnu/libprotobuf.so
}
if (contains(BITSIZE, 32)) {
     LIBS += /usr/lib/libprotobuf.so
}
PROTOS = playlist.proto
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
        audio.cpp \
        playlist.pb.h

HEADERS += mainwindow.h\
        application.h\
        maincontroller.h\
        player.h\
        uploadwincontroller.h\
        playlists.h\
        playlist.h\
        audio.h \
        playlist.pb.cc


FORMS  += mainwindow.ui

RESOURCES += ui.qrc

RC_FILE += icon.rc

OTHER_FILES += playlist.proto

