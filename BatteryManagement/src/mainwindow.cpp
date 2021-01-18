#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "xbeltree.h"
#include "dbhandler.h"
#include "batterylabel.h"
#include "measure.h"
#include "configdialog.h"
#include "reportwidget.h"
#include "listsselected.h"

#include <QTextCodec>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>
#include <QMapIterator>
#include <QTreeWidgetItem>
#include <QDate>
#include <QTime>
#include <QPushButton>
#include <QListWidgetItem>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xbelTree=new XbelTree(ui->treeWidget);
    battLabel=new BatteryLabel;
    measure = new Measure;
    db=new DbHandler;
    configDialog = new ConfigDialog;
    reportWidget = new ReportWidget;
    listsSelected = new ListsSelected;


    //xbelTree->Read("xblprm.xbel");
    xbelTree->setGeometry(ui->treeWidget->geometry());

    codec=QTextCodec::codecForLocale();

    connect(xbelTree,SIGNAL(ClickedTreeItem(QTreeWidgetItem*,int)),this,SLOT(BattInfoLabels(QTreeWidgetItem*,int)));
    connect(xbelTree,SIGNAL(MakeMeasure(BattInfo&)),this,SLOT(GoToBattLabel(BattInfo&)));
    connect(xbelTree,SIGNAL(DatabaseId(QString)),this,SLOT(SetDatabaseId(QString)));
    connect(battLabel,SIGNAL(ForwardButtonClicked()),this,SLOT(GoToMeasures()));
    connect(battLabel,SIGNAL(ClosedWindow()),this,SLOT(MeasuresBattLabelsClosed()));
    connect(measure,SIGNAL(MeasureFinished()),this,SLOT(MeasuresFinished()));
    connect(measure,SIGNAL(CloseWindow()),this,SLOT(MeasuresBattLabelsClosed()));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(GenerateRaport(QListWidgetItem*)));

    CreateActions();
    CreateMenus();
    CreateToolBars();

    labels[ui->battTypeKey]=ui->battTypeVal;
    labels[ui->cellNumberKey]=ui->cellNumberVal;
    labels[ui->commentsKey]=ui->commentsVal;
    labels[ui->extCellStateKey]=ui->extCellStateVal;
    labels[ui->installDataKey]=ui->installDataVal;
    labels[ui->roomKey]=ui->roomVal;
    labels[ui->roomTempKey]=ui->roomTempVal;
    labels[ui->localAdressKey]=ui->localAdressVal;
    labels[ui->localNameKey]=ui->localNameVal;
    labels[ui->cellNumberKey]=ui->cellNumberVal;
    labels[ui->messEndVoltKey]=ui->messEndVoltVal;
    labels[ui->messMadeCurrKey]=ui->messMadeCurrVal;
    EraseValLabels();
    KeyLabelsVisible(false);
    //labels.key(ui->localAdressVal)->setVisible(false);
}
//================================================

MainWindow::~MainWindow()
{
    delete xbelTree;
    delete battLabel;
    delete db;
    delete measure;
    delete reportWidget;
    delete ui;
}
//================================================
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
//================================================
void MainWindow::closeEvent(QCloseEvent *e)
{
    if(xbelTree->WasModified())
    {

        QMessageBox questionMsg(QMessageBox::Question, codec->toUnicode("Koniec pracy programu."),
                                codec->toUnicode("Zapisaæ zmiany w istniej¹cej strukturze?"),QMessageBox::NoButton,this);
        QPushButton *yesButton = questionMsg.addButton(QMessageBox::Yes);
        yesButton->setText("Tak");
        QPushButton *noButton = questionMsg.addButton(QMessageBox::No);
        noButton->setText("Nie");
        QPushButton *cancelButton = questionMsg.addButton(QMessageBox::Cancel);
        cancelButton->setText("Anuluj");
        questionMsg.exec();
        if(questionMsg.clickedButton() == yesButton)
        {
            if(currSobTreePath.isEmpty()){
                SaveAs();
            }
            else{
                Save();
            }
        }
        else if(questionMsg.clickedButton() == noButton){
            xbelTree->DoNotSave();
        }
        else if(questionMsg.clickedButton() == cancelButton)
        {
            e->ignore();
            return;
        }

    }
    qApp->quit();
}

//================================================
void MainWindow::Open()
{

    if(xbelTree->WasModified())
    {
        QMessageBox questionMsg(QMessageBox::Question, codec->toUnicode("Koniec pracy programu."),
                                codec->toUnicode("Zapisaæ zmiany w istniej¹cej strukturze?"),QMessageBox::NoButton,this);
        QPushButton *yesButton = questionMsg.addButton(QMessageBox::Yes);
        yesButton->setText("Tak");
        QPushButton *noButton = questionMsg.addButton(QMessageBox::No);
        noButton->setText("Nie");
        QPushButton *cancelButton = questionMsg.addButton(QMessageBox::Cancel);
        cancelButton->setText("Anuluj");
        questionMsg.exec();
        if(questionMsg.clickedButton() == yesButton)
        {
            if(currSobTreePath.isEmpty()){
                SaveAs();
            }
            else{
                Save();
            }
        }
        else if(questionMsg.clickedButton() == noButton){
            xbelTree->DoNotSave();
        }
        else if(questionMsg.clickedButton() == cancelButton){
            return;
        }
    }


    QString fileName =
               QFileDialog::getOpenFileName(this, tr("Open SOB File"),
                                            QDir::currentPath(),
                                            tr("Pliki SOB (*.sob *.SOB)"));
    if (fileName.isEmpty()){
           return;
       }
    if (xbelTree->Read(fileName)){
            statusBar()->showMessage(codec->toUnicode("Struktura za³adowana"), 2000);
        }
    currSobTreePath.clear();
    currSobTreePath=fileName;
   /* QString name;
    int begIndex=fileName.lastIndexOf("/");
    ++begIndex;
    while(begIndex!=fileName.size())
    {
        name.push_back(fileName[begIndex]);
        ++begIndex;
    }

    xbelTree->SetHeaderTitle(name);*/

}
//================================================
void MainWindow::NewStruct()
{
    if(xbelTree->WasModified())
    {
        QMessageBox questionMsg(QMessageBox::Question, codec->toUnicode("Koniec pracy programu."),
                                codec->toUnicode("Zapisaæ zmiany w istniej¹cej strukturze?"),QMessageBox::NoButton,this);
        QPushButton *yesButton = questionMsg.addButton(QMessageBox::Yes);
        yesButton->setText("Tak");
        QPushButton *noButton = questionMsg.addButton(QMessageBox::No);
        noButton->setText("Nie");
        QPushButton *cancelButton = questionMsg.addButton(QMessageBox::Cancel);
        cancelButton->setText("Anuluj");
        questionMsg.exec();
        if(questionMsg.clickedButton() == yesButton)
        {
            if(currSobTreePath.isEmpty()){
                SaveAs();
            }
            else{
                Save();
            }
        }
        else if(questionMsg.clickedButton() == noButton){
            xbelTree->DoNotSave();
        }
        else if(questionMsg.clickedButton() == cancelButton){
            return;
        }
    }
    currSobTreePath.clear();
    xbelTree->SetHeaderTitle("Title");
    xbelTree->GenerateNewStruct();

}

//================================================
void MainWindow::Save()
{
    if(xbelTree->GetHeaderTitle()=="Nowa struktura."){
        SaveAs();
        return;
    }
    if(!currSobTreePath.isEmpty())
    {
        if(xbelTree->Write(currSobTreePath)){
            statusBar()->showMessage(tr("Zapisano zmiany"), 2000);
            xbelTree->Save();
        }
    }
}
//================================================
void MainWindow::SaveAs()
{
    QString fileName =
                QFileDialog::getSaveFileName(this, codec->toUnicode("Zapisz strukturê SOB"),
                                             QDir::currentPath(),
                                             tr("Pliki SOB (*.sob *.SOB)"));
    if (fileName.isEmpty()){
            return;
    }

    if (xbelTree->Write(fileName)){
            statusBar()->showMessage(codec->toUnicode("Zapisano strukturê."), 2000);
            xbelTree->Save();
    }
    else{
        xbelTree->DoNotSave();
        return;
    }

    //=============================
    //wczytujemy zapisana strukture

    if (xbelTree->Read(fileName))
    {

        statusBar()->showMessage(codec->toUnicode("Struktura za³adowana"), 2000);
        currSobTreePath.clear();
        currSobTreePath=fileName;
        QString name;
        int begIndex=fileName.lastIndexOf("/");
        ++begIndex;
        while(begIndex!=fileName.size())
        {
            name.push_back(fileName[begIndex]);
            ++begIndex;
        }

        xbelTree->SetHeaderTitle(name);
    }
    else
    {
        xbelTree->SetHeaderTitle("Exceptional error occured!");
    }


}
//================================================
void MainWindow::MoveUp()
{
    xbelTree->MoveItemUp();

}
//================================================
void MainWindow::MoveDown()
{
    xbelTree->MoveItemDown();

}
//================================================
void MainWindow::NewBattery()
{
    if(xbelTree->GetHeaderTitle() == "Brak struktury."){
        return;
    }
    if(!xbelTree->currentItem()){
        return;
    }
    xbelTree->AddBattSlot();
}
//================================================
void MainWindow::NewObject()
{
    if(xbelTree->GetHeaderTitle() == "Brak struktury."){
        return;
    }

    xbelTree->AddObjSlot();
}

//================================================
void MainWindow::BattInfoLabels(QTreeWidgetItem *item, int)
{
    //DbHandler *db = new DbHandler;
    BattInfo batt;
    ui->listWidget->clear();
    if(item->parent())
    {
        batt=db->GetBattInfo(item->parent()->text(0),item->text(0));
        ValLabelsText(batt,this->BATTERY);
        QStringList messList=db->GetMeasResults(batt);


        for(int i=0;i<messList.size();i++)
        {
            ui->listWidget->insertItem(i,messList.at(i));
        }
    }
    else
    {
        EraseValLabels();
        KeyLabelsVisible(false);
        ui->localNameKey->setVisible(true);
        ui->localNameVal->setText(item->text(0));
    }
    //delete db;
}
//================================================
void MainWindow::CreateActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&Nowa struktura"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(codec->toUnicode("Stwórz now¹ strukturê."));
    connect(newAct, SIGNAL(triggered()), this, SLOT(NewStruct()));

    openAct = new QAction(QIcon(":/images/open.png"), codec->toUnicode("&Otwórz..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(codec->toUnicode("Otwórz istniej¹c¹ strukturê."));
    connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Zapisz"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(codec->toUnicode("Zapisz bierz¹c¹ strukturê."));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(Save()));

    saveAsAct = new QAction(tr("Zapisz &jako..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(codec->toUnicode("Zapisz bierz¹c¹ strukturê w nowym pliku."));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(SaveAs()));

    exitAct = new QAction(codec->toUnicode("Zakoñcz"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(codec->toUnicode("Zakoñcz pracê."));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    moveUpAct = new QAction(QIcon(":/images/up.png"),codec->toUnicode("Przesuñ w górê"),this);
    moveUpAct->setStatusTip(codec->toUnicode("Przesuñ element w górê."));
    connect(moveUpAct,SIGNAL(triggered()),this,SLOT(MoveUp()));

    moveDownAct = new QAction(QIcon(":/images/down.png"),codec->toUnicode("Przesuñ w dó³"),this);
    moveDownAct->setStatusTip(codec->toUnicode("Przesuñ element w dó³."));
    connect(moveDownAct,SIGNAL(triggered()),this,SLOT(MoveDown()));

    makeMeasAct = new QAction(QIcon(":images/right.png"),"Wykonaj pomiar",this);
    connect(makeMeasAct,SIGNAL(triggered()),xbelTree,SLOT(MakeMeasureSlot()));

    measSetAct = new QAction(tr("Pomiaru"),this);
   // measSetAct->setStatusTip(codec->toUnicode("Ustaw wszystkie potrzebne parametry programu."));
    connect(measSetAct,SIGNAL(triggered()),configDialog,SLOT(ExecWithMeasure()));

    reportSetAct = new QAction(tr("Raportu"),this);
    connect(reportSetAct,SIGNAL(triggered()),configDialog,SLOT(ExecWithReport()));

    addBattAct = new QAction(QIcon(":images/add_battery.PNG"),codec->toUnicode("Dodaj bateriê."),this);
   // addBattAct->setStatusTip(codec->toUnicode("Dodaj now¹ bateriê"));
    connect(addBattAct,SIGNAL(triggered()),this,SLOT(NewBattery()));

    addObjAct = new QAction(QIcon(":images/add_folder.PNG"),codec->toUnicode("Dodaj obiekt."),this);
   // addObjAct->setStatusTip(codec->toUnicode("Dodaj nowy obiekt"));
    connect(addObjAct,SIGNAL(triggered()),this,SLOT(NewObject()));

}
//================================================
void MainWindow::CreateMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Plik"));

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    settingsMenu = menuBar()->addMenu(tr("&Ustawienia"));
    settingsMenu->addAction(measSetAct);
    settingsMenu->addAction(reportSetAct);
}
//================================================
void MainWindow::CreateToolBars()
{
    fileToolBar=addToolBar(tr("&Plik"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    //fileToolBar->addAction(saveAsAct);

    itemMoveToolBar=addToolBar(codec->toUnicode("Przesuñ"));
    itemMoveToolBar->addAction(moveUpAct);
    itemMoveToolBar->addAction(moveDownAct);
    itemMoveToolBar->addAction(makeMeasAct);

    addItemsToolBar=addToolBar("Dodaj");
    addItemsToolBar->addAction(addBattAct);
    addItemsToolBar->addAction(addObjAct);

}
//================================================
void MainWindow::EraseValLabels()
{
    QMap<QLabel *,QLabel*>::iterator it=labels.begin();
    while(it!=labels.end())
    {
        it.value()->setText("");
        ++it;
    }
}
//================================================
void MainWindow::KeyLabelsVisible(bool visible)
{
    QMap<QLabel *,QLabel*>::iterator it=labels.begin();
    while(it!=labels.end())
    {
        it.key()->setVisible(visible);
        ++it;
    }
}
//================================================
void MainWindow::ValLabelsText(BattInfo &batt, PrintMode mode)
{
    if(mode==OBJECT)
    {
        EraseValLabels();
        KeyLabelsVisible(false);
        ui->localNameKey->setVisible(true);
        ui->localNameVal->setText(batt.objectName);
        ui->localAdressKey->setVisible(true);
        ui->localAdressVal->setText(batt.objectAdress);

    }
    else
    {
        EraseValLabels();
        KeyLabelsVisible(true);

        ui->battTypeVal->setText(batt.battType);
        ui->cellNumberVal->setText(batt.cellsNumber);
        ui->commentsVal->setText(batt.comments);
        ui->extCellStateVal->setText(batt.extCellsState);
        ui->installDataVal->setText(batt.installDate);
        ui->roomVal->setText(batt.room);
        ui->roomTempVal->setText(batt.roomTemperature);
        ui->localAdressVal->setText(batt.objectAdress);
        ui->localNameVal->setText(batt.objectName);
        ui->cellNumberVal->setText(batt.cellsNumber);
        ui->messEndVoltVal->setText(batt.messEndVolt);
        ui->messMadeCurrVal->setText(batt.messMadeCurr);
    }
}
//================================================
void MainWindow::GoToBattLabel(BattInfo &battery)
{
   /* if(xbelTree->GetHeaderTitle() == "Brak struktury."){
        return;
    }*/
    this->hide();
    battery=db->GetBattInfo(battery.objectName,battery.battName);
    battLabel->TakeBattery(battery);
    battLabel->show();
}
//================================================
void MainWindow::GoToMeasures()
{
    battLabel->hide();
    BattInfo *battery = battLabel->ReturnBattery();
    measure->TakeBattery(*battery);
    measure->show();
    if(listsSelected->IsSourceFilesEmpty()){
        listsSelected->FlushFiles();
    }
    else
    {
        listsSelected->LoadAll();
        listsSelected->exec();
    }
}
//================================================
void MainWindow::SetDatabaseId(QString id)
{
    db->SetId(id);
}

//================================================
void MainWindow::MeasuresFinished()
{
    BattInfo *battery=measure->ReturnBattery();
    measure->hide();
    db->InsertMeasResult(*battery,battery->measDate,battery->measResult,
                         measure->ReturnTableName(),measure->ReturnPlotName());
    db->UpdateBattInfoField(*battery,"adres lokalizacji",battery->objectAdress);
    db->UpdateBattInfoField(*battery,"ilosc ogniw",battery->cellsNumber);
    db->UpdateBattInfoField(*battery,"data instalacji baterii",battery->installDate);
    db->UpdateBattInfoField(*battery,"pomieszczenie",battery->room);
    db->UpdateBattInfoField(*battery,"typ baterii",battery->battType);

    QStringList people = db->MakeListFromMeas(DbHandler::PEOPLE,*battery,battery->measDate,battery->measResult);
    QStringList equip = db->MakeListFromMeas(DbHandler::EQUIP,*battery,battery->measDate,battery->measResult);;
    reportWidget->AddTable("db/"+measure->ReturnTableName());
    reportWidget->AddPlot("db/"+measure->ReturnPlotName());
    reportWidget->TakeInfoAbout(*battery,people,equip);
    reportWidget->resize(700,790);
    xbelTree->ItemInfoRefresh();
    this->show();
    reportWidget->show();
}
//================================================
void MainWindow::MeasuresBattLabelsClosed()
{
    this->show();
}
//================================================
void MainWindow::GenerateRaport(QListWidgetItem *item)
{
    QTreeWidgetItem *treeItem = xbelTree->currentItem();
    QTreeWidgetItem *treeItemParent = treeItem->parent();
    if(!treeItemParent){
        return;
    }
    BattInfo battery;
    battery.objectName = treeItemParent->text(0);
    battery.battName = treeItem->text(0);
    if(!battery.IsValid()){
        return;
    }
    QString listItemValue = item->text();
    QString date, result;
    //========================
    // wyznaczamy date i wynik
    {
        //int dateDelimiter = listItemValue.indexOf(QChar(' '));
        int resultDelimiter = listItemValue.lastIndexOf(QChar(' '));
        for(int i=0;i<resultDelimiter;i++){
            date.push_back(listItemValue.at(i));
        }
        for(int i=resultDelimiter+1;i<listItemValue.size();i++){
            result.push_back(listItemValue.at(i));
        }
    }
    /*qDebug()<<batteryObject;
    qDebug()<<batteryName;
    qDebug()<<date;
    qDebug()<<result;*/
    battery.measDate = date;
    battery.measResult = result;
    QStringList people = db->MakeListFromMeas(DbHandler::PEOPLE,battery,date,result);
    QStringList equip = db->MakeListFromMeas(DbHandler::EQUIP,battery,date,result);
    reportWidget->AddTable("db/"+db->GetTableName(battery.objectName,battery.battName,date,result));
    reportWidget->AddPlot("db/"+db->GetPlotName(battery.objectName,battery.battName,date,result));
    reportWidget->TakeInfoAbout(battery,people,equip);
    reportWidget->resize(700,790);
    reportWidget->show();
}

