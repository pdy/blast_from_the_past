#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <qwt_plot.h>
#include <QWidget>
#include <map>
#include <QPixmap>
#include <QVector>

namespace Ui{
    class PlotWidgetForm;
}

class QwtPlotCurve;

class PlotWidget : public QwtPlot
{
    Q_OBJECT
public:
    PlotWidget(QWidget *parent = 0);
    ~PlotWidget();
    void Init(int curvesNum);
    void AddMeasurePoint(int curveNume, double yPoint);
    QImage *GetPlot();
private slots:
    void showCurve(QwtPlotItem *, bool on);
private:
    Ui::PlotWidgetForm *ui;
    void SetupPlot();
    QwtPlotCurve *curve_;
    bool curveInit;

    QVector<double> xVal;
    QMap<int,QVector<double> >yValsForCurve_;
    int yMax_;
    int yMin_;
};

#endif // PLOTWIDGET_H
