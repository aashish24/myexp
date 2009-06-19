/********************************************************************************
** Form generated from reading ui file 'AddGeometryWidget.ui'
**
** Created: Thu Apr 30 11:46:40 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDGEOMETRYWIDGET_H
#define UI_ADDGEOMETRYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QtTools/ColorButton.h"

QT_BEGIN_NAMESPACE

class Ui_AddGeometryWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QRadioButton *_sphereRadioButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *_radiusDoubleSpinBox;
    QRadioButton *_torusRadioButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QDoubleSpinBox *_innerRadiusDoubleSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QDoubleSpinBox *_outerRadiusDoubleSpinBox;
    QRadioButton *_boxRadioButton;
    QRadioButton *_squareRadioButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QDoubleSpinBox *_boxWidth;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QDoubleSpinBox *_boxHeight;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QDoubleSpinBox *_boxDepth;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_12;
    QDoubleSpinBox *_squareWidth;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QDoubleSpinBox *_squareHeight;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *_latDoubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *_longDoubleSpinBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *_name;
    QLabel *label_5;
    QtTools::ColorButton *_colorButton;
    QLabel *label_6;
    QSlider *_transparencySlider;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AddGeometryWidget)
    {
    if (AddGeometryWidget->objectName().isEmpty())
        AddGeometryWidget->setObjectName(QString::fromUtf8("AddGeometryWidget"));
    AddGeometryWidget->resize(546, 442);
    verticalLayout_2 = new QVBoxLayout(AddGeometryWidget);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    groupBox = new QGroupBox(AddGeometryWidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    verticalLayout = new QVBoxLayout(groupBox);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    _sphereRadioButton = new QRadioButton(groupBox);
    _sphereRadioButton->setObjectName(QString::fromUtf8("_sphereRadioButton"));

    gridLayout->addWidget(_sphereRadioButton, 0, 0, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);

    _radiusDoubleSpinBox = new QDoubleSpinBox(groupBox);
    _radiusDoubleSpinBox->setObjectName(QString::fromUtf8("_radiusDoubleSpinBox"));

    horizontalLayout->addWidget(_radiusDoubleSpinBox);


    gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

    _torusRadioButton = new QRadioButton(groupBox);
    _torusRadioButton->setObjectName(QString::fromUtf8("_torusRadioButton"));

    gridLayout->addWidget(_torusRadioButton, 1, 0, 1, 1);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_7 = new QLabel(groupBox);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    horizontalLayout_5->addWidget(label_7);

    _innerRadiusDoubleSpinBox = new QDoubleSpinBox(groupBox);
    _innerRadiusDoubleSpinBox->setObjectName(QString::fromUtf8("_innerRadiusDoubleSpinBox"));

    horizontalLayout_5->addWidget(_innerRadiusDoubleSpinBox);


    gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    label_8 = new QLabel(groupBox);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    horizontalLayout_6->addWidget(label_8);

    _outerRadiusDoubleSpinBox = new QDoubleSpinBox(groupBox);
    _outerRadiusDoubleSpinBox->setObjectName(QString::fromUtf8("_outerRadiusDoubleSpinBox"));

    horizontalLayout_6->addWidget(_outerRadiusDoubleSpinBox);


    gridLayout->addLayout(horizontalLayout_6, 1, 2, 1, 1);

    _boxRadioButton = new QRadioButton(groupBox);
    _boxRadioButton->setObjectName(QString::fromUtf8("_boxRadioButton"));

    gridLayout->addWidget(_boxRadioButton, 2, 0, 1, 1);

    _squareRadioButton = new QRadioButton(groupBox);
    _squareRadioButton->setObjectName(QString::fromUtf8("_squareRadioButton"));

    gridLayout->addWidget(_squareRadioButton, 3, 0, 1, 1);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    label_9 = new QLabel(groupBox);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    horizontalLayout_7->addWidget(label_9);

    _boxWidth = new QDoubleSpinBox(groupBox);
    _boxWidth->setObjectName(QString::fromUtf8("_boxWidth"));

    horizontalLayout_7->addWidget(_boxWidth);


    gridLayout->addLayout(horizontalLayout_7, 2, 1, 1, 1);

    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    label_10 = new QLabel(groupBox);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    horizontalLayout_8->addWidget(label_10);

    _boxHeight = new QDoubleSpinBox(groupBox);
    _boxHeight->setObjectName(QString::fromUtf8("_boxHeight"));

    horizontalLayout_8->addWidget(_boxHeight);


    gridLayout->addLayout(horizontalLayout_8, 2, 2, 1, 1);

    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    label_11 = new QLabel(groupBox);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    horizontalLayout_9->addWidget(label_11);

    _boxDepth = new QDoubleSpinBox(groupBox);
    _boxDepth->setObjectName(QString::fromUtf8("_boxDepth"));

    horizontalLayout_9->addWidget(_boxDepth);


    gridLayout->addLayout(horizontalLayout_9, 2, 3, 1, 1);

    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
    label_12 = new QLabel(groupBox);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    horizontalLayout_10->addWidget(label_12);

    _squareWidth = new QDoubleSpinBox(groupBox);
    _squareWidth->setObjectName(QString::fromUtf8("_squareWidth"));

    horizontalLayout_10->addWidget(_squareWidth);


    gridLayout->addLayout(horizontalLayout_10, 3, 1, 1, 1);

    horizontalLayout_11 = new QHBoxLayout();
    horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
    label_13 = new QLabel(groupBox);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    horizontalLayout_11->addWidget(label_13);

    _squareHeight = new QDoubleSpinBox(groupBox);
    _squareHeight->setObjectName(QString::fromUtf8("_squareHeight"));

    horizontalLayout_11->addWidget(_squareHeight);


    gridLayout->addLayout(horizontalLayout_11, 3, 2, 1, 1);


    verticalLayout->addLayout(gridLayout);


    verticalLayout_2->addWidget(groupBox);

    groupBox_2 = new QGroupBox(AddGeometryWidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    horizontalLayout_2 = new QHBoxLayout(groupBox_2);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    _latDoubleSpinBox = new QDoubleSpinBox(groupBox_2);
    _latDoubleSpinBox->setObjectName(QString::fromUtf8("_latDoubleSpinBox"));
    _latDoubleSpinBox->setMinimum(-90);
    _latDoubleSpinBox->setMaximum(90);

    horizontalLayout_2->addWidget(_latDoubleSpinBox);

    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_2->addWidget(label_3);

    _longDoubleSpinBox = new QDoubleSpinBox(groupBox_2);
    _longDoubleSpinBox->setObjectName(QString::fromUtf8("_longDoubleSpinBox"));
    _longDoubleSpinBox->setMinimum(-180);
    _longDoubleSpinBox->setMaximum(180);

    horizontalLayout_2->addWidget(_longDoubleSpinBox);


    verticalLayout_2->addWidget(groupBox_2);

    groupBox_3 = new QGroupBox(AddGeometryWidget);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    verticalLayout_3 = new QVBoxLayout(groupBox_3);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    gridLayout_2 = new QGridLayout();
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    label_4 = new QLabel(groupBox_3);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

    _name = new QLineEdit(groupBox_3);
    _name->setObjectName(QString::fromUtf8("_name"));

    gridLayout_2->addWidget(_name, 0, 1, 1, 3);

    label_5 = new QLabel(groupBox_3);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

    _colorButton = new QtTools::ColorButton(groupBox_3);
    _colorButton->setObjectName(QString::fromUtf8("_colorButton"));

    gridLayout_2->addWidget(_colorButton, 1, 1, 1, 1);

    label_6 = new QLabel(groupBox_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout_2->addWidget(label_6, 1, 2, 1, 1);

    _transparencySlider = new QSlider(groupBox_3);
    _transparencySlider->setObjectName(QString::fromUtf8("_transparencySlider"));
    _transparencySlider->setMaximum(255);
    _transparencySlider->setValue(255);
    _transparencySlider->setOrientation(Qt::Horizontal);

    gridLayout_2->addWidget(_transparencySlider, 1, 3, 1, 1);


    verticalLayout_3->addLayout(gridLayout_2);

    groupBox->raise();

    verticalLayout_2->addWidget(groupBox_3);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);


    retranslateUi(AddGeometryWidget);

    QMetaObject::connectSlotsByName(AddGeometryWidget);
    } // setupUi

    void retranslateUi(QWidget *AddGeometryWidget)
    {
    AddGeometryWidget->setWindowTitle(QApplication::translate("AddGeometryWidget", "Form", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("AddGeometryWidget", "Primitive", 0, QApplication::UnicodeUTF8));
    _sphereRadioButton->setText(QApplication::translate("AddGeometryWidget", "Sphere", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("AddGeometryWidget", "Radius", 0, QApplication::UnicodeUTF8));
    _torusRadioButton->setText(QApplication::translate("AddGeometryWidget", "Torus", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("AddGeometryWidget", "Inner Radius", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("AddGeometryWidget", "Outer Radius", 0, QApplication::UnicodeUTF8));
    _boxRadioButton->setText(QApplication::translate("AddGeometryWidget", "Box", 0, QApplication::UnicodeUTF8));
    _squareRadioButton->setText(QApplication::translate("AddGeometryWidget", "Square", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("AddGeometryWidget", "Width", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("AddGeometryWidget", "Height", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("AddGeometryWidget", "Depth", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("AddGeometryWidget", "Width", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("AddGeometryWidget", "Height", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("AddGeometryWidget", "Location", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("AddGeometryWidget", "Lat:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AddGeometryWidget", "Long:", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QApplication::translate("AddGeometryWidget", "Properties", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("AddGeometryWidget", "Name:", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("AddGeometryWidget", "Color:", 0, QApplication::UnicodeUTF8));
    _colorButton->setText(QApplication::translate("AddGeometryWidget", "PushButton", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("AddGeometryWidget", "Transparency:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AddGeometryWidget);
    } // retranslateUi

};

namespace Ui {
    class AddGeometryWidget: public Ui_AddGeometryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGEOMETRYWIDGET_H
