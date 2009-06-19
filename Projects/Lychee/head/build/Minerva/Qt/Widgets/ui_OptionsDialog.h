/********************************************************************************
** Form generated from reading ui file 'OptionsDialog.ui'
**
** Created: Thu Apr 30 11:46:40 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include "QtTools/StringsView.h"

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QtTools::StringsView *_optionsTreeWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *addRowButton;
    QPushButton *removeRowButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
    if (OptionsDialog->objectName().isEmpty())
        OptionsDialog->setObjectName(QString::fromUtf8("OptionsDialog"));
    OptionsDialog->resize(549, 527);
    vboxLayout = new QVBoxLayout(OptionsDialog);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    groupBox = new QGroupBox(OptionsDialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    vboxLayout1 = new QVBoxLayout(groupBox);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    _optionsTreeWidget = new QtTools::StringsView(groupBox);
    _optionsTreeWidget->setObjectName(QString::fromUtf8("_optionsTreeWidget"));

    vboxLayout1->addWidget(_optionsTreeWidget);


    vboxLayout->addWidget(groupBox);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    addRowButton = new QPushButton(OptionsDialog);
    addRowButton->setObjectName(QString::fromUtf8("addRowButton"));

    hboxLayout->addWidget(addRowButton);

    removeRowButton = new QPushButton(OptionsDialog);
    removeRowButton->setObjectName(QString::fromUtf8("removeRowButton"));

    hboxLayout->addWidget(removeRowButton);


    vboxLayout->addLayout(hboxLayout);

    buttonBox = new QDialogButtonBox(OptionsDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(OptionsDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
    OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("OptionsDialog", "Options", 0, QApplication::UnicodeUTF8));
    addRowButton->setText(QApplication::translate("OptionsDialog", "Add Row", 0, QApplication::UnicodeUTF8));
    removeRowButton->setText(QApplication::translate("OptionsDialog", "Remove Row", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(OptionsDialog);
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
