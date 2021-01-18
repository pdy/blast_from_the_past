#ifndef CARD_H
#define CARD_H

#include <QString>

#include "UtpPoker.h"

class Card
{
public:  
    Card(UtpPoker::Figure figure = UtpPoker::FLIPSIDE,UtpPoker::CardColor cardColor = UtpPoker::NONE)
        : _fig(figure),_cardCol(cardColor)
    {
        _cardImgName = UtpPoker::Description(figure) + "_" + UtpPoker::Description(cardColor) + ".png";
        _reverseCardImgName = UtpPoker::Description(figure) + "_" + UtpPoker::Description(cardColor) + "_inv.png";

        if(figure == UtpPoker::FLIPSIDE)
        {
            _cardImgName = UtpPoker::Description(figure) + ".png";
            _reverseCardImgName = _cardImgName;
            _cardCol = UtpPoker::NONE;
        }
    }

    UtpPoker::CardColor GetCardColor() const
    {
        return _cardCol;
    }

    UtpPoker::Figure GetFigure() const
    {
        return _fig;
    }


    /*void SetImageName(const QString &name)
    {
        _cardImgName = name;
    }

    void SetSelectedImageName(const QString &name)
    {
        _reverseCardImgName = name;
    }*/

    QString GetImageName() const
    {
        return _cardImgName;
    }

    QString GetSelectedImageName() const
    {
        return _reverseCardImgName;
    }

    bool operator> (const Card &card) const
    {
        return GetFigure() > card.GetFigure();
    }

    bool operator< (const Card &card) const
    {
        return GetFigure() < card.GetFigure();
    }

    bool operator== (const Card &card) const
    {
        return (GetFigure() == card.GetFigure() && GetCardColor() == card.GetCardColor());
    }

private:
    UtpPoker::Figure _fig;
    UtpPoker::CardColor _cardCol;

    QString _cardImgName;
    QString _reverseCardImgName;

};

#endif // CARD_H
