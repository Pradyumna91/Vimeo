#include "videouploader.h"

VideoUploader::VideoUploader()
{
    mgr = new QNetworkAccessManager();
}

const int VideoUploader::timeIntervalForStatusQuery = 3000;
