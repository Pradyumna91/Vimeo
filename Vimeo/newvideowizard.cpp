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
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>

NewVideoWizard::NewVideoWizard(QWidget *parent) :
    QWizard(parent), ui(new Ui::NewVideoWizard)
{
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
        initializeEditVideoPage();
        break;
    case 1:
        addImageToVideo();
        //initializeAnnotationsPage();
        break;
    case 2:
        initializeUploadPage();
        break;
    }
}

void NewVideoWizard::cleanupPage(int id)
{
    switch(id)
    {
    case 0:
        cleanupEditVideoPage();
        break;
    case 1:
        cleanUpAnnotationsPage();
        break;
    case 2:
        cleanupUploadPage();
        break;
    }
}

void NewVideoWizard::initializeEditVideoPage()
{
    chooseVideoLabel = new QLabel("Choose a video :", ui->editVideoPage);
    chooseOverlayImageLabel = new QLabel("Choose an overlay image : ", ui->editVideoPage);
    origVideoPathTextbox = new QLineEdit(ui->editVideoPage);
    origOverlayImagePathTextbox = new QLineEdit(ui->editVideoPage);
    browseForVideoButton = new QPushButton("Browse..", ui->editVideoPage);
    browseForOverlayImageButton = new QPushButton("Browse..", ui->editVideoPage);

    ui->editVideoLayout->addWidget(chooseVideoLabel, 0,0);
    ui->editVideoLayout->addWidget(origVideoPathTextbox, 0,1);
    ui->editVideoLayout->addWidget(browseForVideoButton, 0,2);
    ui->editVideoLayout->addWidget(chooseOverlayImageLabel, 1,0);
    ui->editVideoLayout->addWidget(origOverlayImagePathTextbox, 1,1);
    ui->editVideoLayout->addWidget(browseForOverlayImageButton, 1,2);

    connect(browseForVideoButton, SIGNAL(clicked(bool)), this, SLOT(chooseVideoFile()));
    connect(browseForOverlayImageButton, SIGNAL(clicked(bool)), this, SLOT(chooseImageFile()));
}

void NewVideoWizard::cleanupEditVideoPage()
{
    delete chooseVideoLabel;
    delete chooseOverlayImageLabel;
    delete origVideoPathTextbox;
    delete origOverlayImagePathTextbox;
    delete browseForVideoButton;
    delete browseForOverlayImageButton;

    delete videoEditThread;
    delete transformer;
}

void NewVideoWizard::addImageToVideo()
{
    transformer = new Transformer();
    videoEditThread = new QThread();

    transformer->moveToThread(videoEditThread);
    connect(transformer, SIGNAL(editingDone(QString)), this, SLOT(handleEditVideoDone(QString)));
    connect(this, SIGNAL(startVideoEdit(QString, QString)), transformer, SLOT(addOverlay(QString,QString)));
    videoEditThread->start();
    emit startVideoEdit(origVideoPathTextbox->text(), origOverlayImagePathTextbox->text());

    videoEditingProgressDialog = new QProgressDialog("Editing Video", "", 0, 0, this);
    videoEditingProgressDialog->setWindowModality(Qt::WindowModal);
    videoEditingProgressDialog->setCancelButton(0);
    videoEditingProgressDialog->show();
}

void NewVideoWizard::handleEditVideoDone(QString editedVideo)
{
    QDir dir(QCoreApplication::applicationDirPath());
    videoFilename = dir.absoluteFilePath(editedVideo);
    videoEditThread->quit();
    initializeAnnotationsPage();
    videoEditingProgressDialog->done(0);
}

void NewVideoWizard::chooseImageFile()
{
    overlayImageFilepath = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Images (*.jpeg *.png *.jpg *.svg *.bmp)"));

    origOverlayImagePathTextbox->setText(overlayImageFilepath);
}

void NewVideoWizard::chooseVideoFile()
{
    origVideoFilepath = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Videos (*.mov *.mpeg4 *.mp4 *.avi *.wmv *.mpegps *.flv *.webm)"));

    origVideoPathTextbox->setText(origVideoFilepath);
}

void NewVideoWizard::initializeAnnotationsPage()
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

void NewVideoWizard::cleanUpAnnotationsPage()
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

void NewVideoWizard::initializeUploadPage()
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

void NewVideoWizard::cleanupUploadPage()
{

}

bool NewVideoWizard::validateCurrentPage()
{
    if(this->currentId() == 1)
    {
        if(keywordsTextbox->text().isEmpty() || descriptionTextbox->text().isEmpty())
        {
            QMessageBox::information(this, "Incomplete input", "The keyword and desription fields cannot be empty", QMessageBox::Ok);
            return false;
        }
    }
    else if(this->currentId() == 0)
    {
        if(origVideoPathTextbox->text().isEmpty() || origOverlayImagePathTextbox->text().isEmpty())
        {
            QMessageBox::information(this, "Incomplete input", "Please select a video and an image", QMessageBox::Ok);
            return false;
        }
    }

    return true;
}
