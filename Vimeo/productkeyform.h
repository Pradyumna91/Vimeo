#ifndef PRODUCTKEYFORM_H
#define PRODUCTKEYFORM_H

#include <QWidget>

namespace Ui {
class ProductKeyForm;
}

class ProductKeyForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductKeyForm(QWidget *parent = 0);
    ~ProductKeyForm();

public slots:
    void acceptProductKey();

private:
    Ui::ProductKeyForm *ui;
};

#endif // PRODUCTKEYFORM_H
