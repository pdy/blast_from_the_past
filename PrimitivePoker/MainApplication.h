#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QMainWindow>
#include <QList>
#include <QMutex>

namespace Ui {
class MainApplication;
}

class Card;
class CardSet;
class CardView;
class GameLogic;
class QGraphicsScene;
class QGraphicsRectItem;

class MainApplication : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainApplication(QWidget *parent = 0);
    ~MainApplication();
    

private slots:
    void OnGameStart(const CardSet &humanSet,const CardSet &computerSet);
    void OnNumberOfCardsExchangedByComputer(unsigned short num);
    void OnExchangeCardsButton();
    void OnConfirmedExchangeButton();
    void RequestFinishTheGame();
    void CardsForExchange(const QVector<const Card*> &requestedCards);
    void GameFinished(const CardSet &computerSet, const QString &msg);

private:
    void InitSetsViews(const QVector<const Card*> &humanCards,const QVector<const Card*> &computerCards);
    void DisposeSetsView();
    void Dispose(CardView *cardView);
    void SetInfoText(const QString &info);

    void SetPreDistributeState();
    void SetAfterDistributeState();
    void SetExchangeCardsState();

    Ui::MainApplication *ui;
    QGraphicsScene *_scene;

    GameLogic *_gameLogic;

    QVector<CardView*> _humanCardsView;
    QVector<CardView*> _computerCardsView;

    //QVector<const Card*> _humanCards;
    //QVector<const Card*> _computerCards;


};

#endif // MAINAPPLICATION_H
