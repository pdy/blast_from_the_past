#ifndef BATTERYLABEL_H
#define BATTERYLABEL_H

#include <QDialog>


namespace Ui{
    class BattLabel;
}

class BattInfo;
class QCloseEvent;

class BatteryLabel : public QDialog
{
    Q_OBJECT
public:
    BatteryLabel();
    ~BatteryLabel();
   // BatteryLabel(BattInfo &battery);

    void TakeBattery(BattInfo &battery);
    BattInfo *ReturnBattery();
protected:
    void closeEvent(QCloseEvent *);
signals:
    void ForwardButtonClicked();
    void ClosedWindow();
private slots:
    void ForwardButtonClick();
private:
    Ui::BattLabel *ui;
    QString currBattName;
    QString ConvertToString(int val);

    void FillForm(BattInfo &battery);
    void FlushForm();

};

#endif // BATTERYLABEL_H
