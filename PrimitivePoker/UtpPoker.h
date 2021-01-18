#ifndef UTPPOKER_H
#define UTPPOKER_H

#include <QString>
#include <QList>

namespace UtpPoker{
enum CardColor
{
    NONE = 0,   //using with 'FLIPSIDE' Figure
    SPADES = 1,     //pik
    CLUBS,      //trefl
    DIAMONDS,   //kar
    HEARTS      //hearts
};

enum Figure
{
    FLIPSIDE = 0,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14

};

enum CardSystem
{
    HIGH_CARD = -100,
    PAIR = 10,
    TWO_PAIRS = 40,
    THREE_OF_KIND = 100,
    STRAIGHT_SMALL = 150,
    STRAIGHT_BIG = 220,
    FLUSH = 300,
    FULL = 360,
    FOUR_OF_KIND = 430,
    STRAIGHT_FLUSH = 1000, // poker, tutaj maly strit w kolorze
    ROYAL_FLUSH = 2000 // poker krolewski, tutaj duzy strit w kolorze
};

QList<Figure> FiguresList();

QString Description(CardColor color);

QString Description(Figure fig);
};

#endif // UTPPOKER_H
