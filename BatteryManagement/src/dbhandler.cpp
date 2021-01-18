#include "dbhandler.h"
#include "dbwraper.h"

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

DbHandler::DbHandler()
{
    db=new DbWraper;
    dbId="";

}
//============================================
DbHandler::~DbHandler()
{  
    Disconnect();
    delete db;
}
//============================================
bool DbHandler::Connect()
{
    if(dbId.isEmpty()){
        return 0;
    }
    QString connectBase="db/";
    if(IsTemp()){
        connectBase.append(dbId+"_temp.sqlite3");
    }
    else{
        connectBase.append(dbId+".sqlite3");
    }
    if(!db->Init(connectBase)){
        return 0;
    }
    return 1;
}
//============================================
void DbHandler::Disconnect()
{
    db->Close();

}

//============================================
BattInfo DbHandler::GetBattInfo(QString object, QString battName)
{
    BattInfo retBuf(object,battName);
    if(Connect())
    {
        QStringList colsList;
        colsList<<"adres lokalizacji"<<"pomieszczenie"<<"typ baterii"<<"ilosc ogniw"<<"data instalacji baterii";
        QStringList results=db->GetRecord("select * from `battprop` where `nazwa baterii`='"+battName+"' "
                                          "AND `nazwa lokalizacji`='"+object+"'",colsList);

        if(results.at(0).contains("ERROR"))
        {
            Disconnect();
            return retBuf;
        }
        retBuf.objectAdress=results.at(0);
        retBuf.room=results.at(1);
        retBuf.battType=results.at(2);
        retBuf.cellsNumber=results.at(3);      
        retBuf.installDate=results.at(4);
        Disconnect(); //dalsza metoda ma swoje wlasne polaczenie dlatego sie rozlaczamy zeby bylo czysto

        QStringList measures=GetMeasResults(retBuf);
        int lastIndex=measures.size()-1;
        if(lastIndex == -1){
            return retBuf;
        }
        QString lastMeasure=measures.at(lastIndex);
        int spaceBar=lastMeasure.lastIndexOf(" ");
        QString date,result;
        int i=0;
        while(i!=spaceBar)
        {
            date.push_back(lastMeasure.at(i));
            ++i;
        }
        ++i;
        while(i!=lastMeasure.size())
        {
            result.push_back(lastMeasure.at(i));
            ++i;
        }
        QStringList measRecord;
        QStringList cols;
        Connect();
        cols<<"napiecie konca pomiaru"<<"pomiar wykonano pradem"<<"temperatura pomieszczenia"
                <<"uwagi"<<"zewnetrzny stan ogniw";
        measRecord=db->GetRecord("select * from `"+retBuf.objectName+"/"+retBuf.battName+"`"
                                 " where `data pomiaru`='"+date+"'"
                                 " AND `wynik pomiaru`='"+result+"'",cols);

        //=================================
        // tymczasowy blok
        QString people  = db->GetField("select osoby from `"+retBuf.objectName+"/"+retBuf.battName+"`"
                                       " where `data pomiaru`='"+date+"'"
                                       " AND `wynik pomiaru`='"+result+"'");

        QString equip  = db->GetField("select sprzet from `"+retBuf.objectName+"/"+retBuf.battName+"`"
                                       " where `data pomiaru`='"+date+"'"
                                       " AND `wynik pomiaru`='"+result+"'");
        qDebug()<<people;
        qDebug()<<equip;
        // koniec tymczasowego bloku
        //==================================

        Disconnect();

        retBuf.measDate=date;
        retBuf.measResult=result;
        retBuf.messEndVolt=measRecord.at(0);
        retBuf.messMadeCurr=measRecord.at(1);
        retBuf.roomTemperature=measRecord.at(2);
        retBuf.comments=measRecord.at(3);
        retBuf.extCellsState=measRecord.at(4);

    } 
    return retBuf;
}
//============================================
QStringList DbHandler::GetMeasResults(BattInfo &battery)
{
    if(battery.IsValid())
    {
        return GetMeasResults(battery.objectName, battery.battName);
    }
    QStringList ret;
    return ret;

}

//============================================
QStringList DbHandler::GetMeasResults(QString objectName, QString battName)
{
    QStringList retList;
    if(Connect())
    {
        QString tabName=objectName+"/"+battName;

        QStringList datas=db->GetColumn(tabName,"data pomiaru");
        QStringList results=db->GetColumn(tabName,"wynik pomiaru");

        for(int i=0;i<datas.size();i++)
        {
            retList << datas.at(i)+" "+results.at(i);
        }
        Disconnect();
    }
    return retList;
}

//============================================
bool DbHandler::AddNewBatt(BattInfo &battery)
{

    if(Connect())
    {
        if(!battery.IsValid())
        {
            Disconnect();
            return 0;
        }
        if(!BattPropExist())
        {
            if(!CreateBattPropTable()){
                return false;
            }
        }
        QString battTableName=battery.objectName+"/"+battery.battName;
     /*   if(db->IsTable(battTableName)){
            DeleteBatt(battery);
        }*/
        QSqlRecord record;
        record.append(Field("nazwa baterii",battery.battName));
        record.append(Field("nazwa lokalizacji",battery.objectName));
        record.append(Field("typ baterii",battery.battType));
        record.append(Field("adres lokalizacji",battery.objectAdress));
        record.append(Field("ilosc ogniw",battery.cellsNumber));     
        record.append(Field("data instalacji baterii",battery.installDate));    
        record.append(Field("pomieszczenie",battery.room));


        if(!db->InsertRecord("battprop",record))
        {
            Disconnect();
            return 0;
        }
        //QString battTableName=battery.objectName+"/"+battery.battName;


        if(!CreateBattMeasTable(battTableName))
        {
            db->DeleteRecord("battprop",record);
            Disconnect();
            return 0;
        }
        Disconnect();
    }

    return 1;
}
//============================================
bool DbHandler::CreateBattMeasTable(QString tableName)
{

    QStringList cols;
    QStringList colsProp;
    cols << "data pomiaru" << "wynik pomiaru" << "tabela" << "wykres"
            <<"napiecie konca pomiaru"<<"pomiar wykonano pradem"<<"temperatura pomieszczenia"
            <<"uwagi"<<"zewnetrzny stan ogniw"<<"osoby"<<"sprzet";
    colsProp<<"VARCHAR (18)"<<"VARCHAR (4)"<<"VARCHAR (40)"<<"VARCHAR (40)"
            <<"VARCHAR (5)"<<"VARCHAR (5)"<<"VARCHAR (5)"
            <<"VARCHAR (100)"<<"VARCHAR (30)"<<"VARCHAR (500)"<<"VARCHAR (500)";

    if(!db->CreateTable(tableName,cols,colsProp))
    {
        return 0;
    }
    return 1;
}
//============================================
bool DbHandler::CreateBattPropTable()
{
    QStringList cols;
    QStringList colsProp;

    cols<<"nazwa lokalizacji"<<"adres lokalizacji"<<"nazwa baterii"
            <<"pomieszczenie"<<"typ baterii"<<"ilosc ogniw"<<"data instalacji baterii";
    colsProp<<"VARCHAR (25)"<<"VARCHAR (40)"<<"VARCHAR (25)"
            <<"VARCHAR (20)"<<"VARCHAR (25)"<<"VARCHAR (2)"<<"VARCHAR (20)";

    if(!db->CreateTable("battprop",cols,colsProp)){
        return 0;
    }
    return 1;
}

//============================================
bool DbHandler::InsertMeasResult(BattInfo &battery, QString data, QString result, QString table, QString plot)
{
    if(!battery.IsValid() && (data.isEmpty() || result.isEmpty())){
        return 0;
    }
    if(Connect())
    {
        QString tableName=battery.objectName+"/"+battery.battName;
        QSqlRecord record;
        record.append(Field("data pomiaru",data));
        record.append(Field("wynik pomiaru",result));
        record.append(Field("tabela",table));
        record.append(Field("wykres",plot));

        record.append(Field("napiecie konca pomiaru",battery.messEndVolt));
        record.append(Field("pomiar wykonano pradem",battery.messMadeCurr));
        record.append(Field("temperatura pomieszczenia",battery.roomTemperature));
        record.append(Field("uwagi",battery.comments));
        record.append(Field("zewnetrzny stan ogniw",battery.extCellsState));

        QString people = MakeList("cfg/curr_people");
        QString equip = MakeList("cfg/curr_equiplist");
        record.append(Field("osoby",people));
        record.append(Field("sprzet",equip));

        if(!db->InsertRecord(tableName,record))
        {
            Disconnect();
            return 0;
        }
        Disconnect();
    }
    return 1;

}

//============================================
QSqlField DbHandler::Field(QString name, QString value)
{
    QSqlField field(name,QVariant::String);
    field.setValue(value);   
    return field;
}
//============================================
bool DbHandler::DeleteBatt(BattInfo &battery)
{
    if(battery.IsValid())
    {
        return DeleteBatt(battery.objectName,battery.battName);
    }
    return 0;
}

//============================================
bool DbHandler::DeleteBatt(QString objectName, QString battName, bool includeBattProp)
{
    if(Connect())
    {
        if(includeBattProp)
        {
            QSqlRecord record;
            record.append(Field("nazwa lokalizacji",objectName));
            record.append(Field("nazwa baterii",battName));
            if(!db->DeleteRecord("battprop",record))
            {
                Disconnect();
                return 0;
            }
        }
        QString tableName=objectName+"/"+battName;

        //========================================
        // najpierw "usuwamy" pliki tabel.html i wykresów
        QStringList tablesList = db->GetColumn(tableName,"tabela");
        QStringList plotsList = db->GetColumn(tableName,"wykres");

        for(int i=0;i<tablesList.size();i++)
        {
            QString path;
            if(!tablesList.at(i).contains("db/")){
                path.append("db/"+tablesList.at(i));
            }
            else{
                path = tablesList.at(i);
            }

            //===============================================================
            //jezeli dzia³amy na tempie to musimy miec mozliwosc cofniecia zmian
            //dlatego pliki oznaczamy do ewentualnego poŸniejszego usuniecia
            //jezeli dzialamy wprost na bazie po prostu usuwamy pliki
            if(IsTemp())
            {
                QString newIdPath = MakeDelIdName(path);
                QFile::rename(path,newIdPath);
            }
            else
            {
                QFile::remove(path);
            }
        }
        for(int i=0;i<plotsList.size();i++)
        {
            QString path;
            if(!plotsList.at(i).contains("db/")){
                path.append("db/"+plotsList.at(i));
            }
            else{
                path = plotsList.at(i);
            }
            if(IsTemp())
            {
                QString newIdPath = MakeDelIdName(path);
                QFile::rename(path,newIdPath);
            }
            else
            {
                QFile::remove(path);
            }
        }
        // "usuneliœmy" pliki tabel i wykresów
        //==================================

        //==================================
        // usuwamy tabele pomiarow¹ z bazy
        if(!db->DeleteTable(tableName))
        {
            Disconnect();
            return 0;
        }
        Disconnect();
        return 1;
    }
    return 0;
}
//============================================
bool DbHandler::DeleteObject(QString objectName)
{
    //QStringList allBattNames;
    if(Connect())
    {
        QStringList allBattNames=db->GetColumn("battprop","nazwa baterii","`nazwa lokalizacji`='"+objectName+"'");
        if(allBattNames.size()==0)//czyli nie ma takiego obiektu w bazie
        {
            Disconnect();
            return 1;
        }
        QSqlRecord record;
        record.append(Field("nazwa lokalizacji",objectName));
        if(!db->DeleteRecord("battprop",record))
        {
            Disconnect();
            return 0;
        }
        Disconnect(); //nastêpna metoda ma swoje w³asne po³¹czenie
        for(int i=0;i<allBattNames.size();i++)
        {
            if(!DeleteBatt(objectName,allBattNames.at(i),0))
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
//============================================
bool DbHandler::UpdateBattInfoField(BattInfo &battery,QString colName, QString fieldValue)
{
    if(battery.IsValid()){
        return UpdateBattInfoField(battery.battName, battery.objectName, colName,fieldValue);
    }
    return 0;
}

//============================================
bool DbHandler::UpdateBattInfoField(QString battName, QString objectName,QString colName, QString fieldValue)
{

    if(Connect())
    {

        if(colName=="nazwa lokalizacji")
        {
            if(!db->Update("battprop","`"+colName+"`='"+fieldValue+"'","`nazwa lokalizacji`='"+objectName+"'"))
            {
                Disconnect();
                return 0;
            }
            QStringList allBattNames=db->GetColumn("battprop","nazwa baterii","`nazwa lokalizacji`='"+fieldValue+"'");
            for(int i=0;i<allBattNames.size();i++)
            {
                QString newName=fieldValue+"/"+allBattNames.at(i);
                QString oldName=objectName+"/"+allBattNames.at(i);
                if(!db->RenameTable(oldName,newName))
                {
                    Disconnect();
                    return 0;
                }
            }
        }
        else
        {
            if(!db->Update("battprop","`"+colName+"`='"+fieldValue+"'","`nazwa baterii`='"+battName+"' "
                          "AND `nazwa lokalizacji`='"+objectName+"'"))
            {
                Disconnect();
                return 0;
            }
            if(colName=="nazwa baterii")
            {
                //QString objectName=db->GetField("select ")
                QString newName=objectName+"/"+fieldValue;
                QString oldName=objectName+"/"+battName;
                if(!db->RenameTable(oldName,newName))
                {
                    Disconnect();
                    return 0;
                }
            }
        }

        Disconnect();
    }
    return 1;
}
//============================================
void DbHandler::RejectChangesMode()
{
    if(!IsDb())
    {
        Connect();
        Disconnect();
    }
    if(!IsTemp())
    {
        QFile file;
        file.copy("db/"+dbId+".sqlite3", "db/"+dbId+"_temp.sqlite3");

    }
}
//============================================
void DbHandler::DoNotSaveChanges()
{
    if(IsTemp())
    {
        qDebug()<<QFile::remove("db/"+dbId+"_temp.sqlite3");

        //=========================================
        // je¿eli pliki html lub png zosta³y oznaczone
        // jako do usuniêcia - oznaczamy je jako nie do usuniêcia
        QDir directory("db/");
        QStringList entrys = directory.entryList(QDir::Files);
        for(int i=0;i<entrys.size();i++)
        {
            if(entrys.at(i).contains("_todel"))
            {
                QString name;
                if(entrys.at(i).contains(".html") || entrys.at(i).contains(".htm")){
                    name = MakeNameWithoutDelId(entrys.at(i),1);
                }
                else{
                    name = MakeNameWithoutDelId(entrys.at(i),0);
                }
                QFile::rename("db/"+entrys.at(i),"db/"+name);
            }
        }
    }
}

//============================================
void DbHandler::SaveChanges()
{
    if(IsTemp())
    {
        QFile file;
        file.remove("db/"+dbId+".sqlite3");
        file.rename("db/"+dbId+"_temp.sqlite3","db/"+dbId+".sqlite3");

        //=========================================
        // je¿eli pliki html lub png zosta³y oznaczone
        // jako do usuniêcia - usuwamy je
        QDir directory("db/");
        QStringList entrys = directory.entryList(QDir::Files);
        for(int i=0;i<entrys.size();i++)
        {
            if(entrys.at(i).contains("_todel"))
            {
                QFile::remove("db/"+entrys.at(i));
            }
        }
    }
}
//============================================
bool DbHandler::IsTemp()
{
    QFile file("db/"+dbId+"_temp.sqlite3");
    bool ret=file.open(QFile::ReadOnly);
    file.close();
    return ret;
}
//============================================
bool DbHandler::IsDb()
{
    QFile file("db/"+dbId+".sqlite3");
    bool ret=file.open(QFile::ReadOnly);
    file.close();
    return ret;
}

//============================================
bool DbHandler::BattPropExist()
{
    if(!db->IsTable("battprop")){
        return false;
    }
    return true;
}
//============================================
QString DbHandler::MakeList(QString filePath)
{
    QString retString;

    QFile file(filePath);
    if(file.open(QFile::ReadOnly))
    {

        QTextStream in(&file);
        QString value;
        do
        {
            value = in.readLine();
            if(value.isEmpty()){
                break;
            }
            retString.append(value + QChar(';'));
        }while(!value.isNull());
        file.close();
    }
    if(retString.isEmpty()){
        retString = "";
    }
    return retString;
}
//============================================
QString DbHandler::MakeDelIdName(QString in)
{
    QString retValue;
    if(!in.contains("db/")){
        retValue.append("db/"+in);
    }
    else{
        retValue=in;
    }
    int index = retValue.indexOf(".html");
    if(index == -1){
        index = retValue.indexOf(".htm");
    }
    if(index == -1){
        index = retValue.indexOf(".png");
    }
    retValue.insert(index,"_todel");
    return retValue;
}
//============================================
QString DbHandler::MakeNameWithoutDelId(QString in, bool isHtml)
{
    QString retString;
    if(in.contains("_todel"))
    {
        int index = in.indexOf("_todel");
        for(int i=0;i<index;i++){
            retString.push_back(in.at(i));
        }
        if(isHtml){
            retString.append(".html");
        }
        else{
            retString.append(".png");
        }
    }
    return retString;
}
//============================================
QStringList DbHandler::MakeListFromMeas(LISTOF listOf, BattInfo &battery, QString date, QString measResult)
{
    QStringList retBuf;
    QString column;
    if(listOf == PEOPLE){
        column = "osoby";
    }
    else{
        column = "sprzet";
    }
    Connect();
    QString value = db->GetField("select "+column+" from `"+battery.objectName+"/"+battery.battName+"` "
                                 "where `data pomiaru`='"+date+"' "
                                 "AND `wynik pomiaru`='"+measResult+"'");
    Disconnect();
    if(!value.isEmpty())
    {
        int i=0;
        for(;;)
        {
            QString temp;
            while(value.at(i)!=QChar(';'))
            {
                temp.push_back(value.at(i));
                ++i;
                if(i == value.size()-1){
                    break;
                }
            }
            retBuf << temp;
            if(i == value.size()-1){
                break;
            }
            else{
                ++i;
            }
        }
    }
    return retBuf;
}
//============================================
QString DbHandler::GetTableName(QString object, QString battery, QString measDate, QString measResult)
{
    QString value;
    if(Connect())
    {
         value = db->GetField("select tabela from `"+object+"/"+battery+"` "
                                 "where `data pomiaru`='"+measDate+"' "
                                 "and `wynik pomiaru`='"+measResult+"'");
         Disconnect();
         return value;
    }
    return "";
}
//============================================
QString DbHandler::GetPlotName(QString object, QString battery, QString measDate, QString measResult)
{
    QString value;
    if(Connect())
    {
         value = db->GetField("select wykres from `"+object+"/"+battery+"` "
                                 "where `data pomiaru`='"+measDate+"' "
                                 "and `wynik pomiaru`='"+measResult+"'");
         Disconnect();
         return value;
    }
    return "";
}
