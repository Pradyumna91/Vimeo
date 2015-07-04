/********************************************************************************
** Form generated from reading UI file 'productkeyform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTKEYFORM_H
#define UI_PRODUCTKEYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductKeyForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *txtProductKey;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ProductKeyForm)
    {
        if (ProductKeyForm->objectName().isEmpty())
            ProductKeyForm->setObjectName(QStringLiteral("ProductKeyForm"));
        ProductKeyForm->resize(402, 150);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProductKeyForm->sizePolicy().hasHeightForWidth());
        ProductKeyForm->setSizePolicy(sizePolicy);
        ProductKeyForm->setMinimumSize(QSize(402, 150));
        ProductKeyForm->setMaximumSize(QSize(402, 150));
        verticalLayout_2 = new QVBoxLayout(ProductKeyForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(ProductKeyForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        txtProductKey = new QLineEdit(ProductKeyForm);
        txtProductKey->setObjectName(QStringLiteral("txtProductKey"));

        verticalLayout->addWidget(txtProductKey);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(ProductKeyForm);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy1);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ProductKeyForm);

        QMetaObject::connectSlotsByName(ProductKeyForm);
    } // setupUi

    void retranslateUi(QWidget *ProductKeyForm)
    {
        ProductKeyForm->setWindowTitle(QApplication::translate("ProductKeyForm", "Product Key", 0));
        label_2->setText(QApplication::translate("ProductKeyForm", "Please enter the product key:", 0));
    } // retranslateUi

};

namespace Ui {
    class ProductKeyForm: public Ui_ProductKeyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTKEYFORM_H
