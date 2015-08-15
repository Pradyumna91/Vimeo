#include "duplicatevideo.h"
#include <QFile>
#include <QException>
#include <QSettings>

DuplicateVideo::DuplicateVideo(QString orgnlFilename, QStringList *cpyFilenamesList)
{
    this->originalFilename = orgnlFilename;
    this->copyFilenamesList = new QStringList();
    for(int i = 0; i < cpyFilenamesList->count(); i++)
    {
        this->copyFilenamesList->append(cpyFilenamesList->at(i));
    }

    future = new QFuture<void>[cpyFilenamesList->count()];
    watcher = new QFutureWatcher<void>[cpyFilenamesList->count()];
    numberOfRunningJobs = 0;
    mutex = new QMutex();
}

void DuplicateVideo::createCopies()
{
    QSettings settings;
    QDir().mkdir(settings.value("VideoFilesDumpPath").toString());
    numberOfRunningJobs = copyFilenamesList->count();
    for(int i = 0; i < numberOfRunningJobs; i++)
    {
        future[i] = QtConcurrent::run(this, &DuplicateVideo::createCopy, copyFilenamesList->at(i));
        watcher[i].setFuture(future[i]);
        connect(watcher, SIGNAL(finished()), this, SLOT(completedSingleJob()));
    }
}

void DuplicateVideo::createCopy(QString copyFilename)
{
    QFile file(originalFilename);
    if(!file.copy(copyFilename))
        throw QException();
}

void DuplicateVideo::completedSingleJob()
{
    mutex->lock();
    numberOfRunningJobs--;
    mutex->unlock();

    if(numberOfRunningJobs == 0)
    {
        emit completedAllJobs();
    }
}

QString DuplicateVideo::getCopyFilesDumpPath()
{
    QSettings settings;
    return settings.value("VideoFilesDumpPath").toString();
}
