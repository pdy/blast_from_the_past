#include "Deck.h"
#include "Card.h"
#include "CardSet.h"
#include "UtpPoker.h"

#include <QTime>
#include <QDebug>

#include <ctime>

Deck::Deck()
{
    _cardsList.push_back(new Card(UtpPoker::NINE,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::NINE,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::NINE,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::NINE,UtpPoker::HEARTS));

    _cardsList.push_back(new Card(UtpPoker::TEN,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::TEN,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::TEN,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::TEN,UtpPoker::HEARTS));

    _cardsList.push_back(new Card(UtpPoker::JACK,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::JACK,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::JACK,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::JACK,UtpPoker::HEARTS));

    _cardsList.push_back(new Card(UtpPoker::QUEEN,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::QUEEN,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::QUEEN,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::QUEEN,UtpPoker::HEARTS));

    _cardsList.push_back(new Card(UtpPoker::KING,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::KING,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::KING,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::KING,UtpPoker::HEARTS));

    _cardsList.push_back(new Card(UtpPoker::ACE,UtpPoker::SPADES));
    _cardsList.push_back(new Card(UtpPoker::ACE,UtpPoker::DIAMONDS));
    _cardsList.push_back(new Card(UtpPoker::ACE,UtpPoker::CLUBS));
    _cardsList.push_back(new Card(UtpPoker::ACE,UtpPoker::HEARTS));
}
//===========================================================
Deck::~Deck()
{
    QVector<const Card*>::iterator it = _cardsList.begin();
    for(;it != _cardsList.end();++it)
    {
        const Card *currCard = *it;
        if(currCard)
        {
            delete currCard;
            currCard = 0;
        }
    }

    _cardsList.clear();
}
//============================================================
void Deck::Shuffle()
{
    _shuffledList.clear();

    //srand(time(NULL));
    QVector<const Card*> tmpList(_cardsList);

    for(int i=0;i<_cardsList.size();i++)
    {
        int x=rand() % tmpList.size();
        //qDebug() << "Shulfed num: " + QString::number(x);

        QVector<const Card*>::iterator it = tmpList.begin() + x;

        _shuffledList.push_back(*it);
        tmpList.erase(it);

        //qDebug() << "Tmp size: " + QString::number(tmpList.size());
    }

    qDebug() << "Shuffled list:";
    /*for(int i=0 ;i<_shuffledList.size();++i){
        const Card *card = _shuffledList.at(i);
        qDebug() << "Card: " + UtpPoker::Description(card->GetFigure()) + " " + UtpPoker::Description(card->GetCardColor());
    }*/
}
//============================================================
QPair<CardSet *, CardSet *> Deck::Distribute()
{
    Shuffle();
    QVector<const Card*> firstSet;
    QVector<const Card*> secondSet;

    for(int i=0; i<10;++i)
    {
        if(i == 0 || i%2 == 0)
        {
            firstSet.push_back(_shuffledList.first());
            _shuffledList.removeFirst();
        }
        else
        {
            secondSet.push_back(_shuffledList.first());
            _shuffledList.removeFirst();
        }
    }

    qDebug() << "First set size: " + QString::number(firstSet.size());
    qDebug() << "Secon set size: " + QString::number(secondSet.size());

    qDebug() << "First set:";
    for(int i=0 ;i<firstSet.size();++i)
    {
        const Card *card = firstSet.at(i);
        qDebug() << UtpPoker::Description(card->GetFigure()) + " " + UtpPoker::Description(card->GetCardColor());
    }

    qDebug() << "Secon set:";
    for(int i=0 ;i<secondSet.size();++i)
    {
        const Card *card = secondSet.at(i);
        qDebug() << UtpPoker::Description(card->GetFigure()) + " " + UtpPoker::Description(card->GetCardColor());
    }

    return QPair<CardSet*,CardSet*>(new CardSet(*firstSet.at(0),*firstSet.at(1),*firstSet.at(2),*firstSet.at(3),*firstSet.at(4))
                                    , new CardSet(*secondSet.at(0),*secondSet.at(1),*secondSet.at(2),*secondSet.at(3),*secondSet.at(4)));
}
//===========================================================
QVector<const Card *> Deck::GetCards(unsigned short cardsCount)
{
    if(_shuffledList.isEmpty() || _shuffledList.size() < cardsCount){
        return QVector<const Card*>();
    }

    QVector<const Card*> ret;
    for(int i=0;i<cardsCount;++i)
    {
        ret.push_back(_shuffledList.first());
        _shuffledList.removeFirst();
    }
    return ret;
}
