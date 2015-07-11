#include "webviewdialog.h"
#include "ui_webviewdialog.h"

WebViewDialog::WebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebViewDialog)
{
    ui->setupUi(this);
}

WebViewDialog::~WebViewDialog()
{
    delete ui;
}
