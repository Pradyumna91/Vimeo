#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include "videouploader.h"
#include "video.h"
#include <QObject>
#include <QMap>
#include <QList>
#include <QThread>

class UploadManager
{
    Q_OBJECT
public:
    static UploadManager *getInstance();
    void uploadVideos(Video* videoToUpload, QList<UPLOAD_SITES> sitesToUploadTo);

    enum UPLOAD_SITES
    {
        YOUTUBE,
        VIMEO,
        METACAFE,
        DAILYMOTION
    };

signals:
    void startAllUploads();
    void completedAllUploads();

private:
    static UploadManager *instance;
    QList<QThread> *uploadWorkerThreads;
    QMap<UPLOAD_SITES, VideoUploader*> *uploaders;

    UploadManager();

public slots:
    void handleSingleCompletedDownload(UPLOAD_SITES uploadCompletedSite);
};

#endif // UPLOADMANAGER_H
