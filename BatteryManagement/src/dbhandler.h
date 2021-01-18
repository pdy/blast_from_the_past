#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QString>
#include <QStringList>

class DbWraper;
class BattInfo;
class QSqlField;


class DbHandler
{
public:
    DbHandler();
    ~DbHandler();
    enum LISTOF
    {
        PEOPLE,
        EQUIP
    };

    void SetId(QString id){dbId=id;}
    BattInfo GetBattInfo(QString objectName, QString battName);
    QString GetTableName(QString object,QString battery,QString measDate,QString measResult);
    QString GetPlotName(QString object,QString battery,QString measDate,QString measResult);
    QStringList MakeListFromMeas(LISTOF listOf, BattInfo &battery,QString date, QString measResult);
    QStringList GetMeasResults(QString objectName, QString battName);
    QStringList GetMeasResults(BattInfo &battery);
    bool AddNewBatt(BattInfo &battery);
    bool InsertMeasResult(BattInfo &battery, QString data, QString result, QString table, QString plot);
    bool DeleteBatt(QString objectName, QString battName, bool includeBattProp=1);
    bool DeleteBatt(BattInfo &battery);
    bool DeleteObject(QString objectName);
    bool UpdateBattInfoField(QString battName, QString objectName,QString colName, QString fieldValue);
    bool UpdateBattInfoField(BattInfo &battery,QString colName, QString fieldValue);
    void RejectChangesMode();
    void DoNotSaveChanges();
    void SaveChanges();

private:
    DbWraper *db;
    bool IsTemp();
    bool IsDb();   
    bool BattPropExist();
    bool CreateBattPropTable();
    bool CreateBattMeasTable(QString tableName);
    QSqlField Field(QString name, QString value);
    QString MakeList(QString file);
    QString MakeDelIdName(QString in);
    QString MakeNameWithoutDelId(QString in, bool isHtml);

    bool Connect();
    void Disconnect();

    QString dbId;
};


//===========================================================================
//klasa BattInfo to specjalny typ dla buforow uzupelnijajacych dane baterii

class BattInfo
{
public:
    BattInfo(){}
    BattInfo(QString objName, QString batteryName)
    {
        objectName=objName;
        battName=batteryName;

        objectAdress="";
        room="";
        battType="";
        cellsNumber="";
        messEndVolt="";
        installDate="";
        messMadeCurr="";
        roomTemperature="";
        extCellsState="";
        comments="";
    }
    bool IsValid()
    {
        if((objectName.isEmpty() || objectName.isNull())
            && (battName.isEmpty() || battName.isNull()))
        {
            return 0;
        }
        return 1;
    }

    //==============================
    //podstawowe info, battprop
    QString objectName;
    QString objectAdress;
    QString battName;
    QString room;
    QString battType;
    QString cellsNumber;
    QString installDate;

    //=========================================
    //info o ostatnich pomiarach, obiekt/batera - data/wynik
    QString messEndVolt;   
    QString messMadeCurr;
    QString roomTemperature;
    QString extCellsState;
    QString comments;
    QString measDate;
    QString measResult;
};

#endif // DBHANDLER_H
