/********************************************************************************
** Form generated from reading ui file 'BaseAddNetworkLayerWidget.ui'
**
** Created: Thu Apr 30 11:46:40 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BASEADDNETWORKLAYERWIDGET_H
#define UI_BASEADDNETWORKLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseAddNetworkLayerWidget
{
public:
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *_name;
    QLabel *label_2;
    QLineEdit *_server;
    QPushButton *capabilitiesButton;
    QPushButton *getServiceNamesButton;
    QLabel *_serviceNameLabel;
    QLineEdit *_serviceNameLineEdit;
    QGroupBox *_layersGroupBox;
    QVBoxLayout *vboxLayout1;
    QTreeWidget *_layersTree;
    QHBoxLayout *hboxLayout;
    QCheckBox *_addAllAsGroup;
    QCheckBox *_addSelectedAsGroup;
    QGroupBox *groupBox_2;
    QHBoxLayout *hboxLayout1;
    QRadioButton *_pngButton;
    QRadioButton *_tifButton;
    QRadioButton *_jpegButton;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem;
    QPushButton *viewOptionsButton;
    QHBoxLayout *hboxLayout3;
    QLabel *label_3;
    QLineEdit *_cacheDirectory;
    QPushButton *browseDirectory;
    QHBoxLayout *hboxLayout4;
    QCheckBox *_makeDefaultDirectory;

    void setupUi(QWidget *BaseAddNetworkLayerWidget)
    {
    if (BaseAddNetworkLayerWidget->objectName().isEmpty())
        BaseAddNetworkLayerWidget->setObjectName(QString::fromUtf8("BaseAddNetworkLayerWidget"));
    BaseAddNetworkLayerWidget->resize(596, 791);
    vboxLayout = new QVBoxLayout(BaseAddNetworkLayerWidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(BaseAddNetworkLayerWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    _name = new QLineEdit(BaseAddNetworkLayerWidget);
    _name->setObjectName(QString::fromUtf8("_name"));

    gridLayout->addWidget(_name, 0, 1, 1, 1);

    label_2 = new QLabel(BaseAddNetworkLayerWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    _server = new QLineEdit(BaseAddNetworkLayerWidget);
    _server->setObjectName(QString::fromUtf8("_server"));

    gridLayout->addWidget(_server, 1, 1, 1, 1);

    capabilitiesButton = new QPushButton(BaseAddNetworkLayerWidget);
    capabilitiesButton->setObjectName(QString::fromUtf8("capabilitiesButton"));

    gridLayout->addWidget(capabilitiesButton, 1, 3, 1, 1);

    getServiceNamesButton = new QPushButton(BaseAddNetworkLayerWidget);
    getServiceNamesButton->setObjectName(QString::fromUtf8("getServiceNamesButton"));

    gridLayout->addWidget(getServiceNamesButton, 1, 2, 1, 1);

    _serviceNameLabel = new QLabel(BaseAddNetworkLayerWidget);
    _serviceNameLabel->setObjectName(QString::fromUtf8("_serviceNameLabel"));

    gridLayout->addWidget(_serviceNameLabel, 2, 0, 1, 1);

    _serviceNameLineEdit = new QLineEdit(BaseAddNetworkLayerWidget);
    _serviceNameLineEdit->setObjectName(QString::fromUtf8("_serviceNameLineEdit"));

    gridLayout->addWidget(_serviceNameLineEdit, 2, 1, 1, 1);


    vboxLayout->addLayout(gridLayout);

    _layersGroupBox = new QGroupBox(BaseAddNetworkLayerWidget);
    _layersGroupBox->setObjectName(QString::fromUtf8("_layersGroupBox"));
    vboxLayout1 = new QVBoxLayout(_layersGroupBox);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    _layersTree = new QTreeWidget(_layersGroupBox);
    _layersTree->setObjectName(QString::fromUtf8("_layersTree"));

    vboxLayout1->addWidget(_layersTree);


    vboxLayout->addWidget(_layersGroupBox);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    _addAllAsGroup = new QCheckBox(BaseAddNetworkLayerWidget);
    _addAllAsGroup->setObjectName(QString::fromUtf8("_addAllAsGroup"));

    hboxLayout->addWidget(_addAllAsGroup);

    _addSelectedAsGroup = new QCheckBox(BaseAddNetworkLayerWidget);
    _addSelectedAsGroup->setObjectName(QString::fromUtf8("_addSelectedAsGroup"));

    hboxLayout->addWidget(_addSelectedAsGroup);


    vboxLayout->addLayout(hboxLayout);

    groupBox_2 = new QGroupBox(BaseAddNetworkLayerWidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    hboxLayout1 = new QHBoxLayout(groupBox_2);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    _pngButton = new QRadioButton(groupBox_2);
    _pngButton->setObjectName(QString::fromUtf8("_pngButton"));

    hboxLayout1->addWidget(_pngButton);

    _tifButton = new QRadioButton(groupBox_2);
    _tifButton->setObjectName(QString::fromUtf8("_tifButton"));

    hboxLayout1->addWidget(_tifButton);

    _jpegButton = new QRadioButton(groupBox_2);
    _jpegButton->setObjectName(QString::fromUtf8("_jpegButton"));
    _jpegButton->setChecked(true);

    hboxLayout1->addWidget(_jpegButton);


    vboxLayout->addWidget(groupBox_2);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem);

    viewOptionsButton = new QPushButton(BaseAddNetworkLayerWidget);
    viewOptionsButton->setObjectName(QString::fromUtf8("viewOptionsButton"));

    hboxLayout2->addWidget(viewOptionsButton);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_3 = new QLabel(BaseAddNetworkLayerWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout3->addWidget(label_3);

    _cacheDirectory = new QLineEdit(BaseAddNetworkLayerWidget);
    _cacheDirectory->setObjectName(QString::fromUtf8("_cacheDirectory"));

    hboxLayout3->addWidget(_cacheDirectory);

    browseDirectory = new QPushButton(BaseAddNetworkLayerWidget);
    browseDirectory->setObjectName(QString::fromUtf8("browseDirectory"));

    hboxLayout3->addWidget(browseDirectory);


    vboxLayout->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    _makeDefaultDirectory = new QCheckBox(BaseAddNetworkLayerWidget);
    _makeDefaultDirectory->setObjectName(QString::fromUtf8("_makeDefaultDirectory"));

    hboxLayout4->addWidget(_makeDefaultDirectory);


    vboxLayout->addLayout(hboxLayout4);


    retranslateUi(BaseAddNetworkLayerWidget);

    QMetaObject::connectSlotsByName(BaseAddNetworkLayerWidget);
    } // setupUi

    void retranslateUi(QWidget *BaseAddNetworkLayerWidget)
    {
    BaseAddNetworkLayerWidget->setWindowTitle(QApplication::translate("BaseAddNetworkLayerWidget", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Name:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Server:", 0, QApplication::UnicodeUTF8));
    capabilitiesButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Get Layers", 0, QApplication::UnicodeUTF8));
    getServiceNamesButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Get Service Names", 0, QApplication::UnicodeUTF8));
    _serviceNameLabel->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Service Name:", 0, QApplication::UnicodeUTF8));
    _layersGroupBox->setTitle(QApplication::translate("BaseAddNetworkLayerWidget", "Layers", 0, QApplication::UnicodeUTF8));
    _layersTree->headerItem()->setText(0, QApplication::translate("BaseAddNetworkLayerWidget", "1", 0, QApplication::UnicodeUTF8));
    _addAllAsGroup->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Add All As Group", 0, QApplication::UnicodeUTF8));
    _addSelectedAsGroup->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Add Selected As Group", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("BaseAddNetworkLayerWidget", "Image Type", 0, QApplication::UnicodeUTF8));
    _pngButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "image/png", 0, QApplication::UnicodeUTF8));
    _tifButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "image/tif", 0, QApplication::UnicodeUTF8));
    _jpegButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "image/jpeg", 0, QApplication::UnicodeUTF8));
    viewOptionsButton->setText(QApplication::translate("BaseAddNetworkLayerWidget", "View Options", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Cache Directory:", 0, QApplication::UnicodeUTF8));
    browseDirectory->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Browse...", 0, QApplication::UnicodeUTF8));
    _makeDefaultDirectory->setText(QApplication::translate("BaseAddNetworkLayerWidget", "Make default cache directory", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(BaseAddNetworkLayerWidget);
    } // retranslateUi

};

namespace Ui {
    class BaseAddNetworkLayerWidget: public Ui_BaseAddNetworkLayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEADDNETWORKLAYERWIDGET_H
