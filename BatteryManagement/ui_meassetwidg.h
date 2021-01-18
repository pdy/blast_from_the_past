/********************************************************************************
** Form generated from reading UI file 'meassetwidg.ui'
**
** Created: Mon 19. Sep 22:19:44 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASSETWIDG_H
#define UI_MEASSETWIDG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasSetWidget
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout_3;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *measInterval;
    QLabel *label_3;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QSpinBox *cellMeasTime;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *applyButton;
    QPushButton *defaultButton;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MeasSetWidget)
    {
        if (MeasSetWidget->objectName().isEmpty())
            MeasSetWidget->setObjectName(QString::fromUtf8("MeasSetWidget"));
        MeasSetWidget->resize(271, 183);
        gridLayout = new QGridLayout(MeasSetWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(MeasSetWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        measInterval = new QSpinBox(MeasSetWidget);
        measInterval->setObjectName(QString::fromUtf8("measInterval"));
        measInterval->setMinimum(1);
        measInterval->setMaximum(60);

        formLayout->setWidget(0, QFormLayout::FieldRole, measInterval);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, formLayout);

        label_3 = new QLabel(MeasSetWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, label_3);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_2 = new QLabel(MeasSetWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        cellMeasTime = new QSpinBox(MeasSetWidget);
        cellMeasTime->setObjectName(QString::fromUtf8("cellMeasTime"));
        cellMeasTime->setMinimum(100);
        cellMeasTime->setMaximum(9000);
        cellMeasTime->setSingleStep(100);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cellMeasTime);


        formLayout_3->setLayout(1, QFormLayout::LabelRole, formLayout_2);

        label_4 = new QLabel(MeasSetWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, label_4);


        gridLayout->addLayout(formLayout_3, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        applyButton = new QPushButton(MeasSetWidget);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        horizontalLayout->addWidget(applyButton);

        defaultButton = new QPushButton(MeasSetWidget);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));

        horizontalLayout->addWidget(defaultButton);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(MeasSetWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setTextFormat(Qt::RichText);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(MeasSetWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setTextFormat(Qt::RichText);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(MeasSetWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setTextFormat(Qt::RichText);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_7);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(MeasSetWidget);

        QMetaObject::connectSlotsByName(MeasSetWidget);
    } // setupUi

    void retranslateUi(QWidget *MeasSetWidget)
    {
        MeasSetWidget->setWindowTitle(QApplication::translate("MeasSetWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MeasSetWidget", "Odst\304\231p pomi\304\231dzy pomiarami:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MeasSetWidget", "minut", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MeasSetWidget", "Czas pomiaru dla jednego ogniwa:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MeasSetWidget", "msek.", 0, QApplication::UnicodeUTF8));
        applyButton->setText(QApplication::translate("MeasSetWidget", "Ustaw", 0, QApplication::UnicodeUTF8));
        defaultButton->setText(QApplication::translate("MeasSetWidget", "Domy\305\233lne", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MeasSetWidget", "Maksymalny czas pomiaru dla jednego ogniwa", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MeasSetWidget", "jest dynamicznie ustawiany na podstawie", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MeasSetWidget", "ustawionego odst\304\231pu pomi\304\231dzy pomiarami.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeasSetWidget: public Ui_MeasSetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASSETWIDG_H
