#include "Card.h"
#include "CardView.h"

#include <QImage>
#include <QPainter>

using namespace UtpPoker;

CardView::CardView(const Card *card, qreal x, qreal y) :
    QGraphicsItem(), _card(card),_x(x),_y(y)
{
    SetSelectAble(false);
    _selected = false;
}
//=======================================
QRectF CardView::boundingRect() const
{
    return QRectF(_x,_y,90,120);
}
//=======================================
void CardView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString imgName = ":/images/";
    imgName += IsSelected() ? _card->GetSelectedImageName() : _card->GetImageName();
    QImage img(imgName);

    QRectF target = boundingRect();
    //QRectF source = target;

    painter->drawImage(target,img);
}
//=======================================
void CardView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(IsSelectAble()){
        _selected = _selected ? false : true;
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}
//=======================================
void CardView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
