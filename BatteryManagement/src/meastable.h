#ifndef MEASTABLE_H
#define MEASTABLE_H

#include <QTableWidget>
#include <QMap>

class QTextDocument;

class MeasTable : public QTableWidget
{
public:
    MeasTable();
    MeasTable(int rows, QString columnTitle);
    ~MeasTable();

    void AddColumn(QString columnTitle);
    void InsertValue(int row, int col, QString value, bool alert=0);
    void SetColTitle(QString title);
    void Finished(bool clearColorsOnly=0);
    QString GetResult(){return result;}
    QTextDocument *GetTable();
    void Clear();

private:
    QString result;
    QMap<int, int> ResultsForCells();
    QString ConvertToString(int val);
    QStringList labels;
    //QMap<int,int> results;
    int maxRows;
};

#endif // MEASTABLE_H
