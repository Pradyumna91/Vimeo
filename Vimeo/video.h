#ifndef VIDEO_H
#define VIDEO_H

#include <QString>
#include <QList>
#include <QStringList>

class Video
{
public:

    enum UPLOAD_SITES
    {
        YOUTUBE,
        VIMEO,
        METACAFE,
        DAILYMOTION
    };

    static QStringList getUploadSitesAsStrings();
    static UPLOAD_SITES getUploadSiteFromString(QString uploadSiteName);

    Video(QString title, QString desc, QString filepath, QStringList tags, QList<UPLOAD_SITES> sites);
    QString getTitle();
    QString getDescription();
    QStringList getTags();
    QString getFilepath();
    QList<UPLOAD_SITES> getUploadSites();

private:
    QString title;
    QString description;
    QStringList tags;
    QString filepath;
    QList<UPLOAD_SITES> sites;
};

#endif // VIDEO_H
