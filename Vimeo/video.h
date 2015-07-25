#ifndef VIDEO_H
#define VIDEO_H

#include <QString>
#include <QList>
#include <QDate>
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

    Video(QString title, QString desc, QString filepath, QStringList tags, QDate uploadDate, QList<UPLOAD_SITES> sites);
    QString getTitle();
    QString getDescription();
    QStringList getTags();
    QString getFilepath();
    QList<UPLOAD_SITES> getUploadSites();
    QString getUrl();
    QDate getUploadDate();
    qint64 getFileSize();

    void setUrl(QString url);

private:
    QString title;
    QString description;
    QStringList tags;
    QString filepath;
    QList<UPLOAD_SITES> sites;
    QString url;
    QDate uploadDate;
};

#endif // VIDEO_H
