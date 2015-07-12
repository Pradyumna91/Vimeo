#include "newvideowizard.h"
#include "ui_newvideowizard.h"
#include "youtubeuploader.h"
#include "video.h"

#include <QVBoxLayout>

NewVideoWizard::NewVideoWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewVideoWizard)
{
    ui->setupUi(this);
}

NewVideoWizard::NewVideoWizard(QString videoFilename, QWidget *parent) :
    QWizard(parent), ui(new Ui::NewVideoWizard)
{
    this->videoFilename = videoFilename;
    ui->setupUi(this);
    videoPlayer = new QVideoWidget(ui->addAnnotationsPage);
    previewPlayer = new QMediaPlayer(ui->addAnnotationsPage);

    previewPlayer->setMedia(QUrl::fromLocalFile(videoFilename));
    previewPlayer->setVideoOutput(videoPlayer);
    ui->addAnnotationsPage->layout()->addWidget(videoPlayer);

    playPauseToggleButton = new QPushButton("Play", ui->addAnnotationsPage);
    playPauseToggleButton->setCheckable(true);
    ui->addAnnotationsPage->layout()->addWidget(playPauseToggleButton);

    connect(playPauseToggleButton, SIGNAL(toggled(bool)), this, SLOT(togglePlayPause(bool)));
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
    Video* v = new Video("TITLE", "DESC", "/home/pradyumna/Downloads/testvid.webm", tags);
    h->beginUploadProcess(v);
}

void NewVideoWizard::togglePlayPause(bool checked)
{
    if(checked)
    {
        previewPlayer->play();
        playPauseToggleButton->setText("Pause");
    }
    else
    {
        previewPlayer->pause();
        playPauseToggleButton->setText("Play");
    }
}
