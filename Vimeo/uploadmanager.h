#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include "videouploader.h"
#include <QObject>
#include <QMap>

class UploadManager
{
public:
    static UploadManager *getInstance();
    void uploadVideos(QString);

private:
    static UploadManager *instance;
    QMap<QString, VideoUploader*> *uploaders;

    UploadManager();
    void initialiseUploaders(QString);
};

#endif // UPLOADMANAGER_H
