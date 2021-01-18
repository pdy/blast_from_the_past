#ifndef MEASURE_H
#define MEASURE_H

#include <QDialog>
#include <QThread>

class MeasTable;
class LcdCounter;
class QTextCodec;
class QCloseEvent;
class QTime;
class QTextDocument;
class DeviceRequest;
class BattInfo;
class MeasThread;
class BatteryLabel;
class PlotWidget;


namespace Ui {
    class measureDialog;
}

class Measure : public QDialog
{
    Q_OBJECT
public:
    Measure(QWidget *parent = 0);
    ~Measure();

    void TakeBattery(BattInfo &battery);
    BattInfo *ReturnBattery(){return batt;}
    QString ReturnTableName(){return tableName_;}
    QString ReturnPlotName(){return plotName_;}

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private slots:
    void InsertFirstMeasResults(QString data,int row);
    void InsertDirectMeasResults(QString data,int row);

    void FirstMeasure();
    void DirectMeasure();
    void StopMeasure();

    void DisplayBattInformation();
signals:
    void StopMeasureSignal();
    void NextMeasLoop();

    void MeasureFinished();
    void CloseWindow();

private:
    bool bySignal;
    bool firstMeasure;
    bool directMeasure;
    bool firstMeasStoped;
    bool duringMeasure;
    bool stoped;
    bool alert;
    bool measBreak;
    bool gaugeDisconnected;

    void SetFlagsAndButtons();
    void LoadSettings();
    QString CurrentTime();
    QString GenerateBattDateField();
    bool WriteTable(QTextDocument *doc);
    void WriteImage(QImage *image);
    QString ConvertToString(long value);
    int minutes;

    BattInfo *batt;
    BatteryLabel *battLabel;
    Ui::measureDialog *ui;
    MeasTable *table;
    PlotWidget *plot;
    LcdCounter *counter;
    QTextCodec *codec;
    QTime *qtTime;

    QString tableName_;
    QString plotName_;

    MeasThread *measThread;
};


//===============================================
//                  MeasThread
//===============================================

class MeasThread : public QThread
{
    Q_OBJECT
public:
    MeasThread();
    ~MeasThread();

    void SetCellsNumber(int num){iteration=num;}
    void SetAlertValue(QString value);
    //void SetAlertValue(int value){alertValue=QString(value);}
    void SetDelay(int val){delay=val;}
    bool ConfirmDeviceConnection();
public slots:
    void BreakMeasure(){breakMeasure=1;}
signals:
    void DataHasCome(QString data,int row);
protected:
    void run();
private slots:
    void DeviceCleanUp();
private:
    DeviceRequest *device;
    bool breakMeasure;
    QString alertValue;
    int iteration;
    int delay;

};

#endif // MEASURE_H
