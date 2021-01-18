#include "ComputerPlayer.h"

#include "Card.h"
#include "CardSet.h"
#include "UtpPoker.h"
#include "Deck.h"

#include <ctime>

#include <QDebug>
#include <QString>

ComputerPlayer::ComputerPlayer()
{
    _possibleIdexes.push_back(0);
    _possibleIdexes.push_back(1);
    _possibleIdexes.push_back(2);
    _possibleIdexes.push_back(3);
    _possibleIdexes.push_back(4);
}
//===============================================
QPair<unsigned short, CardSet *> ComputerPlayer::ExchangeCards( CardSet &cardSet, Deck &deck)
{
    int howManyCards = Random(5);
    qDebug() << "Computer changed " + QString::number(howManyCards) + " cards.";

    if(howManyCards == 0)
    {
        return QPair<unsigned short, CardSet*>(0,&cardSet);
    }

    QList<int> indexes;
    QVector<int> tmpPossibleIndexes(_possibleIdexes);

    for(int i=0;i<howManyCards;++i)
    {
        int idx = Random(tmpPossibleIndexes.size()-1);

        QVector<int>::iterator it = tmpPossibleIndexes.begin() + idx;

        indexes.push_back(*it);
        tmpPossibleIndexes.erase(it);
    }

    //qDebug()<<indexes;

    QList<const Card*> replacingCards = deck.GetCards(howManyCards).toList();

    if(replacingCards.isEmpty())
    {
        return QPair<unsigned short, CardSet*>(0,&cardSet);
    }

    QVector<const Card*> cards = cardSet.GetCardsVector();
    QMap<int,const Card*> newSet;

    for(int i=0;i<howManyCards;++i)
    {
        int cardAt = indexes.first();
        indexes.removeFirst();

        const Card *replacingCard = replacingCards.first();
        replacingCards.removeFirst();

        newSet[cardAt] = replacingCard;
    }

    for(int i=0;i<cards.size();++i)
    {
        if(!newSet.contains(i)){
            newSet[i] = cards.at(i);
        }
    }
    return QPair<unsigned short, CardSet*>(howManyCards,new CardSet(*newSet[0],*newSet[1],*newSet[2],*newSet[3],*newSet[4]));
}
//==============================================
int ComputerPlayer::Random(int max)
{
    return rand() % (max + 1);
}
//===============================================
