/********************************************************************************
** Form generated from reading UI file 'measure.ui'
**
** Created: Mon 19. Sep 22:19:43 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURE_H
#define UI_MEASURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_measureDialog
{
public:
    QGridLayout *gridLayout_2;
    QFormLayout *counterLayout;
    QGridLayout *tableLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *begMessButton;
    QPushButton *directMessButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *infButton;
    QPushButton *plotButton;
    QPushButton *messEndButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *measureDialog)
    {
        if (measureDialog->objectName().isEmpty())
            measureDialog->setObjectName(QString::fromUtf8("measureDialog"));
        measureDialog->resize(506, 408);
        gridLayout_2 = new QGridLayout(measureDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        counterLayout = new QFormLayout();
        counterLayout->setObjectName(QString::fromUtf8("counterLayout"));
        counterLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

        gridLayout_2->addLayout(counterLayout, 0, 0, 1, 1);

        tableLayout = new QGridLayout();
        tableLayout->setObjectName(QString::fromUtf8("tableLayout"));

        gridLayout_2->addLayout(tableLayout, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        begMessButton = new QPushButton(measureDialog);
        begMessButton->setObjectName(QString::fromUtf8("begMessButton"));

        horizontalLayout->addWidget(begMessButton);

        directMessButton = new QPushButton(measureDialog);
        directMessButton->setObjectName(QString::fromUtf8("directMessButton"));

        horizontalLayout->addWidget(directMessButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        infButton = new QPushButton(measureDialog);
        infButton->setObjectName(QString::fromUtf8("infButton"));

        horizontalLayout->addWidget(infButton);

        plotButton = new QPushButton(measureDialog);
        plotButton->setObjectName(QString::fromUtf8("plotButton"));

        horizontalLayout->addWidget(plotButton);

        messEndButton = new QPushButton(measureDialog);
        messEndButton->setObjectName(QString::fromUtf8("messEndButton"));

        horizontalLayout->addWidget(messEndButton);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(477, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        retranslateUi(measureDialog);

        QMetaObject::connectSlotsByName(measureDialog);
    } // setupUi

    void retranslateUi(QDialog *measureDialog)
    {
        measureDialog->setWindowTitle(QApplication::translate("measureDialog", "Pomiar", 0, QApplication::UnicodeUTF8));
        begMessButton->setText(QApplication::translate("measureDialog", "Pomiar wst\304\231pny", 0, QApplication::UnicodeUTF8));
        directMessButton->setText(QApplication::translate("measureDialog", "Pomiar w\305\202a\305\233ciwy", 0, QApplication::UnicodeUTF8));
        infButton->setText(QApplication::translate("measureDialog", "Informacje", 0, QApplication::UnicodeUTF8));
        plotButton->setText(QApplication::translate("measureDialog", "Wykres", 0, QApplication::UnicodeUTF8));
        messEndButton->setText(QApplication::translate("measureDialog", "Koniec", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class measureDialog: public Ui_measureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_H
