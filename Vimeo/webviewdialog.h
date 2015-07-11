#ifndef WEBVIEWDIALOG_H
#define WEBVIEWDIALOG_H

#include <QDialog>
#include <QWebView>

namespace Ui {
class WebViewDialog;
}

class WebViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebViewDialog(QWidget *parent = 0);
    ~WebViewDialog();
    QWebView* getWebView();

private:
    Ui::WebViewDialog *ui;
};

#endif // WEBVIEWDIALOG_H
