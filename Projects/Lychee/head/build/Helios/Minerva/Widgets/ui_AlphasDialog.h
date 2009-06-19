/********************************************************************************
** Form generated from reading ui file 'AlphasDialog.ui'
**
** Created: Thu Apr 30 11:46:40 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ALPHASDIALOG_H
#define UI_ALPHASDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AlphasDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTreeView *_alphasTreeView;
    QHBoxLayout *hboxLayout;
    QPushButton *addRowButton;
    QPushButton *removeRowButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AlphasDialog)
    {
    if (AlphasDialog->objectName().isEmpty())
        AlphasDialog->setObjectName(QString::fromUtf8("AlphasDialog"));
    AlphasDialog->resize(413, 366);
    vboxLayout = new QVBoxLayout(AlphasDialog);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _alphasTreeView = new QTreeView(AlphasDialog);
    _alphasTreeView->setObjectName(QString::fromUtf8("_alphasTreeView"));
    _alphasTreeView->setAlternatingRowColors(true);

    vboxLayout->addWidget(_alphasTreeView);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    addRowButton = new QPushButton(AlphasDialog);
    addRowButton->setObjectName(QString::fromUtf8("addRowButton"));

    hboxLayout->addWidget(addRowButton);

    removeRowButton = new QPushButton(AlphasDialog);
    removeRowButton->setObjectName(QString::fromUtf8("removeRowButton"));

    hboxLayout->addWidget(removeRowButton);


    vboxLayout->addLayout(hboxLayout);

    buttonBox = new QDialogButtonBox(AlphasDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(AlphasDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), AlphasDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), AlphasDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(AlphasDialog);
    } // setupUi

    void retranslateUi(QDialog *AlphasDialog)
    {
    AlphasDialog->setWindowTitle(QApplication::translate("AlphasDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    addRowButton->setText(QApplication::translate("AlphasDialog", "Add Row", 0, QApplication::UnicodeUTF8));
    removeRowButton->setText(QApplication::translate("AlphasDialog", "Remove Row", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AlphasDialog);
    } // retranslateUi

};

namespace Ui {
    class AlphasDialog: public Ui_AlphasDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALPHASDIALOG_H
