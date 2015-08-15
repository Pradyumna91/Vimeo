#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T11:35:21
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets multimediawidgets

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Venom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productkeyform.cpp \
    productkeyhandler.cpp \
    uploadedvideosstoragehandler.cpp \
    newvideowizard.cpp \
    youtubeuploader.cpp \
    webviewdialog.cpp \
    uploadmanager.cpp \
    video.cpp \
    videouploader.cpp \
    simplecrypt.cpp \
    duplicatevideo.cpp \
    transformer.cpp

INCLUDEPATH +=  /usr/local/include/libopenshot/include \
                /usr/local/include/libopenshot-audio/ \
                /usr/include/ImageMagick/

HEADERS  += mainwindow.h \
    productkeyform.h \
    productkeyhandler.h \
    uploadedvideosstoragehandler.h \
    newvideowizard.h \
    youtubeuploader.h \
    webviewdialog.h \
    uploadmanager.h \
    video.h \
    videouploader.h \
    simplecrypt.h \
    duplicatevideo.h \
    transformer.h

FORMS    += mainwindow.ui \
    productkeyform.ui \
    newvideowizard.ui \
    webviewdialog.ui

RESOURCES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopenshot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopenshot
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopenshot

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopenshot-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopenshot-audio
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopenshot-audio

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
