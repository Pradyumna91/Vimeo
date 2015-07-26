#include "uploadmanager.h"
#include "youtubeuploader.h"

UploadManager* UploadManager::instance = NULL;
int UploadManager::completedUploadsCount = 0;

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
    currentlyUploadingVideos = videosToUpload;
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

            QObject::connect(uploaderObj, SIGNAL(uploadComplete()),
                             this, SLOT(handleSingleCompletedDownload()));
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

void UploadManager::handleSingleCompletedDownload()
{
    bool allCompleted;
    completedUploadsCount++;

    if(completedUploadsCount == uploadWorkerThreads->count())
        allCompleted = true;
    else
        allCompleted = false;

    if(allCompleted)
    {
        //Stopping all upload threads once the uploads are complete
        for(int i = 0; i < uploadWorkerThreads->length(); i++)
        {
            uploadWorkerThreads->at(i)->quit();
        }
        for(int i = 0; i < uploaders->length(); i++)
        {
            delete uploaders->at(i);
        }

        //Resetting count to zero for next batch
        uploaders->clear();
        completedUploadsCount = 0;

        emit completedAllUploads(currentlyUploadingVideos);
    }
}

int UploadManager::getUploaderCount()
{
    return uploaders->count();
}

QList<VideoUploader*>* UploadManager::getUploaders()
{
    return uploaders;
}
