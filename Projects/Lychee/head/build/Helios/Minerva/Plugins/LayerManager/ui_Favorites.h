/********************************************************************************
** Form generated from reading ui file 'Favorites.ui'
**
** Created: Thu Apr 30 11:46:41 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FAVORITES_H
#define UI_FAVORITES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Favorites
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QTreeWidget *_favoritesTree;

    void setupUi(QWidget *Favorites)
    {
    if (Favorites->objectName().isEmpty())
        Favorites->setObjectName(QString::fromUtf8("Favorites"));
    Favorites->resize(435, 416);
    vboxLayout = new QVBoxLayout(Favorites);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));

    vboxLayout->addLayout(hboxLayout);

    _favoritesTree = new QTreeWidget(Favorites);
    _favoritesTree->setObjectName(QString::fromUtf8("_favoritesTree"));

    vboxLayout->addWidget(_favoritesTree);


    retranslateUi(Favorites);

    QMetaObject::connectSlotsByName(Favorites);
    } // setupUi

    void retranslateUi(QWidget *Favorites)
    {
    Favorites->setWindowTitle(QApplication::translate("Favorites", "Form", 0, QApplication::UnicodeUTF8));
    _favoritesTree->headerItem()->setText(0, QApplication::translate("Favorites", "1", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Favorites);
    } // retranslateUi

};

namespace Ui {
    class Favorites: public Ui_Favorites {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVORITES_H
