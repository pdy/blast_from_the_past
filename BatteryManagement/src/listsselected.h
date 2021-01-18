#ifndef LISTSSELECTED_H
#define LISTSSELECTED_H

#include <QDialog>
#include <QStringList>
#include <QCloseEvent>

namespace Ui{
    class ListsDialog;
}

class ListsSelected : public  QDialog
{
    Q_OBJECT
public:
    ListsSelected(QDialog *parent = 0);
    ~ListsSelected();
    void LoadAll();
    bool IsSourceFilesEmpty();
    void FlushFiles();
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void StreamToFile();
private:
    Ui::ListsDialog *ui;   
    void StreamTo(QString path,QStringList content);
    void FlushWidget();

};

#endif // LISTSSELECTED_H
