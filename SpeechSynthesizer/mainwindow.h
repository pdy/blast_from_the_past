#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QTextCodec>
#include <QtGui/QKeySequence>
#include "SyntCore.h"
#include "settingswindow.h"

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
    void  closeEvent(QCloseEvent*);
private slots:
    void OpenTxFile();
    void SaveTxFile();
    void Settings();

    void Speak();
    void Stop();
    void Pause(bool arg);
    void PauseButtonDisable();

private:
    Ui::MainWindow *ui;
    //SyntCore *core;
    SetWindow *setForm;
    bool setFormInitial;
    QTextCodec *codec;

    void CreateActions();
    void CreateMenus();
    QMenu *fileMenu;
    QMenu *settMenu;
    QAction *openAct;
    QAction *quitAct;
    QAction *saveAct;
    QAction *settAct;
};

#endif // MAINWINDOW_H
