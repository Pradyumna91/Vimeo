#include "newvideowizard.h"
#include "ui_newvideowizard.h"
#include "youtubeuploader.h"
#include "video.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileInfo>
#include <QStringList>
#include <QList>

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
    newFilenames = new QStringList();
    ui->setupUi(this);
}

NewVideoWizard::~NewVideoWizard()
{
    delete ui;
}

void NewVideoWizard::uploadVideos()
{
    QStringList tags = keywordsTextbox->text().split(";");
    QList<Video*> videoList;
    QList<Video::UPLOAD_SITES> site;
    site.append(Video::YOUTUBE);
    for(int i = 0; i < newFilenames->length(); i++)
    {
        videoList.append(new Video(titleTextbox->text(), descriptionTextbox->text(), newFilenames->at(i), tags, QDate::currentDate(), site));
    }

    UploadManager::getInstance()->uploadVideos(videoList);
    emit uploadStarted(videoList);
}

void NewVideoWizard::createCopies()
{
    videoDuplicator = new DuplicateVideo(videoFilename, newFilenames);
    connect(videoDuplicator, SIGNAL(completedAllJobs()), this, SLOT(uploadVideos()));
    connect(videoDuplicator, SIGNAL(completedAllJobs()), (MainWindow*)this->parent(), SLOT(hideStatus()));
    videoDuplicator->createCopies();
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
    titleTextbox = new QLineEdit(ui->addAnnotationsPage);
    titleLabel = new QLabel("Title", ui->addAnnotationsPage);

    videoDetailsLayout->addWidget(titleLabel,0,0,1,1);
    videoDetailsLayout->addWidget(titleTextbox,0,1,1,1);
    videoDetailsLayout->addWidget(keywordsLabel,1,0,1,1);
    videoDetailsLayout->addWidget(keywordsTextbox,1,1,1,1);
    videoDetailsLayout->addWidget(descriptionLabel,2,0,1,1);
    videoDetailsLayout->addWidget(descriptionTextbox,2,1,1,1);

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
    QStringList keywordsList = keywordsTextbox->text().split(";");
    QString fileExtension = QFileInfo(videoFilename).suffix();

    filenameLabels = new QLabel[keywordsList.count()];
    for(int i = 0; i < keywordsList.count(); i++)
    {
       QString fname = DuplicateVideo::getCopyFilesDumpPath() + keywordsList.at(i) + "." + fileExtension;
       newFilenames->append(fname);
       filenameLabels[i].setText(fname);
       ui->gridLayout->addWidget(&filenameLabels[i],i,0,1,1);
    }
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
    }

    return true;
}
