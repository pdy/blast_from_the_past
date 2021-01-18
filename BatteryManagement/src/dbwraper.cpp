#include "dbwraper.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QStringList>

#include <vector>

DbWraper::DbWraper()
{
    dbIsOpen=0;
}
//=====================================================
DbWraper::~DbWraper()
{
    if(dbIsOpen)
    {
        db.close();
        query->clear();
        dbIsOpen=0;
    }
}
//=====================================================
bool DbWraper::Init(QString name)
{
    db = QSqlDatabase::addDatabase("QSQLITE",name);
    /*db.setHostName( "localhost" );
    db.setUserName( "root" );
    db.setPassword( "" );*/
    db.setDatabaseName( name );

    if( !db.open() )
    {
        qDebug() << "Brak polaczenia z baza";
        return 0;
    }
    else
    {
        qDebug() << "Polaczenie nawiazane\n";
        dbIsOpen=1;
        m_dbName=name;
        query=new QSqlQuery(db);

        return 1;
    }
}
//=====================================================
void DbWraper::Close()
{
    if(dbIsOpen)
    {
        query->clear();
        delete query;

        db.close();
        db.removeDatabase(m_dbName);
        //QSqlDatabase::removeDatabase(m_dbName);
        //qDebug() << db.connectionName();


        dbIsOpen=0;
    }
}
//=====================================================
QString DbWraper::GetField(QString strQuery)
{
    if(!query->exec(strQuery)){
        return QString("ERROR " + query->lastError().text());
    }

    QString field;
    while (query->next()){
          field = query->value(0).toString();
    }
    return field;
}
//=====================================================
QStringList DbWraper::GetRecord(QString strQuery, QStringList &cols)
{
    if(!query->exec(strQuery))
    {
        QString ret("ERROR " + query->lastError().text());
        QStringList retL;
        retL << ret;
        return retL;
    }
    if(cols.isEmpty()){
        return QStringList(QString("ERROR"));
    }
    QSqlRecord rec=query->record();
    std::vector<int> indexes;
    for(int i=0;i<cols.size();i++)
    {
        indexes.push_back(rec.indexOf(cols.at(i)));
    }

    QStringList retList;

    
    while(query->next())
    {
        for(size_t i=0;i<indexes.size();i++)
        {
            retList << query->value(indexes.at(i)).toString();
        }
    }
    return retList;
}
//=====================================================
QStringList DbWraper::GetColumn(QString tableName, QString colName)
{
    QStringList column;
    query->exec("select `"+colName+"` from `"+tableName+"`");

    while(query->next())
    {
        column << query->value(0).toString();
    }
    return column;
}
//=====================================================
QStringList DbWraper::GetColumn(QString tableName, QString colName, QString where)
{
    QStringList column;
    bool ok=query->exec("select `"+colName+"` from `"+tableName+"` where "+where);

    while(query->next())
    {
        column << query->value(0).toString();
    }
    if(!ok){
        qDebug()<<query->lastError().text();
    }
    return column;
}

//=====================================================
bool DbWraper::InsertRecord(QString tableName, QSqlRecord &record)
{
    if(tableName.isEmpty() || record.isEmpty()){
        return 0;
    }
    QString colsLine="(";
    QString valuesLine="(";
    for(int i=0;i<record.count();i++)
    {
        QString fieldName=record.fieldName(i);
        QString fieldValue=record.value(fieldName).toString();

        colsLine.append("`" + fieldName + "`");
        if(i<record.count()-1){
            colsLine.append(",");
        }
        else{
            colsLine.append(")");
        }

        valuesLine.append("'" + fieldValue + "'");
        if(i<record.count()-1){
            valuesLine.append(",");
        }
        else{
            valuesLine.append(")");
        }
    }
    if(!query->exec("insert into `"+tableName+"` "+colsLine+" values "+valuesLine))
    {
        qDebug() << query->lastError().text();
        return 0;
    }
    return 1;
}
//=====================================================
bool DbWraper::DeleteRecord(QString tableName, QSqlRecord &record)
{
    if(tableName.isEmpty() || record.isEmpty()){
        return 0;
    }
    QString dependies;
    for(int i=0;i<record.count();i++)
    {
        QString fieldName=record.fieldName(i);
        QString fieldValue=record.value(fieldName).toString();

        dependies.append("`" + fieldName + "`='" + fieldValue + "'");
        if(i<record.count()-1){
            dependies.append(" AND ");
        }

    }
    if(!query->exec("delete from `"+tableName+"` where "+dependies))
    {
        qDebug() << query->lastError().text();
        return 0;
    }
    return 1;
}
//=====================================================
bool DbWraper::DeleteTable(QString tableName)
{
    if(!query->exec("drop table `"+tableName+"`"))
    {
        qDebug() << query->lastError().text();
        return 0;
    }
    query->exec("VACUUM");
    return 1;
}
//=====================================================
bool DbWraper::CreateTable(QString tableName, QStringList &colsName, QStringList &colsType)
{
    //CREATE TABLE temp ( pierwszy VARCHAR ( 20 ) , drugi VARCHAR ( 20 ) , trzeci VARCHAR ( 20 ) ) ;
    QString tablePropertie;
    for(int i=0;i<colsName.size();i++)
    {
        tablePropertie.append("["+colsName.at(i)+"]");
        if(!colsType.isEmpty() && i<colsType.size())
        {
            tablePropertie.append(" "+colsType.at(i));
        }

        if(i<colsName.size()-1){
            tablePropertie.append(",");
        }
    }
    if(!query->exec("create table `"+tableName+"` ("+tablePropertie+")"))
    {
        qDebug()<<query->lastError().text();
        return 0;
    }
    return 1;
}
//=====================================================
bool DbWraper::Update(QString tableName, QString set, QString where)
{
    if(!query->exec("update "+tableName+" set "+set+" where "+where))
    {
        qDebug() << query->lastError().text();
        return 0;
    }
    return 1;
}
//=====================================================
bool DbWraper::RenameTable(QString prevTableName, QString newTableName)
{
    if(!query->exec("alter table `"+prevTableName+"` rename to `"+newTableName+"`"))
    {
        qDebug()<<query->lastError().text();
        return 0;
    }
    return 1;
}
//=====================================================
bool DbWraper::IsTable(QString tableName)
{
    QStringList tables=db.tables();
    if(tables.contains(tableName)){
        return true;
    }
    return false;
}
