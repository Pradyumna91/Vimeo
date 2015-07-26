#ifndef UPLOADEDVIDEOSSTORAGEHANDLER_H
#define UPLOADEDVIDEOSSTORAGEHANDLER_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QDate>
#include "video.h"

//struct UploadedVideo
//{
//    QString filename;
//    QUrl url;
//    QDate uploadDate;

//public:
//    UploadedVideo(QString file, QUrl url, QString date)
//    {
//        this->filename = file;
//        this->url = url;
//        this->uploadDate = QDate::fromString(date, Qt::TextDate);
//    }
//};

class UploadedVideosStorageHandler
{
private:
    static QString filename;

public:
    static QList<Video> getPreviouslyUploadedVideos();
    static void addUploadedVideos(QList<Video*>);
};

#endif // UPLOADEDVIDEOSSTORAGEHANDLER_H
