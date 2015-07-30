#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newvideowizard.h"
#include "uploadedvideosstoragehandler.h"
#include <QList>
#include <QStandardItemModel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //individualUploadStatusBars = new QList<QProgressBar*>();
    ui->uploadedVideosTable->setColumnCount(4);
    QStringList headers = QStringList() << QString("Filename") << QString("URL") << QString("Upload Status") << QString("Date Uploaded");
    ui->uploadedVideosTable->setHorizontalHeaderLabels(headers);
    statusProgressBar = new QProgressBar(this);
    statusBarTextLabel = new QLabel(this);
    statusProgressBar->hide();
    statusBarTextLabel->hide();
    statusBar()->addPermanentWidget(statusProgressBar);
    statusBar()->addPermanentWidget(statusBarTextLabel);
    populateUploadedVideosTable();
    connect(ui->btnUploadVideo, SIGNAL(clicked(bool)), this, SLOT(openNewUploadWizard()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewUploadWizard()
{
    QString filepath = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "/home",
                                                    tr("Videos (*.mov *.mpeg4 *.mp4 *.avi *.wmv *.mpegps *.flv *.webm)"));

    if(filepath.isNull())
        return;

    wizrd = new NewVideoWizard(filepath, this);
    connect(wizrd, SIGNAL(finished(int)), wizrd, SLOT(createCopies()));
    connect(wizrd, SIGNAL(finished(int)), this, SLOT(showStatus()));
    connect(wizrd, SIGNAL(uploadStarted(QList<Video*>)), this, SLOT(trackUploadStatus(QList<Video*>)));
    connect(UploadManager::getInstance(), SIGNAL(completedAllUploads(QList<Video*>)), this,
            SLOT(completedCurrentUploads(QList<Video*>)));
    wizrd->show();
}

void MainWindow::showStatus()
{
    statusProgressBar->setMinimum(0);
    statusProgressBar->setMaximum(0);
    statusBarTextLabel->setText("Duplicating files...");
    statusProgressBar->show();
    statusBarTextLabel->show();
}

void MainWindow::hideStatus()
{
    statusProgressBar->close();
    statusProgressBar->hide();
    statusBarTextLabel->hide();
}

void MainWindow::populateUploadedVideosTable()
{
    QList<Video> uploadedVideos = UploadedVideosStorageHandler::getPreviouslyUploadedVideos();

    if(uploadedVideos.count() == 0)
        return;                     // No videos have been uploaded yet

    ui->uploadedVideosTable->setRowCount(uploadedVideos.count());

    int row = 0;
    foreach (Video video, uploadedVideos)
    {
        QString filename = QFileInfo(video.getFilepath()).fileName();
        ui->uploadedVideosTable->setItem(row, 0, (new QTableWidgetItem(filename)));
        ui->uploadedVideosTable->setItem(row, 1, (new QTableWidgetItem(video.getUrl())));
        ui->uploadedVideosTable->setItem(row, 2, (new QTableWidgetItem("Completed")));
        ui->uploadedVideosTable->setItem(row, 3, (new QTableWidgetItem(video.getUploadDate().toString())));
        row++;
    }
}

void MainWindow::trackUploadStatus(QList<Video *> videosBeingUploaded)
{
    QList<VideoUploader*>* uploaders = UploadManager::getInstance()->getUploaders();
    int i = 0;
    foreach (Video* video, videosBeingUploaded)
    {
        QProgressBar* bar = new QProgressBar(this);
        bar->setMaximum(100);
        bar->setMinimum(0);
        connect(uploaders->at(i), SIGNAL(uploadStatus(int)), bar, SLOT(setValue(int)));
        individualUploadStatusBars.append(bar);

        int rowNumber = ui->uploadedVideosTable->rowCount();
        QString filename = QFileInfo(video->getFilepath()).fileName();
        ui->uploadedVideosTable->insertRow(rowNumber);
        ui->uploadedVideosTable->setItem(rowNumber, 0, (new QTableWidgetItem(filename)));
        ui->uploadedVideosTable->setItem(rowNumber, 1, (new QTableWidgetItem(video->getUrl())));
        ui->uploadedVideosTable->setCellWidget(rowNumber, 2, bar);
        ui->uploadedVideosTable->setItem(rowNumber, 3, (new QTableWidgetItem(video->getUploadDate().toString())));

        i++;
    }
}

void MainWindow::completedCurrentUploads(QList<Video*> videoList)
{
    UploadedVideosStorageHandler::addUploadedVideos(videoList);

    foreach(Video* vid, videoList)
    {
        delete vid;
    }
}
