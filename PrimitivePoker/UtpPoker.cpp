#include "UtpPoker.h"

namespace UtpPoker{

QList<Figure> FiguresList()
{
    QList<Figure> ret;
    ret.push_back(NINE);
    ret.push_back(TEN);
    ret.push_back(JACK);
    ret.push_back(QUEEN);
    ret.push_back(KING);
    ret.push_back(ACE);
    return ret;
}

QString Description(CardColor color)
{
    QString ret;
    if(color == SPADES){
        ret = "spades";
    }
    else if(color == CLUBS){
        ret = "clubs";
    }
    else if(color == DIAMONDS){
        ret = "diamonds";
    }
    else if(color == HEARTS){
        ret = "hearts";
    }
    else if(color == NONE){
        ret = "none";
    }
    return ret;
}

QString Description(Figure fig)
{
    QString ret;
    if(fig == NINE){
        ret = "nine";
    }
    else if(fig == TEN){
        ret = "ten";
    }
    else if(fig == JACK){
        ret = "jack";
    }
    else if(fig == QUEEN){
        ret = "queen";
    }
    else if(fig == KING){
        ret = "king";
    }
    else if(fig == ACE){
        ret = "ace";
    }
    else if(fig == FLIPSIDE){
        ret = "flipside";
    }
    return ret;
}

};
