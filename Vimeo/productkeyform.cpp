#include "productkeyform.h"
#include "ui_productkeyform.h"

ProductKeyForm::ProductKeyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductKeyForm)
{
    ui->setupUi(this);
}

ProductKeyForm::~ProductKeyForm()
{
    delete ui;
}
