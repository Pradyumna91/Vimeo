#include "newvideowizard.h"
#include "ui_newvideowizard.h"

NewVideoWizard::NewVideoWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewVideoWizard)
{
    ui->setupUi(this);
}

NewVideoWizard::~NewVideoWizard()
{
    delete ui;
}
