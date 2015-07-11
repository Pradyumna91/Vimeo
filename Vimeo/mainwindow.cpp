#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newvideowizard.h"
#include "uploadedvideosstoragehandler.h"
#include <QList>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateUploadedVideosTable();
    connect(ui->btnUploadVideo, SIGNAL(clicked(bool)), this, SLOT(openNewUploadWizard()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewUploadWizard()
{
    wizrd = new NewVideoWizard();
    connect(wizrd, SIGNAL(finished(int)), wizrd, SLOT(uploadVideo()));
    wizrd->show();
}

void MainWindow::populateUploadedVideosTable()
{
    QList<UploadedVideo> uploadedVideos = UploadedVideosStorageHandler::getPreviouslyUploadedVideos();

    QStandardItemModel *tableModel = new QStandardItemModel(uploadedVideos.count(), 2, ui->centralWidget);
    QStringList headers = QStringList() << QString("Filename") << QString("URL") << QString("Date Uploaded");
    ui->uploadedVideosTable->setModel(tableModel);
    tableModel->setHorizontalHeaderLabels(headers);

    if(uploadedVideos.count() == 0)
        return;                     // No videos have been uploaded yet

    int row = 0;
    foreach (UploadedVideo video, uploadedVideos)
    {
        QStandardItem *filename = new QStandardItem(video.filename);
        QStandardItem *url = new QStandardItem(video.url.toString());
        QStandardItem *date = new QStandardItem(video.uploadDate.toString(Qt::TextDate));

        tableModel->setItem(row, 0, filename);
        tableModel->setItem(row, 1, url);
        tableModel->setItem(row, 2, date);

        row++;
    }
}
