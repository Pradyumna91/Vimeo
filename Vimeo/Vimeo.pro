#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T11:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vimeo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productkeyform.cpp \
    productkeyhandler.cpp \
    uploadedvideosstoragehandler.cpp \
    newvideowizard.cpp

INCLUDEPATH +=  /usr/local/include/libopenshot/ \
                /usr/local/include/libopenshot-audio/

HEADERS  += mainwindow.h \
    productkeyform.h \
    productkeyhandler.h \
    uploadedvideosstoragehandler.h \
    newvideowizard.h

FORMS    += mainwindow.ui \
    productkeyform.ui \
    newvideowizard.ui

RESOURCES +=
