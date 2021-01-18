#ifndef DECK_H
#define DECK_H

#include <QPair>
#include <QList>
#include <QVector>

class Card;
class CardSet;

class Deck
{
public:
    Deck();
    virtual ~Deck();

    QPair<CardSet*,CardSet*> Distribute();

    QVector<const Card*> GetCards(unsigned short cardsCount);


private:
    void Shuffle();

    QVector<const Card*> _cardsList;
    QList<const Card*> _shuffledList;

};

#endif // DECK_H
