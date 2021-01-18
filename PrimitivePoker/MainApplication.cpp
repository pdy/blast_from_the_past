#include "MainApplication.h"
#include "ui_mainapplication.h"

#include <QtGui>
#include <QtCore>

#include "Card.h"
#include "CardSet.h"
#include "CardView.h"
#include "GameLogic.h"
#include "UtpPoker.h"


MainApplication::MainApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplication)
{
    ui->setupUi(this);
    _scene = new QGraphicsScene(this);
    ui->graphicView->setScene(_scene);
    connect(ui->changeCardsButton,SIGNAL(pressed()),this,SLOT(OnExchangeCardsButton()));
    connect(ui->confirmExchangeButtn,SIGNAL(pressed()),this,SLOT(OnConfirmedExchangeButton()));
    connect(ui->notChangeCardsButton,SIGNAL(pressed()),this,SLOT(RequestFinishTheGame()));

    QBrush background(Qt::darkGreen);
    _scene->setBackgroundBrush(background);

    _gameLogic = new GameLogic();
    connect(ui->distributeButton,SIGNAL(pressed()),_gameLogic,SLOT(Start()));
    connect(_gameLogic,SIGNAL(WhenGameStarts(CardSet,CardSet)),this,SLOT(OnGameStart(CardSet,CardSet)));
    connect(_gameLogic,SIGNAL(NumberOfCardsExchangedByComputer(unsigned short)),this,SLOT(OnNumberOfCardsExchangedByComputer(unsigned short)));
    connect(_gameLogic,SIGNAL(CardsRequested(QVector<const Card*>)),this,SLOT(CardsForExchange(QVector<const Card*>)));
    connect(_gameLogic,SIGNAL(GameFinished(CardSet,QString)),this,SLOT(GameFinished(CardSet,QString)));

    SetPreDistributeState();

}
//======================================
MainApplication::~MainApplication()
{
    if(ui)
    {
        delete ui;
        ui = 0;
    }

    if(_scene)
    {
        delete _scene;
        _scene = 0;
    }

    if(_gameLogic)
    {
        delete _gameLogic;
        _gameLogic = 0;
    }

}
//============================================
void MainApplication::SetPreDistributeState()
{
    ui->distributeButton->setEnabled(true);
    ui->confirmExchangeButtn->setEnabled(false);
    ui->changeCardsButton->setEnabled(false);
    ui->notChangeCardsButton->setEnabled(false);
    SetInfoText("Kliknij 'Rozdaj'");
}
//=======================================
void MainApplication::OnGameStart(const CardSet &humanSet, const CardSet &computerSet)
{
    //_humanCards = humanSet.GetCardsVector();
    //_computerCards = computerSet.GetCardsVector();

    InitSetsViews(humanSet.GetCardsVector(),computerSet.GetCardsVector());
    SetAfterDistributeState();
}
//=======================================
void MainApplication::InitSetsViews(const QVector<const Card *> &humanCards, const QVector<const Card *> &computerCards)
{
    if(humanCards.isEmpty() || computerCards.isEmpty())
    {
        //QMessageBox::warning(0,"Nie ma kart do ry")
        return;
    }

    const qreal HUMAN_Y = -60;
    const qreal COMPUTER_Y = 60;
    const qreal START_X = -250;
    const qreal DIFF = 110;

    qreal x = START_X;

    for(int i=0;i<computerCards.size();++i)
    {
        i != 0 ? x += DIFF : x += 0;
        _computerCardsView.push_back(new CardView(computerCards.at(i),x,COMPUTER_Y));
        _scene->addItem(_computerCardsView[i]);
    }


    x = START_X;
    for(int i=0;i<humanCards.size();++i)
    {
        //
        i != 0 ? x += DIFF : x += 0;
        _humanCardsView.push_back( new CardView(humanCards.at(i),x,HUMAN_Y));
        _scene->addItem(_humanCardsView[i]);

        //qDebug()<< "x="+QString::number(_humanCardsView[i]->x()) + "; y="+QString::number(_humanCardsView[i]->y());
    }
}
//=======================================
void MainApplication::SetAfterDistributeState()
{
    ui->distributeButton->setEnabled(false);
    ui->confirmExchangeButtn->setEnabled(false);
    ui->changeCardsButton->setEnabled(true);
    ui->notChangeCardsButton->setEnabled(true);
    SetInfoText("Czy chcesz wymieniac karty");
}
//=======================================
void MainApplication::OnNumberOfCardsExchangedByComputer(unsigned short num)
{
    SetInfoText("Komputer wymienil kart " + QString::number(num));
}

//===========================================
void MainApplication::DisposeSetsView()
{
    for(int i=0;i<_computerCardsView.size();++i)
    {
        Dispose(_computerCardsView.at(i));
    }
    _computerCardsView.clear();

    for(int i=0;i<_humanCardsView.size();++i)
    {
        Dispose(_humanCardsView.at(i));
    }
    _humanCardsView.clear();
}
//===========================================
void MainApplication::Dispose(CardView *cardView)
{
    if(cardView)
    {
        delete cardView;
        cardView = 0;
    }
}
//============================================
void MainApplication::SetInfoText(const QString &info)
{
    ui->infoLabel->setText("Info:\n" + info);
}
//=============================================
void MainApplication::OnExchangeCardsButton()
{
    SetExchangeCardsState();
    for(int i=0;i<_humanCardsView.size();++i){
        _humanCardsView.at(i)->SetSelectAble(true);
    }
}
//=============================================
void MainApplication::SetExchangeCardsState()
{
    ui->distributeButton->setEnabled(false);
    ui->confirmExchangeButtn->setEnabled(true);
    ui->changeCardsButton->setEnabled(false);
    ui->notChangeCardsButton->setEnabled(false);
    SetInfoText("Kliknij na karty ktore chcesz wymienic");
}
//=============================================
void MainApplication::OnConfirmedExchangeButton()
{
    unsigned short exchangeCardsCount = 0;
    for(int i=0;i<_humanCardsView.size();++i)
    {
        CardView *view = _humanCardsView.at(i);
        if(view->IsSelected()){
            ++exchangeCardsCount;
        }
    }

    if(exchangeCardsCount > 0){
        _gameLogic->GiveMeCards(exchangeCardsCount);
    }
    RequestFinishTheGame();
}
//=============================================
void MainApplication::RequestFinishTheGame()
{
    QVector<const Card*> cards;
    for(int i=0;i<_humanCardsView.size();++i){
        cards.push_back(_humanCardsView.at(i)->GetCard());
    }

    CardSet humanSet(*cards.at(0),*cards.at(1),*cards.at(2),*cards.at(3),*cards.at(4));

    _gameLogic->Finish(humanSet);
}
//=============================================
void MainApplication::CardsForExchange(const QVector<const Card *> &requestedCards)
{
    QList<const Card*> tmpList = requestedCards.toList();
    for(int i=0;i<_humanCardsView.size();++i)
    {
        CardView &view = *_humanCardsView.at(i);
        if(view.IsSelected())
        {
            view.SetSelected(false);
            view.RePaint(tmpList.first());
            tmpList.removeFirst();
        }
    }
}
//============================================
void MainApplication::GameFinished(const CardSet &computerSet, const QString &msg)
{
    QList<const Card*> newSet = computerSet.GetCardsVector().toList();
    for(int i=0;i<_computerCardsView.size();++i)
    {
        CardView &view = *_computerCardsView.at(i);
        view.RePaint(newSet.first());
        newSet.removeFirst();
    }

    QMessageBox::information(0,"Koniec rozdania, ",msg);

    DisposeSetsView();
    SetPreDistributeState();
}
