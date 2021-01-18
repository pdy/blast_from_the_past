#include "plotwidget.h"
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_renderer.h>

#include <qwt_plot_curve.h>
#include "ui_uiplotwidget.h"
#include <cmath>
#include <QDebug>
#include <QPen>
#include <QColor>
#include <QTextCodec>
#include <QPainter>
#include <time.h>
#include <cstdlib>

int RandomValue()
{
    static bool sw=false;
    if(!sw){
        srand((unsigned int)time(0));
        sw=true;
    }
    return (rand()%255);// + 10;
}
int Min(QVector<double> &vec)
{
    double min = vec.at(0);
    for(int i= 1;i<vec.size();i++)
    {
        if(vec.at(i)<min){
            min = vec.at(i);
        }

    }
    return (int)min;
}
int Max(QVector<double> &vec)
{
    double max = vec.at(0);
    for(int i= 1;i<vec.size();i++)
    {
        if(vec.at(i)>max){
            max = vec.at(i);
        }

    }
    return (int)ceil(max);
}
PlotWidget::PlotWidget(QWidget *parent) : QwtPlot(parent), ui(new Ui::PlotWidgetForm)
{
    ui->setupUi(this);
    curveInit = false;
    connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
        SLOT(showCurve(QwtPlotItem *, bool)));
    //SetupPlot();
    /*for(int i=0;i<9;i++)
    {
        curveKeys<<(QString(49+i))+"x";
        curveKeys<<(QString(49+i))+"y";
    }
    for(int i=0;i<10;i++)
    {
        curveKeys<<(QString("1")+QString(48+i))+"x";
        curveKeys<<(QString("1")+QString(48+i))+"y";
    }
    for(int i=0;i<10;i++)
    {
        curveKeys<<(QString("2")+QString(48+i))+"x";
        curveKeys<<(QString("2")+QString(48+i))+"y";
    }
    for(int i=0;i<10;i++)
    {
        curveKeys<<(QString("3")+QString(48+i))+"x";
        curveKeys<<(QString("3")+QString(48+i))+"y";
    }
    //qDebug()<<curveKeys;*/
}
//=====================================
PlotWidget::~PlotWidget()
{
    if(curveInit)
    {
        delete[] curve_;
        curveInit = false;
    }
    delete ui;
}
//======================================
void PlotWidget::Init(int curvesNum)
{
    if(curveInit)
    {
        //showCurve(&curve_[i],false);

        delete[] curve_;
        curveInit = false;
    }
    SetupPlot();
    int cnum;
    if(curvesNum<=0){
        cnum=1;
    }
    else{
        cnum=curvesNum;
    }
    curve_ = new QwtPlotCurve[cnum];
    //symb.setStyle(QwtSymbol::Cross);
    for(int i=0;i<cnum;i++)
    {       
        QPen pen;
        /*int x;
        if(i%2==0){
            x=255;
        }
        else{
            x=160;
        }*/
        QColor color(RandomValue(),RandomValue(),RandomValue(),255);
        pen.setColor(color);
        curve_[i].setPen(pen);
        curve_[i].setTitle(QString((i+1)+'0'));

        //curve_[i].setSymbol(new QwtSymbol(QwtSymbol::Cross));
        curve_[i].attach(this);
        yValsForCurve_[i]=QVector<double>();
        showCurve(&curve_[i],true);
    }
    curveInit = true;


}

//======================================
void PlotWidget::SetupPlot()
{
    //this->setTitle("Wykres");
    this->setCanvasBackground(QColor(Qt::white));

    this->setAutoReplot(false);
    this->setMargin(5);

    // legend
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::BottomLegend);

    // axis
    QTextCodec *codec = QTextCodec::codecForLocale();
    this->setAxisTitle(QwtPlot::xBottom, "Czas");
    this->setAxisTitle(QwtPlot::yLeft, codec->toUnicode("Wartoœæ"));

    yMax_ = 5;
    yMin_ = 0;
    this->setAxisScale(yLeft,yMin_,yMax_,1);


}
//======================================
void PlotWidget::AddMeasurePoint(int curveNume, double point)
{
    xVal.push_back(xVal.size());

    yValsForCurve_[curveNume-1].push_back(point);

    /*if(point>=yMax_){
        yMax_=point+1;  
    }
    if(point<=yMin_){
        yMin_=point-1;
    }*/
    int yMaxTemp = Max(yValsForCurve_[curveNume-1])+1;
    if(yMaxTemp>yMax_){
        yMax_ = yMaxTemp;
    }
    int yMinTemp = Min(yValsForCurve_[curveNume-1])-1;
    if(yMinTemp<yMin_){
        yMin_ = yMinTemp;
    }

    if(yMin_<0){
        yMin_=0;
    }
    this->setAxisScale(yLeft,yMin_,yMax_,1);
    curve_[curveNume-1].setSamples(xVal,yValsForCurve_[curveNume-1]);
    this->replot();
}
//======================================
void PlotWidget::showCurve(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") )
        ((QwtLegendItem *)w)->setChecked(on);

    replot();
}
//======================================
QImage *PlotWidget::GetPlot()
{

    const double scaleFactor = 5.0;
    const QSize sz(3543, 2362);
    //const QSize sz(200, 150);

    QImage *image = new QImage(sz, QImage::Format_ARGB32);
    image->fill( QColor( Qt::white ).rgb() );

    QPainter *painter = new QPainter(image);
    painter->scale(scaleFactor, scaleFactor);

    QwtPlotRenderer renderer;
    this->setCanvasBackground(QColor(Qt::black));
    renderer.render(this, painter, QRectF( QPointF(0, 0), sz / scaleFactor ) );
    this->setCanvasBackground(QColor(Qt::white));
    *image = image->scaled(600,400,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //image.save( "bode.png" );

    //QwtPlotRenderer renderer;
    //renderer.renderDocument(this,"plik.SVG","SVG",QSizeF(200,150),250);

    return image;
}
