#include "video.h"

Video::Video(QString title, QString desc, QString filepath, QStringList tags, QList<UPLOAD_SITES> sites)
{
    this->title = title;
    this->description = desc;
    this->tags = tags;
    this->filepath = filepath;
    this->sites = sites;
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

QStringList Video::getUploadSitesAsStrings()
{
    QStringList list;
    list << "Youtube" << "Vimeo" << "Metacafe" << "DailyMotion";
    return list;
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
