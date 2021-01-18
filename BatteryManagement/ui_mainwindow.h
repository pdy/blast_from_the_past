/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 19. Sep 22:19:43 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *localNameKey;
    QLabel *localNameVal;
    QLabel *localAdressKey;
    QLabel *localAdressVal;
    QLabel *roomKey;
    QLabel *roomVal;
    QLabel *battTypeKey;
    QLabel *battTypeVal;
    QLabel *cellNumberKey;
    QLabel *cellNumberVal;
    QLabel *messEndVoltKey;
    QLabel *messEndVoltVal;
    QLabel *installDataKey;
    QLabel *installDataVal;
    QLabel *messMadeCurrKey;
    QLabel *messMadeCurrVal;
    QLabel *roomTempKey;
    QLabel *roomTempVal;
    QLabel *extCellStateKey;
    QLabel *extCellStateVal;
    QLabel *commentsKey;
    QLabel *commentsVal;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(560, 460);
        MainWindow->setMinimumSize(QSize(559, 411));
        MainWindow->setMaximumSize(QSize(560, 1000));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 221, 371));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(230, 130, 301, 225));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setVerticalSpacing(8);
        formLayout->setContentsMargins(0, 0, 0, 0);
        localNameKey = new QLabel(formLayoutWidget);
        localNameKey->setObjectName(QString::fromUtf8("localNameKey"));

        formLayout->setWidget(0, QFormLayout::LabelRole, localNameKey);

        localNameVal = new QLabel(formLayoutWidget);
        localNameVal->setObjectName(QString::fromUtf8("localNameVal"));

        formLayout->setWidget(0, QFormLayout::FieldRole, localNameVal);

        localAdressKey = new QLabel(formLayoutWidget);
        localAdressKey->setObjectName(QString::fromUtf8("localAdressKey"));

        formLayout->setWidget(1, QFormLayout::LabelRole, localAdressKey);

        localAdressVal = new QLabel(formLayoutWidget);
        localAdressVal->setObjectName(QString::fromUtf8("localAdressVal"));

        formLayout->setWidget(1, QFormLayout::FieldRole, localAdressVal);

        roomKey = new QLabel(formLayoutWidget);
        roomKey->setObjectName(QString::fromUtf8("roomKey"));

        formLayout->setWidget(2, QFormLayout::LabelRole, roomKey);

        roomVal = new QLabel(formLayoutWidget);
        roomVal->setObjectName(QString::fromUtf8("roomVal"));

        formLayout->setWidget(2, QFormLayout::FieldRole, roomVal);

        battTypeKey = new QLabel(formLayoutWidget);
        battTypeKey->setObjectName(QString::fromUtf8("battTypeKey"));

        formLayout->setWidget(3, QFormLayout::LabelRole, battTypeKey);

        battTypeVal = new QLabel(formLayoutWidget);
        battTypeVal->setObjectName(QString::fromUtf8("battTypeVal"));

        formLayout->setWidget(3, QFormLayout::FieldRole, battTypeVal);

        cellNumberKey = new QLabel(formLayoutWidget);
        cellNumberKey->setObjectName(QString::fromUtf8("cellNumberKey"));

        formLayout->setWidget(4, QFormLayout::LabelRole, cellNumberKey);

        cellNumberVal = new QLabel(formLayoutWidget);
        cellNumberVal->setObjectName(QString::fromUtf8("cellNumberVal"));

        formLayout->setWidget(4, QFormLayout::FieldRole, cellNumberVal);

        messEndVoltKey = new QLabel(formLayoutWidget);
        messEndVoltKey->setObjectName(QString::fromUtf8("messEndVoltKey"));

        formLayout->setWidget(5, QFormLayout::LabelRole, messEndVoltKey);

        messEndVoltVal = new QLabel(formLayoutWidget);
        messEndVoltVal->setObjectName(QString::fromUtf8("messEndVoltVal"));

        formLayout->setWidget(5, QFormLayout::FieldRole, messEndVoltVal);

        installDataKey = new QLabel(formLayoutWidget);
        installDataKey->setObjectName(QString::fromUtf8("installDataKey"));

        formLayout->setWidget(6, QFormLayout::LabelRole, installDataKey);

        installDataVal = new QLabel(formLayoutWidget);
        installDataVal->setObjectName(QString::fromUtf8("installDataVal"));

        formLayout->setWidget(6, QFormLayout::FieldRole, installDataVal);

        messMadeCurrKey = new QLabel(formLayoutWidget);
        messMadeCurrKey->setObjectName(QString::fromUtf8("messMadeCurrKey"));

        formLayout->setWidget(7, QFormLayout::LabelRole, messMadeCurrKey);

        messMadeCurrVal = new QLabel(formLayoutWidget);
        messMadeCurrVal->setObjectName(QString::fromUtf8("messMadeCurrVal"));

        formLayout->setWidget(7, QFormLayout::FieldRole, messMadeCurrVal);

        roomTempKey = new QLabel(formLayoutWidget);
        roomTempKey->setObjectName(QString::fromUtf8("roomTempKey"));

        formLayout->setWidget(8, QFormLayout::LabelRole, roomTempKey);

        roomTempVal = new QLabel(formLayoutWidget);
        roomTempVal->setObjectName(QString::fromUtf8("roomTempVal"));

        formLayout->setWidget(8, QFormLayout::FieldRole, roomTempVal);

        extCellStateKey = new QLabel(formLayoutWidget);
        extCellStateKey->setObjectName(QString::fromUtf8("extCellStateKey"));

        formLayout->setWidget(9, QFormLayout::LabelRole, extCellStateKey);

        extCellStateVal = new QLabel(formLayoutWidget);
        extCellStateVal->setObjectName(QString::fromUtf8("extCellStateVal"));

        formLayout->setWidget(9, QFormLayout::FieldRole, extCellStateVal);

        commentsKey = new QLabel(formLayoutWidget);
        commentsKey->setObjectName(QString::fromUtf8("commentsKey"));

        formLayout->setWidget(10, QFormLayout::LabelRole, commentsKey);

        commentsVal = new QLabel(formLayoutWidget);
        commentsVal->setObjectName(QString::fromUtf8("commentsVal"));
        commentsVal->setTextFormat(Qt::AutoText);
        commentsVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(10, QFormLayout::FieldRole, commentsVal);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(230, 0, 301, 111));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 560, 20));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Mened\305\274er Obiekt\303\263w", 0, QApplication::UnicodeUTF8));
        localNameKey->setText(QApplication::translate("MainWindow", "Nazwa lokalizacji:", 0, QApplication::UnicodeUTF8));
        localNameVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        localAdressKey->setText(QApplication::translate("MainWindow", "Adres lokalizacji:", 0, QApplication::UnicodeUTF8));
        localAdressVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        roomKey->setText(QApplication::translate("MainWindow", "Pomieszczenie:", 0, QApplication::UnicodeUTF8));
        roomVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        battTypeKey->setText(QApplication::translate("MainWindow", "Typ baterii:", 0, QApplication::UnicodeUTF8));
        battTypeVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        cellNumberKey->setText(QApplication::translate("MainWindow", "Ilo\305\233\304\207 ogniw:", 0, QApplication::UnicodeUTF8));
        cellNumberVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        messEndVoltKey->setText(QApplication::translate("MainWindow", "Napi\304\231cie ko\305\204ca pomiaru:", 0, QApplication::UnicodeUTF8));
        messEndVoltVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        installDataKey->setText(QApplication::translate("MainWindow", "Data instalacji baterii:", 0, QApplication::UnicodeUTF8));
        installDataVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        messMadeCurrKey->setText(QApplication::translate("MainWindow", "Pomiar wykonano pr\304\205dem:", 0, QApplication::UnicodeUTF8));
        messMadeCurrVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        roomTempKey->setText(QApplication::translate("MainWindow", "Temperatura pomieszczenia:", 0, QApplication::UnicodeUTF8));
        roomTempVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        extCellStateKey->setText(QApplication::translate("MainWindow", "Zewn\304\231trzny stan ogniw:", 0, QApplication::UnicodeUTF8));
        extCellStateVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        commentsKey->setText(QApplication::translate("MainWindow", "Uwagi:", 0, QApplication::UnicodeUTF8));
        commentsVal->setText(QApplication::translate("MainWindow", "def", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Wykonane pomiary:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
