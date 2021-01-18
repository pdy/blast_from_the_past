#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QGraphicsItem>

class Card;

class CardView : public QGraphicsItem
{
public:
    explicit CardView(const Card *card,qreal x = 0, qreal y = 0);

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void RePaint(const Card *card)
    {
        _card = card;
        update();
    }

    void SetSelectAble(bool selectable)
    {
        _selectAble = selectable;
    }

    bool IsSelectAble() const
    {
        return _selectAble;
    }

    void SetSelected(bool selected)
    {
        _selected = selected;
        update();
    }

    bool IsSelected() const
    {
        return _selected;
    }

    const Card *GetCard()
    {
        return _card;
    }

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    const Card *_card;
    bool _selected;
    bool _selectAble;

    qreal _x;
    qreal _y;

};

#endif // CARDVIEW_H
