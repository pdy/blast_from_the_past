/********************************************************************************
** Form generated from reading UI file 'battlabel.ui'
**
** Created: Mon 19. Sep 22:19:43 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLABEL_H
#define UI_BATTLABEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_BattLabel
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineLocalName;
    QLabel *label_3;
    QLineEdit *lineLokalAdress;
    QLabel *label_4;
    QLineEdit *lineRoom;
    QLabel *label_5;
    QLineEdit *lineBattType;
    QLabel *label_8;
    QSpinBox *cellNumber;
    QLabel *label_14;
    QLineEdit *mensEndVolt;
    QLabel *label_15;
    QLabel *label_6;
    QLineEdit *battInstDate;
    QLabel *label_7;
    QLineEdit *mensDoneCurr;
    QLabel *label_9;
    QLineEdit *hourIntens;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *roomTemp;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *extCellState;
    QLabel *label_16;
    QTextEdit *heeds;
    QPushButton *backwardButton;
    QPushButton *forwardButton;
    QLabel *label_17;

    void setupUi(QDialog *BattLabel)
    {
        if (BattLabel->objectName().isEmpty())
            BattLabel->setObjectName(QString::fromUtf8("BattLabel"));
        BattLabel->resize(505, 410);
        gridLayout = new QGridLayout(BattLabel);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(BattLabel);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 6);

        label_2 = new QLabel(BattLabel);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineLocalName = new QLineEdit(BattLabel);
        lineLocalName->setObjectName(QString::fromUtf8("lineLocalName"));
        lineLocalName->setMaxLength(25);

        gridLayout->addWidget(lineLocalName, 1, 2, 1, 6);

        label_3 = new QLabel(BattLabel);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineLokalAdress = new QLineEdit(BattLabel);
        lineLokalAdress->setObjectName(QString::fromUtf8("lineLokalAdress"));
        lineLokalAdress->setMaxLength(40);

        gridLayout->addWidget(lineLokalAdress, 2, 2, 1, 6);

        label_4 = new QLabel(BattLabel);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineRoom = new QLineEdit(BattLabel);
        lineRoom->setObjectName(QString::fromUtf8("lineRoom"));
        lineRoom->setMaxLength(25);

        gridLayout->addWidget(lineRoom, 3, 2, 1, 6);

        label_5 = new QLabel(BattLabel);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineBattType = new QLineEdit(BattLabel);
        lineBattType->setObjectName(QString::fromUtf8("lineBattType"));
        lineBattType->setMaxLength(25);

        gridLayout->addWidget(lineBattType, 4, 2, 1, 6);

        label_8 = new QLabel(BattLabel);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        cellNumber = new QSpinBox(BattLabel);
        cellNumber->setObjectName(QString::fromUtf8("cellNumber"));
        cellNumber->setMinimum(1);
        cellNumber->setMaximum(39);

        gridLayout->addWidget(cellNumber, 5, 2, 1, 1);

        label_14 = new QLabel(BattLabel);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 6, 0, 1, 2);

        mensEndVolt = new QLineEdit(BattLabel);
        mensEndVolt->setObjectName(QString::fromUtf8("mensEndVolt"));
        mensEndVolt->setMaxLength(5);

        gridLayout->addWidget(mensEndVolt, 6, 2, 1, 3);

        label_15 = new QLabel(BattLabel);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 6, 5, 1, 1);

        label_6 = new QLabel(BattLabel);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        battInstDate = new QLineEdit(BattLabel);
        battInstDate->setObjectName(QString::fromUtf8("battInstDate"));
        battInstDate->setMaxLength(25);

        gridLayout->addWidget(battInstDate, 7, 2, 1, 3);

        label_7 = new QLabel(BattLabel);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 8, 0, 1, 2);

        mensDoneCurr = new QLineEdit(BattLabel);
        mensDoneCurr->setObjectName(QString::fromUtf8("mensDoneCurr"));
        mensDoneCurr->setMaxLength(5);

        gridLayout->addWidget(mensDoneCurr, 8, 2, 1, 1);

        label_9 = new QLabel(BattLabel);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 3, 1, 3);

        hourIntens = new QLineEdit(BattLabel);
        hourIntens->setObjectName(QString::fromUtf8("hourIntens"));

        gridLayout->addWidget(hourIntens, 8, 6, 1, 1);

        label_10 = new QLabel(BattLabel);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 8, 7, 1, 1);

        label_11 = new QLabel(BattLabel);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 9, 0, 1, 2);

        roomTemp = new QLineEdit(BattLabel);
        roomTemp->setObjectName(QString::fromUtf8("roomTemp"));

        gridLayout->addWidget(roomTemp, 9, 2, 1, 2);

        label_12 = new QLabel(BattLabel);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 9, 4, 1, 1);

        label_13 = new QLabel(BattLabel);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 10, 0, 1, 2);

        extCellState = new QLineEdit(BattLabel);
        extCellState->setObjectName(QString::fromUtf8("extCellState"));
        extCellState->setMaxLength(30);

        gridLayout->addWidget(extCellState, 10, 2, 1, 6);

        label_16 = new QLabel(BattLabel);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 11, 0, 1, 1);

        heeds = new QTextEdit(BattLabel);
        heeds->setObjectName(QString::fromUtf8("heeds"));
        heeds->setMaximumSize(QSize(16777215, 90));

        gridLayout->addWidget(heeds, 11, 2, 1, 6);

        backwardButton = new QPushButton(BattLabel);
        backwardButton->setObjectName(QString::fromUtf8("backwardButton"));
        backwardButton->setMinimumSize(QSize(120, 25));
        backwardButton->setMaximumSize(QSize(135, 16777215));

        gridLayout->addWidget(backwardButton, 12, 0, 1, 1);

        forwardButton = new QPushButton(BattLabel);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setMinimumSize(QSize(120, 25));
        forwardButton->setMaximumSize(QSize(135, 16777215));

        gridLayout->addWidget(forwardButton, 12, 6, 1, 2);

        label_17 = new QLabel(BattLabel);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 7, 5, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(lineLocalName);
        label_3->setBuddy(lineLokalAdress);
        label_4->setBuddy(lineRoom);
        label_5->setBuddy(lineBattType);
        label_8->setBuddy(cellNumber);
        label_14->setBuddy(mensEndVolt);
        label_15->setBuddy(mensEndVolt);
        label_6->setBuddy(battInstDate);
        label_7->setBuddy(mensDoneCurr);
        label_9->setBuddy(hourIntens);
        label_10->setBuddy(hourIntens);
        label_11->setBuddy(roomTemp);
        label_12->setBuddy(roomTemp);
        label_13->setBuddy(extCellState);
#endif // QT_NO_SHORTCUT

        retranslateUi(BattLabel);

        QMetaObject::connectSlotsByName(BattLabel);
    } // setupUi

    void retranslateUi(QDialog *BattLabel)
    {
        BattLabel->setWindowTitle(QApplication::translate("BattLabel", "Etykieta baterii", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BattLabel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:600; color:#55aaff;\">Informacje o obiekcie</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BattLabel", "Nazwa lokalizacji:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BattLabel", "Adres lokalizacji:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BattLabel", "Pomieszczenie:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BattLabel", "Typ baterii:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("BattLabel", "Ilo\305\233\304\207 ogniw:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("BattLabel", "Napi\304\231cie ko\305\204ca pomiaru:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("BattLabel", "V/ogniwo", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("BattLabel", "Data instalacji baterii:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("BattLabel", "Pomiar wykonanno pr\304\205dem: ", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("BattLabel", "godzinnym o nat\304\231\305\274eniu:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("BattLabel", "A", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("BattLabel", "Temperatura pomieszczenia:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("BattLabel", "st. C.", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("BattLabel", "Zewn\304\231trzny stan ogniw:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("BattLabel", "Uwagi:", 0, QApplication::UnicodeUTF8));
        backwardButton->setText(QApplication::translate("BattLabel", "Wstecz", 0, QApplication::UnicodeUTF8));
        forwardButton->setText(QApplication::translate("BattLabel", "Dalej", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("BattLabel", "(rrrr-mm-dd)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BattLabel: public Ui_BattLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLABEL_H
