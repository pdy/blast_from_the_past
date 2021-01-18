#include "lcdcounter.h"
#include <QTimer>
#include <QDebug>
#include <sstream>
LcdCounter::LcdCounter()
{
    timer = new QTimer;
    setSegmentStyle(Flat);

    setDigitCount(4);
    QString text="0:00";
    display(text);
  //  minutes="012345";
    //seconds =new QString[60];
    for(int i=0;i<60;i++)
    {
        seconds<<ConvertToString(i);
        minutes<<ConvertToString(i);
    }
    value="";
    connect(this,SIGNAL(Timeout()),this,SLOT(StopSlot()));
}
//===============================
void LcdCounter::Start(int minutes, int seconds)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    lastSecIndex=seconds;
    lastMinIndex=minutes;
   // QString text;
   // text = "1:00";
   // display(text);
    timer->start(975);
    //qDebug()<<seconds;
}
//================================
void LcdCounter::Stop()
{

   disconnect(timer,SIGNAL(timeout()),this,SLOT(Update()));
   lastSecIndex=0;
   lastMinIndex=0;
   display("0:00");
}

//================================
void LcdCounter::Update()
{


    QString text;
    text.push_back(minutes.at(lastMinIndex));
    if(seconds.at(lastSecIndex).size()==1){
         text.append(":0");
    }
    else{
         text.append(":");
    }
    text.push_back(seconds.at(lastSecIndex));

    --lastSecIndex;
    display(text);
    value=text;

    if(lastSecIndex == -1 && lastMinIndex == 0)
    {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    }

    if(lastSecIndex == -1)
    {
        //qDebug() << text;
        lastSecIndex=59;
        --lastMinIndex;
    }
    if(text=="0:00"){
        emit Timeout();
    }

}
//================================
void LcdCounter::StopSlot()
{
    Stop();
}

//================================
QString LcdCounter::ConvertToString(int val)
{
    std::ostringstream ossVal;
    ossVal<<val;
    return QString(ossVal.str().c_str());
}
