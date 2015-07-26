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
    void uploadVideos(QList<Video*> videosToUpload);
    int getUploaderCount();
    QList<VideoUploader *> *getUploaders();

signals:
    void startAllUploads();
    void completedAllUploads(QList<Video*>);

private:
    QList<Video*> currentlyUploadingVideos;
    static UploadManager *instance;
    static int completedUploadsCount;
    QList<QThread*> *uploadWorkerThreads;
    QList<VideoUploader*> *uploaders;

    UploadManager();
    void uploadSingleVideo(Video* videoToUpload);

public slots:
    void handleSingleCompletedDownload();
};

#endif // UPLOADMANAGER_H
