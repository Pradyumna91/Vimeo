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
#include "videouploader.h"
#include "uploadmanager.h"
#include "duplicatevideo.h"

namespace Ui {
class NewVideoWizard;
}

class NewVideoWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewVideoWizard(QWidget *parent = 0);
    NewVideoWizard(QString videoFilename, QWidget *parent = 0);
    ~NewVideoWizard();
    void initializePage(int id);
    void cleanupPage(int id);
    bool validateCurrentPage();

public slots:
    void createCopies();
    void uploadVideos();
    void togglePlayPause(bool checked);

signals:
    void uploadStarted(QList<Video*> videosBeingUploaded);

private:
    Ui::NewVideoWizard *ui;
    DuplicateVideo* videoDuplicator;
    QString videoFilename;
    QVideoWidget *videoPlayer;
    QMediaPlayer *previewPlayer;
    QPushButton *playPauseToggleButton;
    QLineEdit *keywordsTextbox;
    QLineEdit *descriptionTextbox;
    QLineEdit *titleTextbox;
    QGridLayout *videoDetailsLayout;
    QLabel *keywordsLabel;
    QLabel *descriptionLabel;
    QLabel *titleLabel;
    QLabel *filenameLabels;

    QStringList *newFilenames;

    void initializeFirstPage();
    void cleanUpFirstPage();
    void initializeSecondPage();
    void cleanupSecondPage();
};

#endif // NEWVIDEOWIZARD_H
