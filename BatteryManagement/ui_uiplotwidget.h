/********************************************************************************
** Form generated from reading UI file 'uiplotwidget.ui'
**
** Created: Mon 19. Sep 22:19:44 2011
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIPLOTWIDGET_H
#define UI_UIPLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotWidgetForm
{
public:

    void setupUi(QWidget *PlotWidgetForm)
    {
        if (PlotWidgetForm->objectName().isEmpty())
            PlotWidgetForm->setObjectName(QString::fromUtf8("PlotWidgetForm"));
        PlotWidgetForm->resize(669, 389);

        retranslateUi(PlotWidgetForm);

        QMetaObject::connectSlotsByName(PlotWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *PlotWidgetForm)
    {
        PlotWidgetForm->setWindowTitle(QApplication::translate("PlotWidgetForm", "Wykres", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotWidgetForm: public Ui_PlotWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIPLOTWIDGET_H
