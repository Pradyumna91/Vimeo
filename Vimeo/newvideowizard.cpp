#include "newvideowizard.h"
#include "ui_newvideowizard.h"
#include "youtubeuploader.h"
#include "video.h"

NewVideoWizard::NewVideoWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewVideoWizard)
{
    ui->setupUi(this);
}

NewVideoWizard::~NewVideoWizard()
{
    delete ui;
}

void NewVideoWizard::uploadVideo()
{
    h = new YoutubeUploader();
    QStringList* tags = new QStringList();
    tags->append("one");
    tags->append("two");
    Video* v = new Video("TITLE", "DESC", "/home/pradyumna/Downloads/Captain Phillips 2013 HDRip x264 AC3-JYK/Captain Phillips 2013 HDRip x264 AC3-JYK.mkv", tags);
    h->upload(v);
}
