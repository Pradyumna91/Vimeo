#include "uploadedvideosstoragehandler.h"
#include <QList>
#include <QFile>
#include <QTextStream>

QString UploadedVideosStorageHandler::filename = "UploadedVideosList.dat";

QList<UploadedVideo> UploadedVideosStorageHandler::getPreviouslyUploadedVideos()
{
    QFile storageFile(filename);
    QList<UploadedVideo> uploadedVideos;

    if(storageFile.exists())
    {
        if(storageFile.open(QIODevice::ReadOnly))
        {
            QTextStream reader(&storageFile);
            while(!reader.atEnd())
            {
                QStringList uploadedVidinfo = reader.readLine().split(",", QString::SkipEmptyParts);
                UploadedVideo videoInfo(uploadedVidinfo[0], QUrl(uploadedVidinfo[1]), uploadedVidinfo[2]);
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

void UploadedVideosStorageHandler::addUploadedVideos(QList<UploadedVideo> videos)
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
        //throw exception here

    foreach (UploadedVideo video, videos)
    {
        QString line = video.filename + "," + video.url.toString() + "," + video.uploadDate.toString(Qt::TextDate);
        storageFile.write(line.toLatin1());
    }

    storageFile.close();
}
