/********************************************************************************
** Form generated from reading ui file 'EditWmsLayerWidget.ui'
**
** Created: Thu Apr 30 11:46:54 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EDITWMSLAYERWIDGET_H
#define UI_EDITWMSLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditWmsLayerWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *_nameLabel;
    QLineEdit *_name;
    QHBoxLayout *hboxLayout1;
    QLabel *_serverLabel;
    QLineEdit *_server;
    QGroupBox *_cacheInfoGroupBox;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QLabel *_numberOfFilesLabel;
    QLabel *_cacheInfoText;
    QLabel *label_2;
    QLabel *_cacheDirectoryText;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem1;
    QPushButton *viewCacheButton;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem2;
    QPushButton *deleteCacheButton;
    QHBoxLayout *hboxLayout4;
    QPushButton *viewAlphasButton;
    QSpacerItem *spacerItem3;
    QPushButton *viewOptionsButton;
    QSpacerItem *spacerItem4;

    void setupUi(QWidget *EditWmsLayerWidget)
    {
    if (EditWmsLayerWidget->objectName().isEmpty())
        EditWmsLayerWidget->setObjectName(QString::fromUtf8("EditWmsLayerWidget"));
    EditWmsLayerWidget->resize(452, 430);
    vboxLayout = new QVBoxLayout(EditWmsLayerWidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    _nameLabel = new QLabel(EditWmsLayerWidget);
    _nameLabel->setObjectName(QString::fromUtf8("_nameLabel"));

    hboxLayout->addWidget(_nameLabel);

    _name = new QLineEdit(EditWmsLayerWidget);
    _name->setObjectName(QString::fromUtf8("_name"));

    hboxLayout->addWidget(_name);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    _serverLabel = new QLabel(EditWmsLayerWidget);
    _serverLabel->setObjectName(QString::fromUtf8("_serverLabel"));

    hboxLayout1->addWidget(_serverLabel);

    _server = new QLineEdit(EditWmsLayerWidget);
    _server->setObjectName(QString::fromUtf8("_server"));

    hboxLayout1->addWidget(_server);


    vboxLayout->addLayout(hboxLayout1);

    _cacheInfoGroupBox = new QGroupBox(EditWmsLayerWidget);
    _cacheInfoGroupBox->setObjectName(QString::fromUtf8("_cacheInfoGroupBox"));
    vboxLayout1 = new QVBoxLayout(_cacheInfoGroupBox);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    _numberOfFilesLabel = new QLabel(_cacheInfoGroupBox);
    _numberOfFilesLabel->setObjectName(QString::fromUtf8("_numberOfFilesLabel"));

    gridLayout->addWidget(_numberOfFilesLabel, 1, 0, 1, 1);

    _cacheInfoText = new QLabel(_cacheInfoGroupBox);
    _cacheInfoText->setObjectName(QString::fromUtf8("_cacheInfoText"));

    gridLayout->addWidget(_cacheInfoText, 1, 1, 1, 1);

    label_2 = new QLabel(_cacheInfoGroupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 0, 0, 1, 1);

    _cacheDirectoryText = new QLabel(_cacheInfoGroupBox);
    _cacheDirectoryText->setObjectName(QString::fromUtf8("_cacheDirectoryText"));

    gridLayout->addWidget(_cacheDirectoryText, 0, 1, 1, 1);


    vboxLayout1->addLayout(gridLayout);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem1);

    viewCacheButton = new QPushButton(_cacheInfoGroupBox);
    viewCacheButton->setObjectName(QString::fromUtf8("viewCacheButton"));

    hboxLayout2->addWidget(viewCacheButton);


    vboxLayout1->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem2);

    deleteCacheButton = new QPushButton(_cacheInfoGroupBox);
    deleteCacheButton->setObjectName(QString::fromUtf8("deleteCacheButton"));

    hboxLayout3->addWidget(deleteCacheButton);


    vboxLayout1->addLayout(hboxLayout3);


    vboxLayout->addWidget(_cacheInfoGroupBox);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    viewAlphasButton = new QPushButton(EditWmsLayerWidget);
    viewAlphasButton->setObjectName(QString::fromUtf8("viewAlphasButton"));

    hboxLayout4->addWidget(viewAlphasButton);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem3);

    viewOptionsButton = new QPushButton(EditWmsLayerWidget);
    viewOptionsButton->setObjectName(QString::fromUtf8("viewOptionsButton"));

    hboxLayout4->addWidget(viewOptionsButton);


    vboxLayout->addLayout(hboxLayout4);

    spacerItem4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem4);


    retranslateUi(EditWmsLayerWidget);

    QMetaObject::connectSlotsByName(EditWmsLayerWidget);
    } // setupUi

    void retranslateUi(QWidget *EditWmsLayerWidget)
    {
    EditWmsLayerWidget->setWindowTitle(QApplication::translate("EditWmsLayerWidget", "Form", 0, QApplication::UnicodeUTF8));
    _nameLabel->setText(QApplication::translate("EditWmsLayerWidget", "Name:", 0, QApplication::UnicodeUTF8));
    _serverLabel->setText(QApplication::translate("EditWmsLayerWidget", "Server:", 0, QApplication::UnicodeUTF8));
    _cacheInfoGroupBox->setTitle(QApplication::translate("EditWmsLayerWidget", "Cache Info", 0, QApplication::UnicodeUTF8));
    _numberOfFilesLabel->setText(QApplication::translate("EditWmsLayerWidget", "Number of files:", 0, QApplication::UnicodeUTF8));
    _cacheInfoText->setText(QApplication::translate("EditWmsLayerWidget", "Number Of FIles", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("EditWmsLayerWidget", "Directory:", 0, QApplication::UnicodeUTF8));
    _cacheDirectoryText->setText(QApplication::translate("EditWmsLayerWidget", "Cache Directory", 0, QApplication::UnicodeUTF8));
    viewCacheButton->setText(QApplication::translate("EditWmsLayerWidget", "View Cache", 0, QApplication::UnicodeUTF8));
    deleteCacheButton->setText(QApplication::translate("EditWmsLayerWidget", "Delete Cache", 0, QApplication::UnicodeUTF8));
    viewAlphasButton->setText(QApplication::translate("EditWmsLayerWidget", "View Alphas", 0, QApplication::UnicodeUTF8));
    viewOptionsButton->setText(QApplication::translate("EditWmsLayerWidget", "View Options", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EditWmsLayerWidget);
    } // retranslateUi

};

namespace Ui {
    class EditWmsLayerWidget: public Ui_EditWmsLayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWMSLAYERWIDGET_H
