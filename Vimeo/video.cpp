#include "video.h"
#include <QFileInfo>

Video::Video(QString title, QString desc, QString filepath, QStringList tags, QDate uploadDate, QList<UPLOAD_SITES> sites)
{
    this->title = title;
    this->description = desc;
    this->tags = tags;
    this->filepath = filepath;
    this->sites = sites;
    this->uploadDate = uploadDate;
    this->url = QString("");
}

QString Video::ToString()
{
    return QString("%1||%2||%3\n").arg(filepath).arg(url).arg(uploadDate.toString());
}

QString Video::getDescription()
{
    return description;
}

QStringList Video::getTags()
{
    return tags;
}

QString Video::getTitle()
{
    return title;
}

QString Video::getFilepath()
{
    return filepath;
}

QList<Video::UPLOAD_SITES> Video::getUploadSites()
{
    return sites;
}

QString Video::getUploadSitesAsString(UPLOAD_SITES site)
{
    QString siteNameAsString;

    switch (site) {
    case Video::YOUTUBE:
        siteNameAsString = "Youtube";
        break;
    case Video::DAILYMOTION:
        siteNameAsString = "Dailymotion";
        break;
    case Video::METACAFE:
        siteNameAsString = "Metacafe";
        break;
    case Video::VIMEO:
        siteNameAsString = "Vimeo";
        break;
    }

    return siteNameAsString;
}

Video::UPLOAD_SITES Video::getUploadSiteFromString(QString uploadSiteName)
{
    Video::UPLOAD_SITES site;
    if(uploadSiteName == "Youtube")
        site = Video::YOUTUBE;
    else if(uploadSiteName == "DailyMotion")
        site = Video::DAILYMOTION;
    else if(uploadSiteName == "Metacafe")
        site = Video::METACAFE;
    else
        site = Video::VIMEO;

    return site;
}

QString Video::getUrl()
{
    return url;
}

QDate Video::getUploadDate()
{
    return uploadDate;
}

qint64 Video::getFileSize()
{
    return QFileInfo(filepath).size();
}

void Video::setUrl(QString url)
{
    this->url = url;
}
