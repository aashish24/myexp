/********************************************************************************
** Form generated from reading ui file 'SnapShot.ui'
**
** Created: Thu Apr 30 11:45:35 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SNAPSHOT_H
#define UI_SNAPSHOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnapShot
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *_outerFrame;
    QVBoxLayout *vboxLayout1;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem1;
    QCheckBox *_incrementFilename;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QDoubleSpinBox *_frameScale;
    QHBoxLayout *hboxLayout2;
    QLabel *_numSamplesLabel;
    QSpinBox *_numSamples;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem3;
    QPushButton *snapShotButton;
    QSpacerItem *spacerItem4;
    QSpacerItem *spacerItem5;

    void setupUi(QWidget *SnapShot)
    {
    if (SnapShot->objectName().isEmpty())
        SnapShot->setObjectName(QString::fromUtf8("SnapShot"));
    SnapShot->resize(306, 194);
    vboxLayout = new QVBoxLayout(SnapShot);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(9);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _outerFrame = new QFrame(SnapShot);
    _outerFrame->setObjectName(QString::fromUtf8("_outerFrame"));
    _outerFrame->setFrameShape(QFrame::Panel);
    _outerFrame->setFrameShadow(QFrame::Sunken);
    vboxLayout1 = new QVBoxLayout(_outerFrame);
#ifndef Q_OS_MAC
    vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout1->setMargin(9);
#endif
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem);

    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);

    _incrementFilename = new QCheckBox(_outerFrame);
    _incrementFilename->setObjectName(QString::fromUtf8("_incrementFilename"));

    hboxLayout->addWidget(_incrementFilename);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem2);


    vboxLayout1->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label = new QLabel(_outerFrame);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hboxLayout1->addWidget(label);

    _frameScale = new QDoubleSpinBox(_outerFrame);
    _frameScale->setObjectName(QString::fromUtf8("_frameScale"));
    _frameScale->setValue(1);

    hboxLayout1->addWidget(_frameScale);


    vboxLayout1->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    _numSamplesLabel = new QLabel(_outerFrame);
    _numSamplesLabel->setObjectName(QString::fromUtf8("_numSamplesLabel"));
    _numSamplesLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hboxLayout2->addWidget(_numSamplesLabel);

    _numSamples = new QSpinBox(_outerFrame);
    _numSamples->setObjectName(QString::fromUtf8("_numSamples"));
    _numSamples->setMinimum(1);
    _numSamples->setValue(4);

    hboxLayout2->addWidget(_numSamples);


    vboxLayout1->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout3->setSpacing(6);
#endif
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem3);

    snapShotButton = new QPushButton(_outerFrame);
    snapShotButton->setObjectName(QString::fromUtf8("snapShotButton"));

    hboxLayout3->addWidget(snapShotButton);

    spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem4);


    vboxLayout1->addLayout(hboxLayout3);

    spacerItem5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem5);


    vboxLayout->addWidget(_outerFrame);


    retranslateUi(SnapShot);

    QMetaObject::connectSlotsByName(SnapShot);
    } // setupUi

    void retranslateUi(QWidget *SnapShot)
    {
    SnapShot->setWindowTitle(QApplication::translate("SnapShot", "Screenshot", 0, QApplication::UnicodeUTF8));
    _incrementFilename->setText(QApplication::translate("SnapShot", "Increment Filename", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SnapShot", "Frame Scale", 0, QApplication::UnicodeUTF8));
    _numSamplesLabel->setText(QApplication::translate("SnapShot", "Number of Samples", 0, QApplication::UnicodeUTF8));
    snapShotButton->setText(QApplication::translate("SnapShot", "Screenshot", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SnapShot);
    } // retranslateUi

};

namespace Ui {
    class SnapShot: public Ui_SnapShot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAPSHOT_H
