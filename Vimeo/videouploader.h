#ifndef VIDEOUPLOADER_H
#define VIDEOUPLOADER_H

#include <QNetworkAccessManager>
#include "video.h"

class VideoUploader
{
protected:
    QNetworkAccessManager *mgr;
public:
    VideoUploader();
    virtual void upload(Video* videoToUpload) = 0;
};

#endif // VIDEOUPLOADER_H
