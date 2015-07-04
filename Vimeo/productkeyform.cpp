#include "productkeyform.h"
#include "ui_productkeyform.h"
#include "productkeyhandler.h"
#include "mainwindow.h"

ProductKeyForm::ProductKeyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductKeyForm)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptProductKey()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

ProductKeyForm::~ProductKeyForm()
{
    delete ui;
}

void ProductKeyForm::acceptProductKey()
{
    if(!ui->txtProductKey->text().isEmpty())
    {
        if(ProductKeyHandler::isValidProductKey(ui->txtProductKey->text()))
        {
            this->close();
            MainWindow* window = new MainWindow();
            window->show();
        }
    }
}
