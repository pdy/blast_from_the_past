#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui
{
    class ConfigDialog;
    class MeasSetWidget;
    class RepData;
}

class QCloseEvent;
class QListWidgetItem;
class QTextCodec;

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
public slots:
    void ExecWithReport();
    void ExecWithMeasure();

protected:
    void changeEvent(QEvent *e);
private slots:
    void WidgetsChange(QListWidgetItem *current,QListWidgetItem *previous);

private:
    Ui::ConfigDialog *ui;
    void CreateIcons();


};

//=========================================
//  Klasy "stron"
//=========================================

//==============================
// ustawienia pomiarów
class MeasSet : public QWidget
{
    Q_OBJECT
public:
    MeasSet(QWidget *parent = 0);
    ~MeasSet();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
private slots:
    void Save();
    void DefaultSettings();

    void OnMeasIntervalChanged(int val);

private:
    Ui::MeasSetWidget *ui;


    int ComputeMax(int valueOfMeasInterval);
    void LoadSettings();
    QString ConvertToString(int val);
   // int maxCellMeasTime;
    int defaultMaxCellMeasTime;
};

//==============================
// dane do raportu
class ReportSets : public QWidget
{
    Q_OBJECT
public:
    ReportSets(QWidget *parent=0);
    ~ReportSets();
private slots:
    void AddPerson();
    void AddEquip();

    void EditPersonLine();
    void EditEquipLine();

    void DeletePersonLine();
    void DeleteEquipLine();

    void ChangePic();
    void SetDefaultPic();
private:
    enum CHOOSELIST
    {
        PERSONS,
        EQUIPMENT,
        ALL
    };
    Ui::RepData *ui;
    QTextCodec *codec;
    void LoadResource();
    void LoadImage();
    void StreamToFiles(CHOOSELIST whichList);
    void StreamToFiles(QString path,QStringList content);

};

#endif // CONFIGDIALOG_H
