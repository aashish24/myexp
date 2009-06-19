/********************************************************************************
** Form generated from reading ui file 'ClipPlanes.ui'
**
** Created: Thu Apr 30 11:45:35 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CLIPPLANES_H
#define UI_CLIPPLANES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClipPlanes
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *_outerFrame;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QPushButton *clearButton;
    QSpacerItem *spacerItem;
    QCheckBox *_advancedButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QRadioButton *posXAxis;
    QRadioButton *negXAxis;
    QRadioButton *posZAxis;
    QRadioButton *negYAxis;
    QRadioButton *posYAxis;
    QRadioButton *negZAxis;
    QVBoxLayout *vboxLayout2;
    QSlider *_distanceSlider;
    QDoubleSpinBox *_distanceSpinBox;
    QSpacerItem *spacerItem1;
    QFrame *_advancedOptions;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QDoubleSpinBox *_normalX;
    QLabel *label_2;
    QDoubleSpinBox *_normalY;
    QLabel *label_3;
    QDoubleSpinBox *_normalZ;
    QHBoxLayout *hboxLayout2;
    QPushButton *_addButton;
    QPushButton *_removeButton;
    QListWidget *_clipPlaneList;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *ClipPlanes)
    {
    if (ClipPlanes->objectName().isEmpty())
        ClipPlanes->setObjectName(QString::fromUtf8("ClipPlanes"));
    ClipPlanes->resize(342, 610);
    vboxLayout = new QVBoxLayout(ClipPlanes);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
    vboxLayout->setMargin(1);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _outerFrame = new QFrame(ClipPlanes);
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
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    clearButton = new QPushButton(_outerFrame);
    clearButton->setObjectName(QString::fromUtf8("clearButton"));

    hboxLayout->addWidget(clearButton);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    _advancedButton = new QCheckBox(_outerFrame);
    _advancedButton->setObjectName(QString::fromUtf8("_advancedButton"));

    hboxLayout->addWidget(_advancedButton);


    vboxLayout1->addLayout(hboxLayout);

    groupBox = new QGroupBox(_outerFrame);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout = new QGridLayout(groupBox);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout1 = new QGridLayout();
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout1->setMargin(0);
#endif
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    posXAxis = new QRadioButton(groupBox);
    posXAxis->setObjectName(QString::fromUtf8("posXAxis"));

    gridLayout1->addWidget(posXAxis, 0, 0, 1, 1);

    negXAxis = new QRadioButton(groupBox);
    negXAxis->setObjectName(QString::fromUtf8("negXAxis"));

    gridLayout1->addWidget(negXAxis, 0, 1, 1, 1);

    posZAxis = new QRadioButton(groupBox);
    posZAxis->setObjectName(QString::fromUtf8("posZAxis"));

    gridLayout1->addWidget(posZAxis, 2, 0, 1, 1);

    negYAxis = new QRadioButton(groupBox);
    negYAxis->setObjectName(QString::fromUtf8("negYAxis"));

    gridLayout1->addWidget(negYAxis, 1, 1, 1, 1);

    posYAxis = new QRadioButton(groupBox);
    posYAxis->setObjectName(QString::fromUtf8("posYAxis"));

    gridLayout1->addWidget(posYAxis, 1, 0, 1, 1);

    negZAxis = new QRadioButton(groupBox);
    negZAxis->setObjectName(QString::fromUtf8("negZAxis"));

    gridLayout1->addWidget(negZAxis, 2, 1, 1, 1);


    gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);


    vboxLayout1->addWidget(groupBox);

    vboxLayout2 = new QVBoxLayout();
#ifndef Q_OS_MAC
    vboxLayout2->setSpacing(6);
#endif
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    _distanceSlider = new QSlider(_outerFrame);
    _distanceSlider->setObjectName(QString::fromUtf8("_distanceSlider"));
    _distanceSlider->setMinimum(0);
    _distanceSlider->setMaximum(99);
    _distanceSlider->setSliderPosition(0);
    _distanceSlider->setOrientation(Qt::Horizontal);

    vboxLayout2->addWidget(_distanceSlider);

    _distanceSpinBox = new QDoubleSpinBox(_outerFrame);
    _distanceSpinBox->setObjectName(QString::fromUtf8("_distanceSpinBox"));
    _distanceSpinBox->setMinimumSize(QSize(100, 0));
    _distanceSpinBox->setMaximum(1e+10);
    _distanceSpinBox->setSingleStep(1);

    vboxLayout2->addWidget(_distanceSpinBox);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem1);


    vboxLayout1->addLayout(vboxLayout2);

    _advancedOptions = new QFrame(_outerFrame);
    _advancedOptions->setObjectName(QString::fromUtf8("_advancedOptions"));
    _advancedOptions->setFrameShape(QFrame::StyledPanel);
    _advancedOptions->setFrameShadow(QFrame::Raised);
    vboxLayout3 = new QVBoxLayout(_advancedOptions);
#ifndef Q_OS_MAC
    vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout3->setMargin(9);
#endif
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout1->setMargin(0);
#endif
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label = new QLabel(_advancedOptions);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout1->addWidget(label);

    _normalX = new QDoubleSpinBox(_advancedOptions);
    _normalX->setObjectName(QString::fromUtf8("_normalX"));
    _normalX->setMaximum(1);
    _normalX->setMinimum(-1);
    _normalX->setSingleStep(0.1);

    hboxLayout1->addWidget(_normalX);

    label_2 = new QLabel(_advancedOptions);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout1->addWidget(label_2);

    _normalY = new QDoubleSpinBox(_advancedOptions);
    _normalY->setObjectName(QString::fromUtf8("_normalY"));
    _normalY->setMaximum(1);
    _normalY->setMinimum(-1);
    _normalY->setSingleStep(0.1);

    hboxLayout1->addWidget(_normalY);

    label_3 = new QLabel(_advancedOptions);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout1->addWidget(label_3);

    _normalZ = new QDoubleSpinBox(_advancedOptions);
    _normalZ->setObjectName(QString::fromUtf8("_normalZ"));
    _normalZ->setMaximum(1);
    _normalZ->setMinimum(-1);
    _normalZ->setSingleStep(0.1);

    hboxLayout1->addWidget(_normalZ);


    vboxLayout3->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    _addButton = new QPushButton(_advancedOptions);
    _addButton->setObjectName(QString::fromUtf8("_addButton"));

    hboxLayout2->addWidget(_addButton);

    _removeButton = new QPushButton(_advancedOptions);
    _removeButton->setObjectName(QString::fromUtf8("_removeButton"));

    hboxLayout2->addWidget(_removeButton);


    vboxLayout3->addLayout(hboxLayout2);

    _clipPlaneList = new QListWidget(_advancedOptions);
    _clipPlaneList->setObjectName(QString::fromUtf8("_clipPlaneList"));

    vboxLayout3->addWidget(_clipPlaneList);


    vboxLayout1->addWidget(_advancedOptions);

    spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem2);


    vboxLayout->addWidget(_outerFrame);


    retranslateUi(ClipPlanes);

    QMetaObject::connectSlotsByName(ClipPlanes);
    } // setupUi

    void retranslateUi(QWidget *ClipPlanes)
    {
    ClipPlanes->setWindowTitle(QApplication::translate("ClipPlanes", "Form", 0, QApplication::UnicodeUTF8));
    clearButton->setText(QApplication::translate("ClipPlanes", "Clear", 0, QApplication::UnicodeUTF8));
    _advancedButton->setText(QApplication::translate("ClipPlanes", "Advanced", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("ClipPlanes", "Axis", 0, QApplication::UnicodeUTF8));
    posXAxis->setText(QApplication::translate("ClipPlanes", "X Axis", 0, QApplication::UnicodeUTF8));
    negXAxis->setText(QApplication::translate("ClipPlanes", "-X Axis", 0, QApplication::UnicodeUTF8));
    posZAxis->setText(QApplication::translate("ClipPlanes", "Z Axis", 0, QApplication::UnicodeUTF8));
    negYAxis->setText(QApplication::translate("ClipPlanes", "-Y Axis", 0, QApplication::UnicodeUTF8));
    posYAxis->setText(QApplication::translate("ClipPlanes", "Y Axis", 0, QApplication::UnicodeUTF8));
    negZAxis->setText(QApplication::translate("ClipPlanes", "-Z Axis", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ClipPlanes", "X:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ClipPlanes", "Y:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ClipPlanes", "Z:", 0, QApplication::UnicodeUTF8));
    _addButton->setText(QApplication::translate("ClipPlanes", "Add Clip Plane", 0, QApplication::UnicodeUTF8));
    _removeButton->setText(QApplication::translate("ClipPlanes", "Remove Clip Plane", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ClipPlanes);
    } // retranslateUi

};

namespace Ui {
    class ClipPlanes: public Ui_ClipPlanes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIPPLANES_H
