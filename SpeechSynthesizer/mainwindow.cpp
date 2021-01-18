#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filestream.h"
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pauseButton->setDisabled(1);
    connect(ui->playButton, SIGNAL(clicked()),this,SLOT(Speak()));
    connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(Stop()));
    connect(ui->pauseButton,SIGNAL(toggled(bool)),this,SLOT(Pause(bool)));
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(PauseButtonDisable()));


    codec=QTextCodec::codecForLocale();
    //Synth=new SyntSynth();
    CreateActions();
    CreateMenus();
    setFormInitial=0;



}
//==============================================
MainWindow::~MainWindow()
{

    destroy(1,1);
    delete ui;
    if(setFormInitial)
    {
        delete setForm;
    }
}
//==============================================
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
//==============================================
void MainWindow::closeEvent(QCloseEvent*)
{
    qApp->quit();
}
//==============================================
void MainWindow::Speak()
{
    QString temp=ui->textEdit->toPlainText();
    if(temp.length()>0)
    {
        int specCharsNum=temp.count(QChar('.'));
        specCharsNum+=temp.count(QChar('?'));
        specCharsNum+=temp.count(QChar('!'));
        temp=codec->fromUnicode(temp);

        std::string syntBuffer=temp.toStdString();

        if(specCharsNum>=2){
            ui->pauseButton->setDisabled(0);
        }
        else{
            ui->pauseButton->setDisabled(1);
        }
        Synth.SayIt(syntBuffer.c_str());

        if(Synth.TextEnded()){
            ui->pauseButton->setDisabled(1);
        }
    }
    else
    {
        QMessageBox::information(this,codec->toUnicode("Brak tekstu"), codec->toUnicode("WprowadŸ tekst to syntezy.") );
    }
}
//==============================================
void MainWindow::Stop()
{
    QString temp=ui->textEdit->toPlainText();
    if(temp.length()>0)// && playing)
    {
        Synth.Stop();
        ui->pauseButton->setDisabled(1);

    }

    /*else
    {
        QMessageBox msg;
        msg.setText(codec->toUnicode("WprowadŸ tekst do syntezy."));
        msg.exec();
    }*/
}
//==============================================
void MainWindow::Pause(bool arg)
{
    if(setFormInitial)
    {
        setForm->setDisabled(arg);
    }
    ui->playButton->setDisabled(arg);
    ui->stopButton->setDisabled(arg);
    ui->textEdit->setDisabled(arg);

    fileMenu->setDisabled(arg);
    settMenu->setDisabled(arg);

    Synth.Pause();
    if(Synth.TextEnded()){
        ui->pauseButton->setDisabled(1);
    }
}
//==============================================
void MainWindow::PauseButtonDisable()
{
    ui->pauseButton->setDisabled(1);
}

//==============================================
void MainWindow::OpenTxFile()
{
    QString temp=QFileDialog::getOpenFileName(this, tr("Open file"),
                                              "/home",
                                              tr("Text files(*.txt)"));
    temp=codec->fromUnicode(temp);
    std::string path=temp.toStdString();
    temp.clear();
    FileStream *stream=new FileStream();

    if(stream->Open(path.c_str(),FileStream::READ))
    {
        stream->StreamSeek(0,FileStream::END);
        long fileSize=stream->StreamTell();
        stream->StreamSeek(0,FileStream::BEGIN);
        char *fileBuffer=new char[fileSize];

        stream->Read(fileBuffer,fileSize);
        stream->Close();
        temp=codec->toUnicode(fileBuffer);

        delete[] fileBuffer;
        ui->textEdit->setText(temp);
    }
    else
    {
        QMessageBox msgBox;
        QString msg=codec->toUnicode("Nie wybrano ¿adnego pliku.");
        msgBox.setText(msg);
        msgBox.exec();
    }

    delete stream;
}
//==============================================
void MainWindow::SaveTxFile()
{

}
//==============================================
void MainWindow::Settings()
{
    if(!setFormInitial)
    {
        setForm=new SetWindow();
        setFormInitial=1;
    }
    setForm->show();

}

//==============================================
void MainWindow::CreateActions()
{
    openAct = new QAction(codec->toUnicode("&Otwórz..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(codec->toUnicode("Otwórz istniej¹cy plik  *.txt."));
    connect(openAct, SIGNAL(triggered()), this, SLOT(OpenTxFile()));

    quitAct=new QAction(codec->toUnicode("&Zakoñcz..."),this);
    quitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAct->setStatusTip(codec->toUnicode("Zakoñcz pracê z programem."));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));


    settAct=new QAction(tr("&Syntezy..."),this);
    settAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    settAct->setStatusTip(tr("Tutaj ustawisz parametry syntezera."));
    connect(settAct,SIGNAL(triggered()),this,SLOT(Settings()));
}
//==============================================
void MainWindow::CreateMenus()
{
    fileMenu=menuBar()->addMenu(tr("&Plik"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    settMenu=menuBar()->addMenu(tr("&Ustawienia"));
    settMenu->addAction(settAct);

}





























