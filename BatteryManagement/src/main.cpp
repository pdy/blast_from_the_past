#include <QtGui/QApplication>
#include "mainwindow.h"
#include "dbhandler.h"
#include <QDate>
#include <QMessageBox>
#include <sstream>
#include <QString>
#include "listsselected.h"

QString ConvertToString(int val)
{
    std::ostringstream ossPortNumber;
    ossPortNumber << val;
    return QString(ossPortNumber.str().c_str());
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDate date=QDate::currentDate();
    QString strDate=date.toString("yyyy-MM-dd");
    int year = 2011;
    int month = 11;
    int day = 1;
    int currYear,currMonth,currDay;
    {
       QString temp;
       temp.push_back(strDate.at(0));
       temp.push_back(strDate.at(1));
       temp.push_back(strDate.at(2));
       temp.push_back(strDate.at(3));
       currYear=temp.toInt();
       temp.clear();

       if(strDate.at(5)!=QChar('0')){
            temp.push_back(strDate.at(5));
       }
       temp.push_back(strDate.at(6));
       currMonth=temp.toInt();
       temp.clear();

       if(strDate.at(8)!=QChar('0')){
            temp.push_back(strDate.at(8));
       }
       temp.push_back(strDate.at(9));
       currDay=temp.toInt();
       temp.clear();

    }
    if(currYear<=year)
    {
        if(currMonth==month)
        {
            if(currDay<day)
            {
                MainWindow w;
                w.show();
                return a.exec();
            }
        }
        if(currMonth<month)
        {
            MainWindow w;
            w.show();
            return a.exec();
        }

    }

    QMessageBox::information(0,"Timeout","Czas waznosci obecnej wersji testowej minal.\n"
                                 "Skontaktuj sie z Pawlem Drzycimskim by otrzymac nastepna.");

    /*ListsSelected list;
    list.exec();
    list.FlushFiles();*/
    return a.exec();
}
