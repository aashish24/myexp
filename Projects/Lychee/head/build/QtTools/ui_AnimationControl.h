/********************************************************************************
** Form generated from reading ui file 'AnimationControl.ui'
**
** Created: Thu Apr 30 11:45:11 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ANIMATIONCONTROL_H
#define UI_ANIMATIONCONTROL_H

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
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnimationControl
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *_outerFrame;
    QVBoxLayout *vboxLayout1;
    QSpacerItem *spacerItem;
    QSlider *_sliderSlider;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QCheckBox *_loopCheckBox;
    QSpacerItem *spacerItem1;
    QPushButton *_stepBackwardButton;
    QPushButton *_playBackwardButton;
    QPushButton *_stopButton;
    QPushButton *_playForwardButton;
    QPushButton *_stepForwardButton;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QDoubleSpinBox *_speedSpinBox;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *AnimationControl)
    {
    if (AnimationControl->objectName().isEmpty())
        AnimationControl->setObjectName(QString::fromUtf8("AnimationControl"));
    AnimationControl->resize(665, 323);
    vboxLayout = new QVBoxLayout(AnimationControl);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
    vboxLayout->setMargin(1);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _outerFrame = new QFrame(AnimationControl);
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

    _sliderSlider = new QSlider(_outerFrame);
    _sliderSlider->setObjectName(QString::fromUtf8("_sliderSlider"));
    _sliderSlider->setOrientation(Qt::Horizontal);

    vboxLayout1->addWidget(_sliderSlider);

    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout1->setMargin(0);
#endif
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    _loopCheckBox = new QCheckBox(_outerFrame);
    _loopCheckBox->setObjectName(QString::fromUtf8("_loopCheckBox"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_loopCheckBox->sizePolicy().hasHeightForWidth());
    _loopCheckBox->setSizePolicy(sizePolicy);
    _loopCheckBox->setMinimumSize(QSize(0, 32));

    hboxLayout1->addWidget(_loopCheckBox);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    _stepBackwardButton = new QPushButton(_outerFrame);
    _stepBackwardButton->setObjectName(QString::fromUtf8("_stepBackwardButton"));
    sizePolicy.setHeightForWidth(_stepBackwardButton->sizePolicy().hasHeightForWidth());
    _stepBackwardButton->setSizePolicy(sizePolicy);
    _stepBackwardButton->setMinimumSize(QSize(32, 32));
    _stepBackwardButton->setMaximumSize(QSize(32, 32));
    _stepBackwardButton->setBaseSize(QSize(32, 32));
    _stepBackwardButton->setIconSize(QSize(16, 16));
    _stepBackwardButton->setFlat(true);

    hboxLayout1->addWidget(_stepBackwardButton);

    _playBackwardButton = new QPushButton(_outerFrame);
    _playBackwardButton->setObjectName(QString::fromUtf8("_playBackwardButton"));
    sizePolicy.setHeightForWidth(_playBackwardButton->sizePolicy().hasHeightForWidth());
    _playBackwardButton->setSizePolicy(sizePolicy);
    _playBackwardButton->setMinimumSize(QSize(32, 32));
    _playBackwardButton->setMaximumSize(QSize(32, 32));
    _playBackwardButton->setFlat(true);

    hboxLayout1->addWidget(_playBackwardButton);

    _stopButton = new QPushButton(_outerFrame);
    _stopButton->setObjectName(QString::fromUtf8("_stopButton"));
    sizePolicy.setHeightForWidth(_stopButton->sizePolicy().hasHeightForWidth());
    _stopButton->setSizePolicy(sizePolicy);
    _stopButton->setMinimumSize(QSize(32, 32));
    _stopButton->setMaximumSize(QSize(32, 32));
    _stopButton->setFlat(true);

    hboxLayout1->addWidget(_stopButton);

    _playForwardButton = new QPushButton(_outerFrame);
    _playForwardButton->setObjectName(QString::fromUtf8("_playForwardButton"));
    sizePolicy.setHeightForWidth(_playForwardButton->sizePolicy().hasHeightForWidth());
    _playForwardButton->setSizePolicy(sizePolicy);
    _playForwardButton->setMinimumSize(QSize(32, 32));
    _playForwardButton->setMaximumSize(QSize(32, 32));
    _playForwardButton->setFlat(true);

    hboxLayout1->addWidget(_playForwardButton);

    _stepForwardButton = new QPushButton(_outerFrame);
    _stepForwardButton->setObjectName(QString::fromUtf8("_stepForwardButton"));
    sizePolicy.setHeightForWidth(_stepForwardButton->sizePolicy().hasHeightForWidth());
    _stepForwardButton->setSizePolicy(sizePolicy);
    _stepForwardButton->setMinimumSize(QSize(32, 32));
    _stepForwardButton->setMaximumSize(QSize(32, 32));
    _stepForwardButton->setIconSize(QSize(16, 16));
    _stepForwardButton->setFlat(true);

    hboxLayout1->addWidget(_stepForwardButton);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem2);


    hboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label = new QLabel(_outerFrame);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout2->addWidget(label);

    _speedSpinBox = new QDoubleSpinBox(_outerFrame);
    _speedSpinBox->setObjectName(QString::fromUtf8("_speedSpinBox"));
    _speedSpinBox->setDecimals(1);
    _speedSpinBox->setMaximum(100);
    _speedSpinBox->setMinimum(0.1);
    _speedSpinBox->setSingleStep(0.1);
    _speedSpinBox->setValue(1);

    hboxLayout2->addWidget(_speedSpinBox);


    hboxLayout->addLayout(hboxLayout2);


    vboxLayout1->addLayout(hboxLayout);

    spacerItem3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem3);


    vboxLayout->addWidget(_outerFrame);


    retranslateUi(AnimationControl);

    QMetaObject::connectSlotsByName(AnimationControl);
    } // setupUi

    void retranslateUi(QWidget *AnimationControl)
    {
    AnimationControl->setWindowTitle(QApplication::translate("AnimationControl", "Form", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    _loopCheckBox->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">If checked, the animation will loop continuously</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _loopCheckBox->setText(QApplication::translate("AnimationControl", "Loop", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    _stepBackwardButton->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Take one step backward</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _stepBackwardButton->setText(QString());

#ifndef QT_NO_TOOLTIP
    _playBackwardButton->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Play backward</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _playBackwardButton->setText(QString());

#ifndef QT_NO_TOOLTIP
    _stopButton->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Stop playing</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _stopButton->setText(QString());

#ifndef QT_NO_TOOLTIP
    _playForwardButton->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Play forward</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _playForwardButton->setText(QString());

#ifndef QT_NO_TOOLTIP
    _stepForwardButton->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Take one step forward</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _stepForwardButton->setText(QString());
    label->setText(QApplication::translate("AnimationControl", "Seconds / Step", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    _speedSpinBox->setToolTip(QApplication::translate("AnimationControl", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Set the number of seconds between animation steps</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    _speedSpinBox->setPrefix(QString());
    Q_UNUSED(AnimationControl);
    } // retranslateUi

};

namespace Ui {
    class AnimationControl: public Ui_AnimationControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONCONTROL_H
