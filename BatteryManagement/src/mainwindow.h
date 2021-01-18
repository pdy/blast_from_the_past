#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QToolBar;
class QMenu;
class QAction;
class QTextCodec;
class QCloseEvent;
class QLabel;
class QTreeWidgetItem;
class QListWidgetItem;
class XbelTree;
class BattInfo;
class DbHandler;
class BatteryLabel;
class Measure;
class ConfigDialog;
class ReportWidget;
class ListsSelected;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
private slots:
    void NewStruct();
    void Open();
    void Save();
    void SaveAs();

    void MoveUp();
    void MoveDown();

    void NewBattery();
    void NewObject();

    void BattInfoLabels(QTreeWidgetItem *,int);

    void GoToBattLabel(BattInfo &battery);
    void GoToMeasures();
    void MeasuresFinished();
    void MeasuresBattLabelsClosed();

    void GenerateRaport(QListWidgetItem *item);

    void SetDatabaseId(QString id);

private:
    enum PrintMode
    {
        BATTERY,
        OBJECT
    };
    QMap<QLabel *,QLabel *> labels;
    void EraseValLabels();
    void KeyLabelsVisible(bool visible);
    void ValLabelsText(BattInfo &batt,PrintMode mode);


    Ui::MainWindow *ui;
    XbelTree *xbelTree;
    BatteryLabel *battLabel;
    Measure *measure;
    ListsSelected *listsSelected;
    ConfigDialog *configDialog;
    ReportWidget *reportWidget;
    DbHandler *db;
    QTextCodec *codec;
    QString currSobTreePath;

    void CreateActions();
    void CreateMenus();
    void CreateToolBars();

    QToolBar *fileToolBar;
    QToolBar *itemMoveToolBar;
    QToolBar *addItemsToolBar;

    QAction *moveUpAct;
    QAction *moveDownAct;
    QAction *makeMeasAct;

    QAction *saveAct;
    QAction *saveAsAct;
    QAction *openAct;
    QAction *newAct;
    QAction *exitAct;

    QAction *measSetAct;
    QAction *reportSetAct;

    QAction *addBattAct;
    QAction *addObjAct;

    QMenu *fileMenu;
    QMenu *settingsMenu;
};

#endif // MAINWINDOW_H
