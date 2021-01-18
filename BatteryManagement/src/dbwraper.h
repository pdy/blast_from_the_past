#ifndef DBWRAPER_H
#define DBWRAPER_H

#include <QString>
#include <QSqlDatabase>



class QSqlQuery;
class QSqlRecord;
class QStringList;

class DbWraper
{
public:
    DbWraper();
    ~DbWraper();

    bool Init(QString name);
    void Close();

    QString GetField(QString sqlQuery);
    QStringList GetRecord(QString sqlQuery, QStringList &colsName);
    QStringList GetColumn(QString tableName, QString colName);
    QStringList GetColumn(QString tableName, QString colName, QString where);

    bool InsertRecord(QString tableName, QSqlRecord &record);
    bool DeleteRecord(QString tableName, QSqlRecord &record);

    bool DeleteTable(QString tableName);
    bool CreateTable(QString tableName, QStringList &colsName,QStringList &colsType);   
    bool RenameTable(QString prevTableName, QString newTableName );

    bool Update(QString tableName, QString set, QString where);
    bool IsTable(QString tableName);

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QString m_dbName;
    bool dbIsOpen;
};

#endif // DATABASE_H
