#include <QDebug>
#include <QMenu>
#include <QTextCodec>
#include <QAction>
#include <QFile>
#include <QMessageBox>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QKeyEvent>

#include <sstream>
#include <string>
#include <ctime>

#include "xbeltree.h"
#include "dbhandler.h"

XbelTree::XbelTree(QWidget *parent)
    : QTreeWidget(parent)
{
    dataBase=new DbHandler;
    addBatt=0;
    addObj=0;
    addNew=0;
    byItemMove=0;
    markItem=0;
    header()->setResizeMode(QHeaderView::Stretch);
    //setHeaderLabels(labels);
    SetHeaderTitle(tr("Brak struktury."));
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    //bookmarkIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(SetItemMarked(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(SaveItemExpand(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(SaveItemCollapse(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(OnSelectionChanged()));

    codec=QTextCodec::codecForLocale();
    CreateActions();
    treeModified=0;
  //  setFocusPolicy(Qt::ClickFocus);
    this->setSelectionMode(QTreeView::SingleSelection);


}
//=====================================================================================
XbelTree::~XbelTree()
{
    delete dataBase;
}

//=====================================================================================
bool XbelTree::Read(QString srcPath)
{
    QFile *device=new QFile(srcPath);
    if(!device->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(window(),"File",
                                 "No such file in directory.",0,0);
        return false;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn))
    {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        device->close();
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "xbel")
    {
        QMessageBox::information(window(), tr("SOB dokument"),
                                 codec->toUnicode("Plik nie jest prawid³ow¹ struktur¹ SOB."));
        device->close();
        return false;
    }
    else if (root.hasAttribute("version")
               && root.attribute("version") != "1.0")
    {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("The file is not an XBEL version 1.0 "
                                    "file."));
        device->close();
        return false;
    }
    device->close();
    clear();

    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
               this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));

    QDomElement child = root.firstChildElement("folder");
    while (!child.isNull())
    {
        ParseFolderElement(child);
        child = child.nextSiblingElement("folder");
    }

    child = root.firstChildElement("id");
    if(child.isNull())
    {
        QMessageBox::information(window(),"SOB dokument",
                                 codec->toUnicode("Za³adowana struktura nie jest kompatybilna z obecn¹ wersj¹ programu."));
        clear();
        return false;
    }
    documentId=child.attribute("val");
    QFile file("db/"+documentId+".sqlite3");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(window(),"Baza danych",
                                 codec->toUnicode("Nie wykryto bazy danych dla za³adowanego dokumentu SOB. \n"
                                                  "Jeœli nast¹pi³o przypadkowe usuniêcie przywróæ z kosza plik:\n "
                                                  +documentId.toLocal8Bit()+".sqlite3\n"));
        clear();
        return false;
    }
    emit DatabaseId(documentId);
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
            this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));
    treeModified=0;

    QString name;
    int begIndex=srcPath.lastIndexOf("/");
    ++begIndex;
    while(begIndex!=srcPath.size())
    {
        name.push_back(srcPath[begIndex]);
        ++begIndex;
    }

    SetHeaderTitle(name);
    return true;
}
//=====================================================================================
bool XbelTree::Write(QString destinyPath)
{
    const int IndentSize = 4;
    QFile *device=new QFile(destinyPath);
    if(!device->open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(window(),"SOB dokument",
                                 codec->toUnicode("Nieprawid³owa œcie¿ka."),0,0);
        return false;
    }
    QTextStream out(device);
    domDocument.save(out, IndentSize);
    device->close();
    return true;
}
//=====================================================================================
void XbelTree::Save()
{
    treeModified=0;
    dataBase->SaveChanges();
}
//=====================================================================================
void XbelTree::DoNotSave()
{
    dataBase->DoNotSaveChanges();
}

//=====================================================================================
void XbelTree::UpdateDomElement(QTreeWidgetItem *item, int column)
{
    if(PassName(item))
    {
        QDomElement element = domElementForItem.value(item);
        if (!element.isNull())
        {
            if (column == 0)
            {
                QDomElement oldTitleElement = element.firstChildElement("title");
                QDomElement newTitleElement = domDocument.createElement("title");

                QDomText newTitleText;
                newTitleText = domDocument.createTextNode(item->text(0));
                newTitleElement.appendChild(newTitleText);
                element.replaceChild(newTitleElement, oldTitleElement);
                //qDebug()<<oldTitleElement.text();
                if(item->parent())//jest bateria
                {
                    UpdateDbBattName(item->parent()->text(0),oldTitleElement.text(),item->text(0));
                }
                else
                {
                    UpdateDbObjectName(oldTitleElement.text(),item->text(0));
                }
            }
            else
            {
                if (element.tagName() == "bookmark"){
                    element.setAttribute("href", item->text(1));
                }
            }
        }

    }
    else
    {
        QTreeWidgetItem *parent=item->parent();
        if(parent)//item jest bateria
        {
            QMessageBox::information(window(),"SOB dokument",
                                     codec->toUnicode("Bateria o podanej nazwie ju¿ istnieje."));
            markItem=1;
            elemToSelect=domElementForItem.value(item);
            Refresh();
            markItem=0;
        }
        else
        {
            QMessageBox::information(window(),"SOB dokument",
                                     codec->toUnicode("Obiekt o podanej nazwie ju¿ istnieje."));
            addObj=1;
            elemToSelect=domElementForItem.value(item);
            Refresh();
            addObj=0;
        }



    }
}
//=====================================================================================
bool XbelTree::PassName(QTreeWidgetItem *item, bool listSwitcher)
{
    if(item->text(0)==""){
        return false;
    }

    QTreeWidgetItem *parent=item->parent();
    if(parent)//item jest "bateria"
    {

        int itemIndex=parent->indexOfChild(item);
        for(int i=0;i<parent->childCount();i++)
        {
            if(i==itemIndex){
                continue;
            }

            if(item->text(0) == parent->child(i)->text(0)){
                return false;
            }
        }
        return true;
    }
    else
    {
        //====================================================================
        // Najpierw sprawdzamy po samych obiektach
        QList<QTreeWidgetItem *> list=findItems(item->text(0),Qt::MatchExactly);
        qDebug() <<"lista: "<< list.size();
        if(!listSwitcher)
        {
            //wartosc gdy edytujemy obiekt
            if(list.size()>1){
                return false;
            }
        }
        else
        {
            //wartosc dla dodawania obiektu
            if(list.size()>=1){
                return false;
            }
        }

        //====================================================================
        //Teraz przeszukujemy zawartosc obiektow
        QTreeWidgetItem *rootItem=invisibleRootItem();
        QTreeWidgetItem *rootChild;
        for(int i=0;i<rootItem->childCount();i++)
        {
            rootChild=rootItem->child(i);
            for(int i=0;i<rootChild->childCount();i++)
            {
                if(item->text(0) == rootChild->child(i)->text(0)){
                    return false;
                }
            }

        }

    }
    return true;
}
//=====================================================================================
void XbelTree::SetItemMarked(QTreeWidgetItem *item, int column)
{
    currentElMarked=domElementForItem.value(item);
    if(!byItemMove){
        emit ClickedTreeItem(item,column);
    }
    else{
        byItemMove=0;
    }
}
//=====================================================================================
void XbelTree::OnSelectionChanged()
{
    currentElMarked=domElementForItem.value(this->currentItem());
    if(!addBatt && !addObj)
    {
        if(!byItemMove)
        {
            //currentElMarked=domElementForItem.value(this->currentItem());
            emit ClickedTreeItem(this->currentItem(),0);
        }
       /* else{
            byItemMove=0;
        }*/
    }
}

//=====================================================================================

void XbelTree::ParseFolderElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{

    QTreeWidgetItem *item = CreateItem(element, parentItem);

    QString title = element.firstChildElement("title").text();
    if (title.isEmpty())
        title = QObject::tr("Folder");

    item->setFlags(item->flags() | Qt::ItemIsEditable );
    item->setIcon(0, folderIcon);
    item->setText(0, title);


    disconnect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(SaveItemExpand(QTreeWidgetItem*)));
    disconnect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(SaveItemCollapse(QTreeWidgetItem*)));


    bool folded = (element.attribute("folded") != "no");
    setItemExpanded(item, !folded);
    if(addObj && elemToSelect.text() == element.text()){
        editItem(item,0);
    }
    else if(addNew){
        editItem(item,0);
    }


    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(SaveItemExpand(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(SaveItemCollapse(QTreeWidgetItem*)));


    QDomElement child = element.firstChildElement();
    while (!child.isNull())
    {
        if (child.tagName() == "folder") {
            ParseFolderElement(child, item);
        }
        else if (child.tagName() == "bookmark")
        {


            QTreeWidgetItem *childItem = CreateItem(child, item);

            QString title = child.firstChildElement("title").text();
//            if (title.isEmpty())
 //               title = QObject::tr("Folder");

            childItem->setFlags(item->flags() | Qt::ItemIsEditable);
            childItem->setIcon(0, QIcon(":/images/akumulator.PNG"));
            childItem->setText(0, title);
            if((addBatt||markItem) && elemToSelect.text() == child.text()
                && elemToSelect.parentNode().toElement().text() == child.parentNode().toElement().text())
            {

                editItem(childItem,0);
                if(addBatt){
                    AddToDatabase(childItem->parent()->text(0),childItem->text(0));
                }
            }
            childItem->setText(1, child.attribute("href"));
        }
        /*else if (child.tagName() == "separator")
        {
            /*QTreeWidgetItem *childItem = createItem(child, item);
            childItem->setFlags(item->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEditable));
            childItem->setText(0, QString(30, 0xB7));
            qDebug()<<child.attribute("val");
        }*/

        child = child.nextSiblingElement();
    }
}
//=====================================================================================
QTreeWidgetItem *XbelTree::CreateItem(const QDomElement &element,
                                      QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item;
    if (parentItem) {
        item = new QTreeWidgetItem(parentItem);
    } else {
        item = new QTreeWidgetItem(this);
    }
    if(elemToSelect.text() == element.text()
        && elemToSelect.parentNode().toElement().text() == element.parentNode().toElement().text()){
        item->setSelected(true);
    }


    domElementForItem.insert(item, element);
    return item;
}
//=====================================================================================
bool XbelTree::GenerateNewStruct()
{

    clear();
    domDocument.clear();
    SetHeaderTitle("Nowa struktura.");

    QDomElement docId=domDocument.createElement("id");
    QString idArg=IdGenerate();
    documentId=idArg;
    docId.setAttribute("val",idArg);

    QDomElement elem=domDocument.createElement("xbel");
    elem.setAttribute("version","1.0");
    domDocument.appendChild(elem);
    elem.appendChild(docId);

    AddObject("",elem);

    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
               this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));
    addNew=1;
    Refresh();
    addNew=0;
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
            this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));


    return true;
}
//=====================================================================================
QString XbelTree::IdGenerate()
{
    time_t rawtime;   
    time(&rawtime);
    return ConvertToString(rawtime);
}

//=====================================================================================
void XbelTree::SetHeaderTitle(QString title)
{
   QStringList labels;
   labels << title;
   setHeaderLabels(labels);
   treeTitle=labels.value(0);
}

//=====================================================================================
QDomElement XbelTree::AddObject(QString name, QDomNode &parent)
{
    QDomElement elem=domDocument.createElement("folder");
    elem.setAttribute("folded","no");
    QDomElement elemTitle=domDocument.createElement("title");
    QDomText txt;
    if(name==""){
         txt=domDocument.createTextNode("obiekt");
    }
    else{
        txt=domDocument.createTextNode(name);
    }
    elemTitle.appendChild(txt);
    elem.appendChild(elemTitle);
    parent.appendChild(elem);
    treeModified=1;
    return elem;
}
//=====================================================================================
QDomElement XbelTree::AddBatt(QString name, QDomNode &parent)
{
    QDomElement elem=domDocument.createElement("bookmark");

    QDomElement elemTitle=domDocument.createElement("title");

    QDomText txt;
    if(name==""){
         txt=domDocument.createTextNode("");
    }
    else{
        txt=domDocument.createTextNode(name);
    }
    elemTitle.appendChild(txt);

    elem.appendChild(elemTitle);
    parent.appendChild(elem);

    treeModified=1;
    return elem;
}

//=====================================================================================
void XbelTree::AddObjSlot()
{
    QDomElement elem;
    /*if(!currentElMarked.isNull())
    {
         elem=CurrentItemMarked();
         if(!IsObject(elem)){
             elem=elem.parentNode().toElement();
         }
    }
    else{
        elem=GetRootNode();
    }*/

    QString objName="obiekt";
    //elem.clear();
    int count=CountNames(objName);

    if(count>0){
        objName+=ConvertToString(count);
    }

    bool ok=0;

    QTreeWidgetItem *item=new QTreeWidgetItem;
    item->setText(0,objName);
    ok=PassName(item,1);

    while(!ok)
    {

        ++count;
        objName+=ConvertToString(count);

        item->setText(0,objName);
        ok=PassName(item);

    }

    addObj=1;
    elem=GetRootNode();
    elemToSelect=AddObject(objName,elem);
    Refresh();
    addObj=0;
    //this->show();
    currentElMarked.clear();

}
//=====================================================================================
void XbelTree::AddBattSlot()
{
    QDomElement elem;
    if(!currentElMarked.isNull()){
         elem=CurrentItemMarked();
         if(!IsObject(elem)){
             elem=elem.parentNode().toElement();
         }
    }
    else{
        //elem=GetRootNode();
        return;
    }
    QString battName="bateria";

    int count=CountNames(battName);

    if(count>0){
        battName+=ConvertToString(count);
    }

    bool ok=0;

    QTreeWidgetItem *item=new QTreeWidgetItem();
    item->setText(0,battName);
    ok=PassName(item);

    while(!ok)
    {

        ++count;
        battName+=ConvertToString(count);

        item->setText(0,battName);
        ok=PassName(item);

    }

    addBatt=1;
    elemToSelect=AddBatt(battName,elem);
    Refresh();
    currentElMarked.clear();
    addBatt=0;
}
//=====================================================================================
void XbelTree::MoveItemDown()
{
    QDomElement elem;
    if(!currentElMarked.isNull()){
         elem=CurrentItemMarked();
    }
    else{
        return;
    }

    QDomNode parent=elem.parentNode();
    parent.insertAfter(elem,elem.nextSibling());
    elemToSelect=elem;
    byItemMove=1;
    Refresh();
    currentElMarked.clear();
    treeModified=1; 
    emit itemClicked(domElementForItem.key(elem),0);

}
//=====================================================================================
void XbelTree::MoveItemUp()
{
    QDomElement elem;
    if(!currentElMarked.isNull()){
         elem=CurrentItemMarked();
    }
    else{
        return;
    }

    QDomNode parent=elem.parentNode();

   // if(elem.text() != elem.parentNode().firstChild().toElement().text())
    //{
        parent.insertBefore(elem,elem.previousSibling());
        elemToSelect=elem;
        byItemMove=1;
        Refresh();     
        currentElMarked.clear();
        treeModified=1;
        //this->setCurrentItem(domElementForItem.key(elem),0);
       // byItemMove=1;
        emit itemClicked(domElementForItem.key(elem),0);
    //}



}

//=====================================================================================
void XbelTree::DeleteNode()
{
    QDomElement elem;
    if(!currentElMarked.isNull()){
         elem=CurrentItemMarked();
    }
    else{
        return;
    }
    DeleteFromBase(elem);
    QDomNode parent=elem.parentNode();
    parent.removeChild(elem);

    Refresh();
    //this->show();
    currentElMarked.clear();
    treeModified=1;
}

//=====================================================================================
QDomElement XbelTree::GetRootNode()
{ 
    QDomElement el=domDocument.documentElement();
    return el;
}
//=====================================================================================
void XbelTree::Refresh()
{

    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
               this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));
    disconnect(this,SIGNAL(itemSelectionChanged()),this,SLOT(OnSelectionChanged()));

    clear();
    QDomElement root = domDocument.documentElement();


    QDomElement child = root.firstChildElement("folder");
    while (!child.isNull()) {
        ParseFolderElement(child);
        child = child.nextSiblingElement("folder");
    }
    elemToSelect.clear();

    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(OnSelectionChanged()));
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
            this, SLOT(UpdateDomElement(QTreeWidgetItem *, int)));

}
//=====================================================================================
void XbelTree::contextMenuEvent(QContextMenuEvent *event)
{
    //qDebug()<<this->CurrentItemMarked().text();
    QString headerLabel=this->GetHeaderTitle();
    if(headerLabel=="Brak struktury."
       || headerLabel=="")
    {
        return;
    }
    QMenu menu;

    menu.addAction(addObjAct);
    menu.addAction(addBattAct);
    menu.addSeparator();
    menu.addAction(deleteNodeAct);

    menu.addSeparator();

    menu.addAction(moveBattUpAct);
    menu.addAction(moveBattDownAct);

    menu.addSeparator();
    menu.addAction(makeMeasureAct);

    menu.exec(event->globalPos());


}
//=====================================================================================
void XbelTree::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right){
        e->ignore();
    }
    else{
        QTreeWidget::keyPressEvent(e);
    }
}

//=====================================================================================
void XbelTree::CreateActions()
{
    addObjAct=new QAction("Nowy Obiekt",this);
    connect(addObjAct,SIGNAL(triggered()),this,SLOT(AddObjSlot()));

    addBattAct=new QAction("Nowa Bateria",this);
    connect(addBattAct,SIGNAL(triggered()),this,SLOT(AddBattSlot()));

    deleteNodeAct=new QAction(codec->toUnicode("Usuñ"),this);
    connect(deleteNodeAct, SIGNAL(triggered()),this,SLOT(DeleteNode()));

    moveBattUpAct=new QAction(codec->toUnicode("Przesuñ w górê"),this);
    connect(moveBattUpAct,SIGNAL(triggered()),this,SLOT(MoveItemUp()));

    moveBattDownAct=new QAction(codec->toUnicode("Przesuñ w dó³"),this);
    connect(moveBattDownAct,SIGNAL(triggered()),this,SLOT(MoveItemDown()));

    makeMeasureAct=new QAction(codec->toUnicode("Wykonaj pomiar"),this);
    connect(makeMeasureAct,SIGNAL(triggered()),this,SLOT(MakeMeasureSlot()));
}
//=====================================================================================
bool XbelTree::IsObject(QDomNode &el)
{
    if(el.nodeName()=="folder"){
        return true;
    }
    return false;
}
//=====================================================================================
void XbelTree::SaveItemExpand(QTreeWidgetItem *item)
{
    QDomElement elem=domElementForItem.value(item);
    QDomNode parent=elem.parentNode();
    QDomElement newElem=elem.cloneNode().toElement();
    newElem.setAttribute("folded","no");
    parent.replaceChild(newElem,elem);
    Refresh();
}
//=====================================================================================
void XbelTree::SaveItemCollapse(QTreeWidgetItem *item)
{
    QDomElement elem=domElementForItem.value(item);
    QDomNode parent=elem.parentNode();
    QDomElement newElem=elem.cloneNode().toElement();
    newElem.setAttribute("folded","yes");
    parent.replaceChild(newElem,elem);
    Refresh();
}
//=====================================================================================
void XbelTree::MakeMeasureSlot()
{
    if(GetHeaderTitle() == "Brak struktury."){
        return;
    }
    QDomElement element = CurrentItemMarked();
    if(IsObject(element)){
        return;
    }
    if(element.isNull())
    {
        QMessageBox::warning(this,"SOB dokument",
                             codec->toUnicode("Zaznacz lub dokoñcz edycjê elementu."));
        return;
    }
    if(GetHeaderTitle() == "Nowa struktura.")
    {
        QMessageBox::information(this,"Nie zachowano nowej struktury.",
                                 codec->toUnicode("Zachowaj stworzon¹ struktur¹ przed przyst¹pieniem do pomiarów."));
        return;
    }
    if(treeModified)
    {
        QMessageBox::information(this,"Nie zachowano zmian w strukturze.",
                                 codec->toUnicode("Zachowaj zmiany w obecnej strukturze przed przyst¹pieniem do pomiarów."));
        return;

    }

    QString object = element.parentNode().toElement().firstChildElement("title").text();
    QString battName = element.firstChildElement("title").text();
    BattInfo battery;
    battery=dataBase->GetBattInfo(object,battName);
    emit MakeMeasure(battery);

}

//=====================================================================================
int XbelTree::CountNames(QString name)
{
    int counter=0;

        //====================================================================
        // Najpierw sprawdzamy po samych obiektach
        QList<QTreeWidgetItem *> list=findItems(name,Qt::MatchContains);
        counter+=list.size();

        //====================================================================
        //Teraz przeszukujemy zawartosc obiektow
        QTreeWidgetItem *rootItem=invisibleRootItem();
        QTreeWidgetItem *rootChild;
        for(int i=0;i<rootItem->childCount();i++)
        {
            rootChild=rootItem->child(i);
            for(int i=0;i<rootChild->childCount();i++)
            {
                if(rootChild->child(i)->text(0).contains(name)){
                    ++counter;
                }
            }

        }


    return counter;
}
//=====================================================================================
QString XbelTree::ConvertToString(long val)
{
    std::ostringstream ossVal;
    ossVal << val;

    return QString(ossVal.str().c_str());
}


//=====================================================================================
//wrapery dla bazy danych
//=====================================================================================


void XbelTree::AddToDatabase(QString objectName, QString battName)
{
    dataBase->SetId(documentId);
    dataBase->RejectChangesMode();
    BattInfo batt;
    batt.objectName=objectName;
    batt.battName=battName;
    if(!dataBase->AddNewBatt(batt))
    {
        qDebug()<<"Bateria sie nie dodala";
    }
}
//=====================================================================================
void XbelTree::UpdateDbBattName(QString objectName,QString oldName, QString newName)
{
    dataBase->SetId(documentId);
    dataBase->RejectChangesMode();
    if(!dataBase->UpdateBattInfoField(oldName,objectName,"nazwa baterii",newName))
    {
        qDebug() << "Aktualizacja nazwy baterii dupa!";
    }
}
//=====================================================================================
void XbelTree::UpdateDbObjectName(QString oldName, QString newName)
{
    dataBase->SetId(documentId);
    dataBase->RejectChangesMode();
    if(!dataBase->UpdateBattInfoField("",oldName,"nazwa lokalizacji",newName))
    {
        qDebug()<<"Akutalizacja nazwy obiektu dupa!";
    }

}
//=====================================================================================
void XbelTree::DeleteFromBase(QDomElement &el)
{
    dataBase->SetId(documentId);
    dataBase->RejectChangesMode();
    if(IsObject(el))
    {
        QString titleEl=el.firstChildElement("title").text();
        //qDebug()<<titleEl.text();
        if(!dataBase->DeleteObject(titleEl))
        {
            qDebug()<<"kasowanie obiektu dupa";
        }
        return;
    }
    QString parentTitle=el.parentNode().firstChildElement("title").text();
    QString titleEl=el.firstChildElement("title").text();
    if(!dataBase->DeleteBatt(parentTitle,titleEl))
    {
        qDebug()<<"kasowanie baterii dupa";
    }
    //qDebug()<<el.firstChildElement("title").text();

}
