#ifndef CARDSET_H
#define CARDSET_H

#include <QVector>
#include <QMap>

#include "UtpPoker.h"

class Card;
class CardSet
{
public:
    struct FiveCards
    {
        const Card *card1;
        const Card *card2;
        const Card *card3;
        const Card *card4;
        const Card *card5;
    };

    CardSet(const Card &card1,const Card &card2, const Card &card3, const Card &card4, const Card &card5);

    UtpPoker::CardSystem GetCardSystem() const
    {
        return _cardSystem;
    }

    int GetPointsOfSystem() const
    {
        return _pointsOfSystem;
    }

    FiveCards GetCards() const
    {
        return _fiveCards;
    }

    QVector<const Card*> GetCardsVector() const
    {
        return _cardSet;
    }



    bool operator > (const CardSet &cardSet) const;
    bool operator < (const CardSet &cardSet) const;
    bool operator == (const CardSet &cardSet) const;

private: //methods
    int GetSumOfAllCards();
    void CountFigures();

    bool CheckIfAllCardsAreSameColor();
    unsigned short CountColor(UtpPoker::CardColor color);

    void ComputeCardSystemAndSystemPoints();

    bool IsSmallStraight();
    bool IsBigStraight();

    bool IsPair();
    bool IsTwoPair();
    bool IsThreeOfKind();
    bool IsFull();
    bool IsFourOfKind();


private: //variables
    UtpPoker::CardSystem _cardSystem;
    int _pointsOfSystem;
    struct PointsComputeHelper
    {
        UtpPoker::Figure fig1;
        UtpPoker::Figure fig2;
    }_pointsComputeHelper;

    QMap<UtpPoker::Figure,unsigned short> _figuresCount;

    bool _allSameColor;

    QVector<const Card*> _cardSet;
    FiveCards _fiveCards;
};

#endif // CARDSET_H
