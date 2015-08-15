#ifndef NEWVIDEOWIZARD_H
#define NEWVIDEOWIZARD_H

#include <QWizard>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QProgressDialog>
#include <QThread>

#include "videouploader.h"
#include "uploadmanager.h"
#include "duplicatevideo.h"
#include "transformer.h"

namespace Ui {
class NewVideoWizard;
}

class NewVideoWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewVideoWizard(QWidget *parent = 0);
    ~NewVideoWizard();
    void initializePage(int id);
    void cleanupPage(int id);
    bool validateCurrentPage();

private slots:
    void chooseVideoFile();
    void chooseImageFile();
    void handleEditVideoDone(QString editedVideo);

public slots:
    void createCopies();
    void uploadVideos();
    void togglePlayPause(bool checked);

signals:
    void uploadStarted(QList<Video*> videosBeingUploaded);
    void startVideoEdit(QString videoFilepath, QString imageFilepath);

private:
    Ui::NewVideoWizard *ui;
    DuplicateVideo* videoDuplicator;
    QString videoFilename;
    QVideoWidget *videoPlayer;
    QMediaPlayer *previewPlayer;
    QPushButton *playPauseToggleButton;
    QLineEdit *keywordsTextbox;
    QLineEdit *descriptionTextbox;
    QLineEdit *origVideoPathTextbox;
    QLineEdit *origOverlayImagePathTextbox;
    QPushButton *browseForVideoButton;
    QPushButton *browseForOverlayImageButton;
    QLineEdit *titleTextbox;
    QGridLayout *videoDetailsLayout;
    QLabel *keywordsLabel;
    QLabel *descriptionLabel;
    QLabel *titleLabel;
    QLabel *filenameLabels;
    QLabel *chooseVideoLabel;
    QLabel *chooseOverlayImageLabel;

    QThread* videoEditThread;
    Transformer* transformer;
    QProgressDialog *videoEditingProgressDialog;

    QStringList *newFilenames;
    QString origVideoFilepath;
    QString overlayImageFilepath;

    void addImageToVideo();
    void initializeEditVideoPage();
    void cleanupEditVideoPage();
    void initializeAnnotationsPage();
    void cleanUpAnnotationsPage();
    void initializeUploadPage();
    void cleanupUploadPage();
};

#endif // NEWVIDEOWIZARD_H
