#ifndef NEWVIDEOWIZARD_H
#define NEWVIDEOWIZARD_H

#include <QWizard>

namespace Ui {
class NewVideoWizard;
}

class NewVideoWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewVideoWizard(QWidget *parent = 0);
    ~NewVideoWizard();

private:
    Ui::NewVideoWizard *ui;
};

#endif // NEWVIDEOWIZARD_H
