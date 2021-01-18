#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QPair>
#include <QVector>

class CardSet;
class Card;
class Deck;

class ComputerPlayer
{
public:
    ComputerPlayer();

    QPair<unsigned short,CardSet*> ExchangeCards( CardSet &cardSet,Deck &deck);

private:
    int Random(int max);

    QVector<int> _possibleIdexes;

};

#endif // COMPUTERPLAYER_H
