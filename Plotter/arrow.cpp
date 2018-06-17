#include "arrow.h"

#include <QPainter>

Arrow::Arrow()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

QRectF Arrow::boundingRect() const
{
    return QRectF(-6, -6, 6, 6);
}

void Arrow::move(double x, double y)
{
    setTransform(QTransform::fromTranslate(x-old_x, y-old_y), true);
    old_x = x;
    old_y = y;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawEllipse(-5, -5, 5, 5);
}

