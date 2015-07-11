#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include "videouploader.h"
#include "video.h"
#include <QObject>
#include <QMap>
#include <QList>
#include <QThread>

class UploadManager : public QObject
{
    Q_OBJECT
public:
    static UploadManager *getInstance();
    void uploadVideos(Video* videoToUpload, QList<Video::UPLOAD_SITES> sitesToUploadTo);

signals:
    void startAllUploads();
    void completedAllUploads();

private:
    static UploadManager *instance;
    QList<QThread*> *uploadWorkerThreads;
    QMap<Video::UPLOAD_SITES, VideoUploader*> *uploaders;

    UploadManager();

public slots:
    void handleSingleCompletedDownload(Video::UPLOAD_SITES uploadCompletedSite);
};

#endif // UPLOADMANAGER_H
