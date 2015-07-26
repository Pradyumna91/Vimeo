#include "uploadedvideosstoragehandler.h"
#include <QList>
#include <QFile>
#include <QTextStream>

QString UploadedVideosStorageHandler::filename = "UploadedVideosList.dat";

QList<Video> UploadedVideosStorageHandler::getPreviouslyUploadedVideos()
{
    QFile storageFile(filename);
    QList<Video> uploadedVideos;

    if(storageFile.exists())
    {
        if(storageFile.open(QIODevice::ReadOnly))
        {
            QTextStream reader(&storageFile);
            while(!reader.atEnd())
            {
                QStringList uploadedVidinfo = reader.readLine().split("||");

                Video videoInfo("", "", uploadedVidinfo[0], QStringList(),
                        QDate::fromString(uploadedVidinfo[2]), QList<Video::UPLOAD_SITES>());
                videoInfo.setUrl(uploadedVidinfo[1]);

                uploadedVideos.append(videoInfo);
            }
        }
        else
        {
            //throw exception here
        }
    }
    storageFile.close();

    return uploadedVideos;
}

void UploadedVideosStorageHandler::addUploadedVideos(QList<Video*> videos)
{
    QFile storageFile(filename);

    bool isOpen;
    switch(storageFile.exists())
    {
    case true:
        isOpen = storageFile.open(QIODevice::Append);
        break;
    case false:
        isOpen = storageFile.open(QIODevice::WriteOnly);
        break;
    }

    if(!isOpen)
        ;//throw exception here

    foreach (Video* video, videos)
    {
        storageFile.write(video->ToString().toLatin1());
    }

    storageFile.close();
}
