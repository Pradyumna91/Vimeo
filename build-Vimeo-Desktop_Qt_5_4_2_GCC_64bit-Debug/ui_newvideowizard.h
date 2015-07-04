/********************************************************************************
** Form generated from reading UI file 'newvideowizard.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWVIDEOWIZARD_H
#define UI_NEWVIDEOWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_NewVideoWizard
{
public:
    QWizardPage *addAnnotationsPage;
    QWizardPage *addKeywordsPage;
    QWizardPage *uploadPage;

    void setupUi(QWizard *NewVideoWizard)
    {
        if (NewVideoWizard->objectName().isEmpty())
            NewVideoWizard->setObjectName(QStringLiteral("NewVideoWizard"));
        NewVideoWizard->resize(800, 638);
        addAnnotationsPage = new QWizardPage();
        addAnnotationsPage->setObjectName(QStringLiteral("addAnnotationsPage"));
        NewVideoWizard->addPage(addAnnotationsPage);
        addKeywordsPage = new QWizardPage();
        addKeywordsPage->setObjectName(QStringLiteral("addKeywordsPage"));
        NewVideoWizard->addPage(addKeywordsPage);
        uploadPage = new QWizardPage();
        uploadPage->setObjectName(QStringLiteral("uploadPage"));
        NewVideoWizard->addPage(uploadPage);

        retranslateUi(NewVideoWizard);

        QMetaObject::connectSlotsByName(NewVideoWizard);
    } // setupUi

    void retranslateUi(QWizard *NewVideoWizard)
    {
        NewVideoWizard->setWindowTitle(QApplication::translate("NewVideoWizard", "Wizard", 0));
    } // retranslateUi

};

namespace Ui {
    class NewVideoWizard: public Ui_NewVideoWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWVIDEOWIZARD_H
