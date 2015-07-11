#include "uploadmanager.h"
#include "youtubeuploader.h"

UploadManager* UploadManager::instance = NULL;

UploadManager::UploadManager()
{
    uploaders = new QMap<QString, VideoUploader*>();
    uploaders->insert("Youtube", new YoutubeUploader());
}

UploadManager* UploadManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new UploadManager();
    }

    return instance;
}

void UploadManager::uploadVideos(QString filename)
{
    initialiseUploaders(filename);
}

void UploadManager::initialiseUploaders(QString filename)
{
//    foreach (uploaders->uniqueKeys(), key) {
//        if(uploaders[key] == NULL)
//        {

//        }
//    }
}
