/********************************************************************************
** Form generated from reading UI file 'reportdata.ui'
**
** Created: Mon 19. Sep 22:19:44 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDATA_H
#define UI_REPORTDATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RepData
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QListWidget *measMadeBy;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *addPersonButton;
    QPushButton *deletePersonButton;
    QPushButton *editPersonButton;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *measEquipList;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *addEquipButton;
    QPushButton *deleteEquipButton;
    QPushButton *editEquipButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QLabel *pictureLabel;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *changePicButton;
    QPushButton *setDefaultPicButton;

    void setupUi(QWidget *RepData)
    {
        if (RepData->objectName().isEmpty())
            RepData->setObjectName(QString::fromUtf8("RepData"));
        RepData->resize(284, 295);
        RepData->setMaximumSize(QSize(284, 295));
        gridLayout = new QGridLayout(RepData);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(RepData);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        measMadeBy = new QListWidget(tab);
        measMadeBy->setObjectName(QString::fromUtf8("measMadeBy"));

        horizontalLayout->addWidget(measMadeBy);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addPersonButton = new QPushButton(tab);
        addPersonButton->setObjectName(QString::fromUtf8("addPersonButton"));

        verticalLayout->addWidget(addPersonButton);

        deletePersonButton = new QPushButton(tab);
        deletePersonButton->setObjectName(QString::fromUtf8("deletePersonButton"));

        verticalLayout->addWidget(deletePersonButton);

        editPersonButton = new QPushButton(tab);
        editPersonButton->setObjectName(QString::fromUtf8("editPersonButton"));

        verticalLayout->addWidget(editPersonButton);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        measEquipList = new QListWidget(tab_2);
        measEquipList->setObjectName(QString::fromUtf8("measEquipList"));

        horizontalLayout_2->addWidget(measEquipList);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        addEquipButton = new QPushButton(tab_2);
        addEquipButton->setObjectName(QString::fromUtf8("addEquipButton"));

        verticalLayout_4->addWidget(addEquipButton);

        deleteEquipButton = new QPushButton(tab_2);
        deleteEquipButton->setObjectName(QString::fromUtf8("deleteEquipButton"));

        verticalLayout_4->addWidget(deleteEquipButton);

        editEquipButton = new QPushButton(tab_2);
        editEquipButton->setObjectName(QString::fromUtf8("editEquipButton"));

        verticalLayout_4->addWidget(editEquipButton);


        verticalLayout_3->addLayout(verticalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pictureLabel = new QLabel(tab_3);
        pictureLabel->setObjectName(QString::fromUtf8("pictureLabel"));
        pictureLabel->setMinimumSize(QSize(250, 150));
        pictureLabel->setMaximumSize(QSize(250, 150));

        gridLayout_2->addWidget(pictureLabel, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        changePicButton = new QPushButton(tab_3);
        changePicButton->setObjectName(QString::fromUtf8("changePicButton"));

        horizontalLayout_3->addWidget(changePicButton);

        setDefaultPicButton = new QPushButton(tab_3);
        setDefaultPicButton->setObjectName(QString::fromUtf8("setDefaultPicButton"));

        horizontalLayout_3->addWidget(setDefaultPicButton);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(RepData);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(RepData);
    } // setupUi

    void retranslateUi(QWidget *RepData)
    {
        RepData->setWindowTitle(QApplication::translate("RepData", "Form", 0, QApplication::UnicodeUTF8));
        addPersonButton->setText(QApplication::translate("RepData", "Dodaj", 0, QApplication::UnicodeUTF8));
        deletePersonButton->setText(QApplication::translate("RepData", "Usu\305\204", 0, QApplication::UnicodeUTF8));
        editPersonButton->setText(QApplication::translate("RepData", "Edytuj", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RepData", "Lista os\303\263b", 0, QApplication::UnicodeUTF8));
        addEquipButton->setText(QApplication::translate("RepData", "Dodaj", 0, QApplication::UnicodeUTF8));
        deleteEquipButton->setText(QApplication::translate("RepData", "Usu\305\204", 0, QApplication::UnicodeUTF8));
        editEquipButton->setText(QApplication::translate("RepData", "Edytuj", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RepData", "Sprz\304\231t pomiarowy", 0, QApplication::UnicodeUTF8));
        pictureLabel->setText(QApplication::translate("RepData", "...", 0, QApplication::UnicodeUTF8));
        changePicButton->setText(QApplication::translate("RepData", "Zmie\305\204", 0, QApplication::UnicodeUTF8));
        setDefaultPicButton->setText(QApplication::translate("RepData", "Domy\305\233lna", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("RepData", "Grafika", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RepData: public Ui_RepData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDATA_H
