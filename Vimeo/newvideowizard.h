#ifndef NEWVIDEOWIZARD_H
#define NEWVIDEOWIZARD_H

#include <QWizard>
#include "videouploader.h"

namespace Ui {
class NewVideoWizard;
}

class NewVideoWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewVideoWizard(QWidget *parent = 0);
    ~NewVideoWizard();

public slots:
    void uploadVideo();

private:
    Ui::NewVideoWizard *ui;
    VideoUploader *h;
};

#endif // NEWVIDEOWIZARD_H
