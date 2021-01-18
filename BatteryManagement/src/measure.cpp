#include "measure.h"
#include "ui_measure.h"
#include "meastable.h"
#include "lcdcounter.h"
#include "devicerequest.h"
#include "dbhandler.h"
#include "batterylabel.h"
#include "plotwidget.h"

#include <QTextCodec>
#include <QTextDocument>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QSound>

#include <sstream>
#include <ctime>

Measure::Measure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measureDialog)
{
    ui->setupUi(this);

    table=new MeasTable;
    ui->tableLayout->addWidget(table);
    codec = QTextCodec::codecForLocale();
    counter = new LcdCounter;
    ui->counterLayout->insertRow(0,codec->toUnicode("Do nastêpnego pomiaru pozosta³o: "),counter);

    measThread = new MeasThread;
    batt=new BattInfo;
    battLabel=new BatteryLabel;
    plot = new PlotWidget;

    SetFlagsAndButtons();

    connect(ui->begMessButton,SIGNAL(clicked()),this,SLOT(FirstMeasure()));
    connect(ui->messEndButton,SIGNAL(clicked()),this,SLOT(StopMeasure())); 
    connect(this,SIGNAL(StopMeasureSignal()),measThread,SLOT(BreakMeasure()));
    connect(ui->directMessButton,SIGNAL(clicked()),this,SLOT(DirectMeasure()));  
    connect(ui->infButton,SIGNAL(clicked()),this,SLOT(DisplayBattInformation()));
    connect(ui->plotButton,SIGNAL(clicked()),plot,SLOT(show()));
  //  connect(counter,SIGNAL(Timeout()),this,SLOT(DirectMeasure()));
}
//=========================================
Measure::~Measure()
{

    delete measThread;
    delete table;
    delete plot;
    delete counter;
    delete battLabel;
    delete ui;
}
//=========================================
void Measure::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
//==========================================
void Measure::closeEvent(QCloseEvent *e)
{
    if(duringMeasure){
        e->ignore();
    }
    else
    {
        e->accept();
        table->Clear();
        emit CloseWindow();
    }
}
//=========================================
void Measure::SetFlagsAndButtons()
{
    bySignal=0;
    firstMeasure=0;
    directMeasure=0;
    firstMeasStoped=0;
    duringMeasure=0;
    stoped=0;
    alert=0;
    measBreak=0;
    gaugeDisconnected=0;

    ui->directMessButton->setDisabled(true);
    ui->messEndButton->setDisabled(true);
    ui->messEndButton->setText("Przerwij");
    ui->plotButton->setDisabled(true);

    ui->begMessButton->setEnabled(true);
    ui->infButton->setEnabled(true);

    table->Clear();

}
//=========================================
void Measure::LoadSettings()
{
    QFile file("cfg/times");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        QString value;
        value = in.readAll();
        int index=value.indexOf(QChar('\n'));
        QString interval,delay;
        int i=0;
        while(i!=index)
        {
            interval.push_back(value.at(i));
            ++i;
        }
        ++i;
        while(i<value.size())
        {
            delay.push_back(value.at(i));
            ++i;
        }
        measThread->SetDelay(delay.toInt());
        minutes=interval.toInt();
        file.close();

    }
}

//==========================================
void Measure::TakeBattery(BattInfo &battery)
{
    SetFlagsAndButtons();
    LoadSettings();
    batt->battName=battery.battName;
    batt->battType=battery.battType;
    batt->cellsNumber=battery.cellsNumber;
    if(battery.comments == ""){
        batt->comments="brak uwag";
    }
    else{
        batt->comments=battery.comments;
    }
    batt->extCellsState=battery.extCellsState;
    batt->installDate=battery.installDate;
    batt->messEndVolt=battery.messEndVolt;
    batt->messMadeCurr=battery.messMadeCurr;
    batt->objectAdress=battery.objectAdress;
    batt->objectName=battery.objectName;
    batt->room=battery.room;
    batt->roomTemperature=battery.roomTemperature;

    measThread->SetCellsNumber(batt->cellsNumber.toInt());
    table->setRowCount(batt->cellsNumber.toInt());
    table->setColumnCount(1);
    //plot->Init(batt->cellsNumber.toInt());

}

//==========================================
void Measure::FirstMeasure()
{
   // DeviceRequest device;
    SetFlagsAndButtons();
    plot->Init(table->rowCount());
    if(!measThread->ConfirmDeviceConnection())
    {
        QMessageBox::warning(this,codec->toUnicode("Urz¹dzenie"),
                             codec->toUnicode("Nie wykryto urz¹dzenia PPB. Upewnij siê, ¿e kabel USB jest podpiêty."));
        return;
    }

    disconnect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertDirectMeasResults(QString,int)));
    connect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertFirstMeasResults(QString,int)));

    //ui->messEndButton->setEnabled(true);

    table->SetColTitle(codec->toUnicode("Pomiar wstêpny"));

    measThread->start();
    firstMeasure=1;
    duringMeasure=1;
    firstMeasStoped=0;
    ui->begMessButton->setEnabled(false);
    ui->directMessButton->setEnabled(false);
    ui->messEndButton->setEnabled(true);

}
//============================================
void Measure::DirectMeasure()
{   
    if(!measThread->ConfirmDeviceConnection())
    {
        QMessageBox::warning(this,codec->toUnicode("Urz¹dzenie"),
                             codec->toUnicode("Nie wykryto urz¹dzenia PPB. Upewnij siê, ¿e kabel USB jest podpiêty."));
        return;
    }

    directMeasure=1;
    duringMeasure=1;
    firstMeasStoped=0;

    if(!bySignal)
    {
        disconnect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertFirstMeasResults(QString,int)));
        connect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertDirectMeasResults(QString,int)));
        connect(counter,SIGNAL(Timeout()),this,SLOT(DirectMeasure()));
    }

    measThread->SetAlertValue(batt->messEndVolt);
    counter->Start(minutes,0);
    measThread->start();
    ui->messEndButton->setEnabled(true);
    ui->plotButton->setEnabled(true);
}

//============================================
void Measure::StopMeasure()
{
        QMessageBox warnMsg(QMessageBox::Warning, codec->toUnicode("Koñczenie pomiaru"),
                            codec->toUnicode("Przerwaæ pomiar?"), 0, this);
        warnMsg.addButton(tr("&Tak"),QMessageBox::AcceptRole);
        warnMsg.addButton(tr("&Nie"),QMessageBox::RejectRole);

        if (warnMsg.exec() == QMessageBox::RejectRole){
            return;
        }

        emit StopMeasureSignal();
        stoped=1;
        ui->messEndButton->setEnabled(false);

        if(directMeasure)
        {
            disconnect(counter,SIGNAL(Timeout()),this,SLOT(DirectMeasure()));
            ui->directMessButton->setEnabled(false);
            duringMeasure=0;
            counter->Stop();
            ui->messEndButton->setEnabled(false);
            table->Finished();
            batt->measDate=GenerateBattDateField();
            batt->measResult=table->GetResult()+"%";
            WriteTable(table->GetTable());
            WriteImage(plot->GetPlot());
            emit MeasureFinished();
        }

        if(firstMeasure)
        {
           // ui->directMessButton->setEnabled(true);
            disconnect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertFirstMeasResults(QString,int)));
            firstMeasStoped=1;
            duringMeasure=0;
            gaugeDisconnected=0;
            table->Finished(true);
            measThread->quit();
            ui->begMessButton->setEnabled(true);
            return;
        }

}
//============================================
void Measure::InsertFirstMeasResults(QString data,int row)
{
    if(data!="measEnd")
    {
        if(!data.contains("BLAD"))
        {
            //qDebug()<<data;
            table->InsertValue(row,0,data);
            plot->AddMeasurePoint(row+1,data.toDouble());
            gaugeDisconnected=0;
            //qDebug()<<"doszedlem";
        }
        else if(data.contains("BLAD"))
        {
           /* if(!gaugeDisconnected)
            {
                QMessageBox::critical(this,codec->toUnicode("Urz¹dzenie"),
                                      codec->toUnicode("<b>Krytyczny b³¹d.</b>\nCzy miernik jest pod³¹czony do reszty urz¹dzenia?"));
                gaugeDisconnected=1;
                //table->InsertValue(row,0,"bd");

            }*/
            table->InsertValue(row,0,"bd");
        }
    }
    else
    {
        measThread->quit();

        ui->messEndButton->setEnabled(false);
        if(!firstMeasStoped){
            ui->directMessButton->setEnabled(true);
        }
        disconnect(measThread,SIGNAL(DataHasCome(QString,int)),this,SLOT(InsertFirstMeasResults(QString,int)));
        ui->begMessButton->setEnabled(true);
        firstMeasure=0;
        duringMeasure=0;
        gaugeDisconnected=0;
    }
}
//============================================
void Measure::InsertDirectMeasResults(QString data, int row)
{
    ui->begMessButton->setEnabled(false);
    ui->directMessButton->setEnabled(false);
    ui->messEndButton->setText("Koniec");
    if((row==0 && data!="measEnd") || firstMeasStoped)
    {
        table->AddColumn(CurrentTime());      
        firstMeasStoped=0;
    }

    if(data!="measEnd")
    {
        if(!data.contains("BLAD",Qt::CaseInsensitive))
        {
            float alertValue=batt->messEndVolt.toFloat();
            float flData=data.toFloat();
            if(flData<=alertValue)
            {
                table->InsertValue(row,table->columnCount()-1,data,1);
                if(QFile::exists("cfg/beep.wav")){
                    QSound::play("cfg/beep.wav");
                }
                gaugeDisconnected=0;
            }
            else
            {
                table->InsertValue(row,table->columnCount()-1,data);
                gaugeDisconnected=0;
            }
            plot->AddMeasurePoint(row+1,data.toDouble());
        }
        else
        {
            /*if(!gaugeDisconnected)
            {
                QMessageBox::critical(this,codec->toUnicode("Urz¹dzenie"),
                                      codec->toUnicode("<b>Krytyczny b³¹d.</b>\nCzy miernik jest pod³¹czony do reszty urz¹dzenia?"));
                gaugeDisconnected=1;
                //table->InsertValue(row,0,"bd");

            }*/
            table->InsertValue(row,table->columnCount()-1,"bd");
        }
    }
    else
    {
        measThread->quit();
      //  directMeasure=0;
        if(!stoped){
            bySignal=1;     
        }
    }
}
//============================================
void Measure::DisplayBattInformation()
{
    battLabel->TakeBattery(*batt);
    battLabel->setEnabled(false);
    battLabel->show();
}

//============================================
QString Measure::CurrentTime()
{
    QString strTime=qtTime->currentTime().toString();
    int index=strTime.lastIndexOf(":");
    QString temp=strTime;
    strTime.clear();
    for(int i=0;i<index;i++){
        strTime.push_back(temp.at(i));
    }
    return strTime;
}
//============================================
QString Measure::GenerateBattDateField()
{
    QDate date=QDate::currentDate();
    QString strDate=date.toString("yyyy-MM-dd");
    strDate+=" "+CurrentTime();
    return strDate;
}
//============================================
bool Measure::WriteTable(QTextDocument *doc)
{
    QString tableName;
    {
        time_t rawtime;
        time(&rawtime);
        tableName = ConvertToString(rawtime);
    }
    tableName+="table.html";
    tableName_ = tableName;
    QFile file("db/"+tableName);
    if(file.open(QFile::WriteOnly))
    {
        QString outValue = doc->toHtml();
        QTextStream stream(&file);
        stream << outValue;
        file.close();
        return true;
    }
    return false;
}
//=================================================
void Measure::WriteImage(QImage *image)
{
    QString imageName;
    {
        time_t rawtime;
        time(&rawtime);
        imageName = ConvertToString(rawtime);
    }
    imageName+="image.png";
    plotName_=imageName;
    image->save("db/"+imageName,"png");
}

//=================================================
QString Measure::ConvertToString(long value)
{
    std::ostringstream ossVal;
    ossVal << value;
    return QString(ossVal.str().c_str());
}

//=================================================
//         MaesThread implementation
//=================================================

MeasThread::MeasThread()
{
    device=new DeviceRequest;
    connect(this,SIGNAL(finished()),this,SLOT(DeviceCleanUp()));
    breakMeasure=0;
    iteration=1;
    alertValue="";
    delay=0;
}
//============================================
MeasThread::~MeasThread()
{
    delete device;
}
//============================================
void MeasThread::run()
{
   breakMeasure=0;
   for(int i=1;i<=iteration;i++)
   {
       if(!device->PrepareRequest(i,delay))
       {
           device->CleanUp();
           break;
       }
       if(breakMeasure)
       {
           device->CleanUp();
           break;
       }
       if(!device->SendRequest())
       {
           device->CleanUp();
           emit DataHasCome("Sending ERROR",i-1);
           continue;
       }
       QString val=device->GetData();
       emit DataHasCome(val,i-1);
   }
   emit DataHasCome(QString("measEnd"),0);

}
//============================================
void MeasThread::SetAlertValue(QString value)
{
    QString val=value;
    if(!val.contains(QChar('.'))){
        val.append(".00");
    }
    if(value.size() == 1)
    {
        QString temp=val;
        val.clear();
        val="0"+temp;
    }
    alertValue=val;
}
//============================================
bool MeasThread::ConfirmDeviceConnection()
{
    return device->ConfirmConnection();
}
//============================================
void MeasThread::DeviceCleanUp()
{
    device->CleanUp();
}
