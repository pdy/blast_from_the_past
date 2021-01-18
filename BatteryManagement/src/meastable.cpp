#include "meastable.h"
#include <QTableWidgetItem>
#include <QBrush>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableCell>
#include <QTextCursor>
#include <QTextCodec>

#include <sstream>


MeasTable::MeasTable()
{
    setColumnCount(1);
}
//===============================
MeasTable::MeasTable(int rows, QString columnTitle)
{
    setColumnCount(1);
    setRowCount(rows);
    labels << columnTitle;
    setHorizontalHeaderLabels(labels);
    maxRows=rows;
   // colRow[0]=0;
    //setUpdatesEnabled(true);
}
//===============================
MeasTable::~MeasTable()
{

}
//===============================
void MeasTable::AddColumn(QString columnTitle)
{
    int currColsNum=columnCount();
    setColumnCount(currColsNum+1);
    labels << columnTitle;
    setHorizontalHeaderLabels(labels);
    //colRow[currColsNum+1]=0;
}
//===============================
void MeasTable::InsertValue(int row, int col, QString value, bool alert)
{
    if(row>rowCount()){
        return;
    }
    if(col>columnCount()){
        return;
    }

    QTableWidgetItem *item=new QTableWidgetItem;
    item->setText(value);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    QColor color;
    QString colorName;
    if(alert)
    {
        colorName="red";
        color.setNamedColor(colorName);
        item->setBackgroundColor(color);
    }
    else
    {
        colorName="white";
        color.setNamedColor(colorName);
        item->setBackgroundColor(color);
    }
    setItem(row,col,item);
    scrollToItem(item);

    if(row+1<=rowCount())// && colorName=="white")
    {
        QColor nextColor;
        QTableWidgetItem *nextItem=new QTableWidgetItem;
        nextItem->setText("");
        nextItem->setFlags(Qt::ItemIsEnabled);
        nextColor.setBlue(255);
        nextItem->setBackgroundColor(nextColor);
        this->setItem(row+1,col,nextItem);
        if(row+1<rowCount()){
            scrollToItem(nextItem);
        }
    }
    update();


}
//================================
void MeasTable::SetColTitle(QString title)
{
    QTextCodec *codec = QTextCodec::codecForLocale();
    if(title.contains(codec->toUnicode("Pomiar wstêpny")))
    {
        labels.clear();
    }
    labels << title;
    setHorizontalHeaderLabels(labels);
}
//================================
void MeasTable::Finished(bool clearColorsOnly)
{
    //=======================
    // ustawiamy kolor, wype³niamy do koñca ostatni¹ kolumnê
    {
        QList<QTableWidgetItem *> items=findItems("",Qt::MatchExactly);
        if(!items.isEmpty())
        {
            QString colorName="white";
            QColor color;
            color.setNamedColor(colorName);
            for(int i=0;i<items.size();i++)
            {
                //items.at(0)->setBackgroundColor(color);
                int rowNum,colNum;
                if(items.at(i)->backgroundColor()==Qt::blue)
                {
                    rowNum=row(items.at(i));
                    colNum=column(items.at(i));
                    items.at(i)->setBackgroundColor(color);
                    QTableWidgetItem *newItem=new QTableWidgetItem(*items.at(i));
                  //  this->setItem(rowNum,colNum,newItem);
                    setItem(rowNum,colNum,newItem);
                    break;

                }
            }
        }
        int lastCol = columnCount()-1;
        bool startFilling=0;
        for(int row=0;row<rowCount();row++)
        {
            if(!startFilling)
            {
                QTableWidgetItem *item = this->item(row,lastCol);
                if(item->text()=="")
                {
                    startFilling=1;
                   // continue;
                }
            }
            else{
                InsertValue(row,lastCol,"");
            }

        }
    }

    if(!clearColorsOnly)
    {
        QMap<int,int> results = ResultsForCells();
        QMap<int,int>::iterator it=results.begin();
        int intResult=32000;
        while(it!=results.end())
        {
            if(it.value()<intResult){
                intResult=it.value();
            }
            ++it;
        }
      //  intResult*=100;
        result=ConvertToString(intResult);
       // this->clear();
    }
   // this->update();

}
//================================
QMap<int,int> MeasTable::ResultsForCells()
{
    QMap<int,int> retBuf;

    bool lastItemPassed=0;
    for(int row=0;row<rowCount();row++)
    {

        QTableWidgetItem *firstItem = item(row,0);
        QTableWidgetItem *lastItem ;//= this->item(row,columnCount()-1);
        if(lastItemPassed){
            lastItem = item(row,columnCount()-2);
        }
        else
        {
            lastItem = item(row,columnCount()-1);
            int i=2;
            while(lastItem->text()=="" || lastItem->text()=="bd")
            {
                lastItem = item(row,columnCount()-i);
                ++i;
                lastItemPassed=1;
            }
        }
        float res = (lastItem->text().toFloat() / firstItem->text().toFloat()) * 100;
        retBuf.insert(row+1,(int)res);
    }

    return retBuf;
}
//================================
QTextDocument *MeasTable::GetTable()
{
    QTextDocument *editor = new QTextDocument;
    QTextCursor cursor(editor);

    QTextTableFormat tableFormat;
    tableFormat.setBorderBrush(QBrush(Qt::black));
    tableFormat.setBorder(2);
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(0);
    QTextTable *textTable = cursor.insertTable(rowCount(),columnCount());
    textTable->setFormat(tableFormat);


    for(int row=0;row<rowCount();row++)
    {

        for(int col=0;col<columnCount();col++)
        {
            QTableWidgetItem *cell=item(row,col);
            cursor = textTable->cellAt(row,col).firstCursorPosition();         

            if(cell->backgroundColor()==Qt::red)
            {
                QTextTableCell cellForChangeColor = textTable->cellAt(row,col);
                QTextCharFormat cellColor = cellForChangeColor.format();
                cellColor.setBackground(QColor(Qt::red));
                cellForChangeColor.setFormat(cellColor);
                cursor.insertText(cell->text(),cellColor);

            }
            else{
                cursor.insertText(cell->text());
            }
        }
    }

  /*  QFile file("table.txt");
    if(file.open(QFile::WriteOnly))
    {
        QTextStream stream(&file);
        stream << retString;
        file.close();
    }*/

    return editor;
}
//==================================================
void MeasTable::Clear()
{
    labels.clear();
    clear();
}

//==================================================
QString MeasTable::ConvertToString(int val)
{
    std::ostringstream ossVal;
    ossVal << val;
    return QString(ossVal.str().c_str());
}


