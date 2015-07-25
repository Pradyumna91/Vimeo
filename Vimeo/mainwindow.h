#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include "newvideowizard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void populateUploadedVideosTable();

public slots:
    void openNewUploadWizard();
    void showStatus();
    void hideStatus();
    void trackUploadStatus(QList<Video*> videosBeingUploaded);
    void completedCurrentUploads();

private:
    Ui::MainWindow *ui;
    NewVideoWizard *wizrd;
    QProgressBar* statusProgressBar;
    QLabel* statusBarTextLabel;
    QList<QProgressBar*> individualUploadStatusBars;
};

#endif // MAINWINDOW_H
