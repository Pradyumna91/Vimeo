#include "uploadmanager.h"
#include "youtubeuploader.h"

UploadManager* UploadManager::instance = NULL;

UploadManager::UploadManager()
{
    uploaders = new QMap<UPLOAD_SITES, VideoUploader*>();
    uploaders->insert(YOUTUBE, new YoutubeUploader());

    uploadWorkerThreads = new QList<QThread>();
}

UploadManager* UploadManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new UploadManager();
    }

    return instance;
}

void UploadManager::uploadVideos(Video* videoToUpload, QList<UPLOAD_SITES> sitesToUploadTo)
{
    UPLOAD_SITES site;
    foreach(site, sitesToUploadTo)
    {
        switch(site)
        {
        case YOUTUBE:
            QThread youtubeWorker;
            uploadWorkerThreads->append(youtubeWorker);
            uploaders->value(YOUTUBE)->moveToThread(youtubeWorker);
            QObject::connect(this, SIGNAL(startAllUploads()),
                             uploaders->value(YOUTUBE), SLOT(beginUploadProcess(Video*)));
            QObject::connect(uploaders->value(YOUTUBE), SIGNAL(uploadComplete(UploadManager::UPLOAD_SITES)),
                             this, SLOT(handleSingleCompletedDownload(UPLOAD_SITES)));
            youtubeWorker.start();
            break;
        case METACAFE:
            break;
        case DAILYMOTION:
            break;
        case VIMEO:
            break;
        }
    }
}

void UploadManager::handleSingleCompletedDownload(UPLOAD_SITES uploadCompletedSite)
{
    QThread item;
    bool allCompleted = true;
    foreach(item, uploadWorkerThreads)
    {
        if(item.isRunning())
        {
            allCompleted = false;
            break;
        }
    }

    if(allCompleted)
        emit completedAllUploads();
}
