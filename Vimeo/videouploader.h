#ifndef VIDEOUPLOADER_H
#define VIDEOUPLOADER_H

#include <QNetworkAccessManager>
#include "video.h"

class VideoUploader : public QObject
{
    Q_OBJECT
protected:
    QNetworkAccessManager *mgr;
    virtual void upload() = 0;
public:
    VideoUploader();

public slots:
    virtual void beginUploadProcess(Video* videoToUpload) = 0;

signals:
    void uploadComplete(QString filepath, Video::UPLOAD_SITES currentSite);
    void uploadStatus(int percentOfBytesWritten);
};

#endif // VIDEOUPLOADER_H
