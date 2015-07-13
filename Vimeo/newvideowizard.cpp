#include "newvideowizard.h"
#include "ui_newvideowizard.h"
#include "youtubeuploader.h"
#include "video.h"

#include <QVBoxLayout>
#include <QMessageBox>

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
    Video* v = new Video("Banu's headphones", "look at the lighting!!", "/home/pradyumna/Downloads/testvid.webm", tags);
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

void NewVideoWizard::initializePage(int id)
{
    switch(id)
    {
    case 0:
        initializeFirstPage();
        break;
    case 1:
        initializeSecondPage();
        break;
    }
}

void NewVideoWizard::cleanupPage(int id)
{
    switch(id)
    {
    case 0:
        cleanUpFirstPage();
        break;
    case 1:
        cleanupSecondPage();
        break;
    }
}

void NewVideoWizard::initializeFirstPage()
{
    videoPlayer = new QVideoWidget(ui->addAnnotationsPage);
    previewPlayer = new QMediaPlayer(ui->addAnnotationsPage);

    previewPlayer->setMedia(QUrl::fromLocalFile(videoFilename));
    previewPlayer->setVideoOutput(videoPlayer);
    ui->verticalLayout->addWidget(videoPlayer);

    playPauseToggleButton = new QPushButton("Play", ui->addAnnotationsPage);
    playPauseToggleButton->setCheckable(true);
    ui->verticalLayout->addWidget(playPauseToggleButton);

    videoDetailsLayout = new QGridLayout(ui->addAnnotationsPage);
    keywordsTextbox = new QLineEdit(ui->addAnnotationsPage);
    keywordsLabel = new QLabel("Keywords:", ui->addAnnotationsPage);
    descriptionTextbox = new QLineEdit(ui->addAnnotationsPage);
    descriptionLabel = new QLabel("Description:", ui->addAnnotationsPage);

    videoDetailsLayout->addWidget(keywordsLabel,0,0,1,1);
    videoDetailsLayout->addWidget(keywordsTextbox,0,1,1,1);
    videoDetailsLayout->addWidget(descriptionLabel,1,0,1,1);
    videoDetailsLayout->addWidget(descriptionTextbox,1,1,1,1);

    //ui->verticalLayout->addStretch();
    ui->verticalLayout->addLayout(videoDetailsLayout);

    connect(playPauseToggleButton, SIGNAL(toggled(bool)), this, SLOT(togglePlayPause(bool)));
}

void NewVideoWizard::cleanUpFirstPage()
{
    delete videoPlayer;
    delete previewPlayer;
    delete playPauseToggleButton;
    delete keywordsLabel;
    delete keywordsTextbox;
    delete descriptionLabel;
    delete descriptionTextbox;
    delete videoDetailsLayout;
}

void NewVideoWizard::initializeSecondPage()
{

}

void NewVideoWizard::cleanupSecondPage()
{

}

bool NewVideoWizard::validateCurrentPage()
{
    if(this->currentId() == 0)
    {
        if(keywordsTextbox->text().isEmpty() || descriptionTextbox->text().isEmpty())
        {
            QMessageBox::information(this, "Incomplete input", "The keyword and desription fields cannot be empty", QMessageBox::Ok);
            return false;
        }
        else
            return true;
    }
}
