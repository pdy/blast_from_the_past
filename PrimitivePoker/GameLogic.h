#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QVector>

class Card;
class CardSet;
class Deck;
class ComputerPlayer;

class GameLogic : public QObject
{
    Q_OBJECT
public:
    explicit GameLogic(QObject *parent = 0);
    virtual ~GameLogic();

signals:
    void WhenGameStarts(const CardSet &humanSet,const CardSet &computerSet);
    void CardsRequested(const QVector<const Card*> &requestedCards);

    void NumberOfCardsExchangedByComputer(unsigned short num);

    void GameFinished(const CardSet &computerSet, const QString &msg);


public slots:
    void Start();
    void GiveMeCards(unsigned short cardsCount);

    void Finish(const CardSet &humanSet);


private:
    void DisposeSets();

    Deck *_deck;

    CardSet *_flipsideSet;
    CardSet *_humanSet;
    CardSet *_computerSet;

    ComputerPlayer *_computerPlayer;
    
};

#endif // GAMELOGIC_H
