#include "uploadmanager.h"
#include "youtubeuploader.h"

UploadManager* UploadManager::instance = NULL;

UploadManager::UploadManager()
{
    uploaders = new QMap<Video::UPLOAD_SITES, VideoUploader*>();
    uploaders->insert(Video::YOUTUBE, new YoutubeUploader());

    uploadWorkerThreads = new QList<QThread*>();
}

UploadManager* UploadManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new UploadManager();
    }

    return instance;
}

void UploadManager::uploadVideos(Video* videoToUpload, QList<Video::UPLOAD_SITES> sitesToUploadTo)
{
    for(int i = 0; i < sitesToUploadTo.length(); i++)
    {
        QThread* worker = new QThread();
        switch(sitesToUploadTo[i])
        {
        case Video::YOUTUBE:
            uploadWorkerThreads->append(worker);
            uploaders->value(Video::YOUTUBE)->moveToThread(worker);
            QObject::connect(this, SIGNAL(startAllUploads()),
                             uploaders->value(Video::YOUTUBE), SLOT(beginUploadProcess(Video*)));
            QObject::connect(uploaders->value(Video::YOUTUBE), SIGNAL(uploadComplete(Video::UPLOAD_SITES)),
                             this, SLOT(handleSingleCompletedDownload(Video::UPLOAD_SITES)));
            worker->start();
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

void UploadManager::handleSingleCompletedDownload(Video::UPLOAD_SITES uploadCompletedSite)
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
