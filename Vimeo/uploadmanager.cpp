#include "uploadmanager.h"
#include "youtubeuploader.h"

UploadManager* UploadManager::instance = NULL;

UploadManager::UploadManager()
{
    uploadWorkerThreads = new QList<QThread*>();
    uploaders = new QList<VideoUploader*>();
}

UploadManager* UploadManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new UploadManager();
    }

    return instance;
}

void UploadManager::uploadVideos(QList<Video*> videosToUpload)
{
    for(int i = 0; i < videosToUpload.length(); i++)
    {
        uploadSingleVideo(videosToUpload.at(0));
    }
}

void UploadManager::uploadSingleVideo(Video* videoToUpload)
{
    int numberOfSites = videoToUpload->getUploadSites().length();
    VideoUploader* uploaderObj;
    for(int i = 0; i < numberOfSites; i++)
    {
        QThread* worker = new QThread();
        switch(videoToUpload->getUploadSites().at(i))
        {
        case Video::YOUTUBE:
            uploaderObj = new YoutubeUploader();
            uploadWorkerThreads->append(worker);
            uploaders->append(uploaderObj);
            uploaderObj->moveToThread(worker);

            QObject::connect(uploaderObj, SIGNAL(uploadComplete(QString,Video::UPLOAD_SITES)),
                             this, SLOT(handleSingleCompletedDownload(QString,Video::UPLOAD_SITES)));
            worker->start();
            uploaderObj->beginUploadProcess(videoToUpload);
            break;
        case Video::METACAFE:
            break;
        case Video::DAILYMOTION:
            break;
        case Video::VIMEO:
            break;
        }
    }
}

void UploadManager::handleSingleCompletedDownload(QString filepath, Video::UPLOAD_SITES uploadCompletedSite)
{
    bool allCompleted = true;
    for(int i = 0; i < uploadWorkerThreads->length(); i++)
    {
        if(uploadWorkerThreads->at(i)->isRunning())
        {
            allCompleted = false;
            break;
        }
    }

    if(allCompleted)
        emit completedAllUploads();
}

int UploadManager::getUploaderCount()
{
    return uploaders->count();
}

QList<VideoUploader*>* UploadManager::getUploaders()
{
    return uploaders;
}
