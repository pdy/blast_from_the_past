#ifndef XBELTREE_H
#define XBELTREE_H

#include <QDomDocument>
#include <QHash>
#include <QIcon>
#include <QTreeWidget>
#include <QString>

class QAction;
class QTextCodec;
class QContextMenuEvent;
class DbHandler;
class BattInfo;

class XbelTree : public QTreeWidget
{
    Q_OBJECT

public:
    XbelTree(QWidget *parent = 0);
    ~XbelTree();

    bool Read(QString sourcePath);
    bool Write(QString destinyPath);

    bool WasModified(){return treeModified;}
    void Save();
    void DoNotSave();
    bool IsNull(){return domDocument.isNull();}
    bool GenerateNewStruct();
    void SetHeaderTitle(QString title);
    QString GetHeaderTitle(){return treeTitle;}
    QDomElement GetRootNode();
    QString IdGenerate();
    void ItemInfoRefresh(){emit ClickedTreeItem(this->currentItem(),0);}

signals:
    void MakeMeasure(BattInfo &battery);
    void ClickedTreeItem(QTreeWidgetItem *,int);
    void DatabaseId(QString id);

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void keyPressEvent( QKeyEvent *e );

public slots:
    void AddObjSlot();
    void AddBattSlot();
    void DeleteNode();

    void MoveItemUp();
    void MoveItemDown();

    void MakeMeasureSlot();

private slots:
    void UpdateDomElement(QTreeWidgetItem *item, int column);
    void SetItemMarked(QTreeWidgetItem *item,int column);
    void OnSelectionChanged();

    void SaveItemExpand(QTreeWidgetItem *item);
    void SaveItemCollapse(QTreeWidgetItem *item);

private:
    DbHandler *dataBase;
    void AddToDatabase(QString objectName, QString battName);
    void UpdateDbBattName(QString objectName,QString oldName, QString newName);
    void UpdateDbObjectName(QString oldName,QString newName);
    void DeleteFromBase(QDomElement &el);

    QString treeTitle;
    QDomElement elemToSelect;
    bool treeModified;
    bool addBatt;
    bool addObj;
    bool addNew;
    bool byItemMove;
    bool markItem;
    void Refresh();
    int CountNames(QString name);
    QString ConvertToString(long val);
    QDomElement AddObject(QString name,QDomNode &parent);
    QDomElement AddBatt(QString name, QDomNode &parent);

    bool PassName(QTreeWidgetItem *item, bool listSwitcher=0);
    void ParseFolderElement(const QDomElement &element,QTreeWidgetItem *parentItem = 0);
    QTreeWidgetItem *CreateItem(const QDomElement &element,QTreeWidgetItem *parentItem = 0);
    //QString IdGenerate();


    bool IsObject(QDomNode &el);
    QDomElement CurrentItemMarked(){return currentElMarked;}
    QDomElement currentElMarked;

    QString documentId;
    QDomDocument domDocument;
    QHash<QTreeWidgetItem *, QDomElement> domElementForItem;

    QIcon folderIcon;

    QTextCodec *codec;
    void CreateActions();
    QAction *addObjAct;
    QAction *addBattAct;
    QAction *moveBattUpAct;
    QAction *moveBattDownAct;
    QAction *deleteNodeAct;
    QAction *makeMeasureAct;
};

#endif
