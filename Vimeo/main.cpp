#include "mainwindow.h"
#include "productkeyhandler.h"
#include "productkeyform.h"
#include <QApplication>
#include <QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QWebView view;
//    view.load(QUrl("http://www.google.com"));
//    view.show();

    MainWindow *mainWindow;
    ProductKeyForm *productKeyWindow;

    if(!ProductKeyHandler::isLincensedProduct())
    {
        productKeyWindow = new ProductKeyForm();
        productKeyWindow->show();
    }
    else
    {
        mainWindow = new MainWindow();
        mainWindow->show();
    }

    return a.exec();
}
