#include "video.h"

Video::Video(QString title, QString desc, QString filepath, QStringList* tags)
{
    this->title = title;
    this->description = desc;
    this->tags = tags;
    this->filepath = filepath;
}

QString Video::getDescription()
{
    return description;
}

QStringList* Video::getTags()
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
