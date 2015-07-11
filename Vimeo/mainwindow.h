#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    NewVideoWizard *wizrd;
};

#endif // MAINWINDOW_H
