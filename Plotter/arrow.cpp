#include <algorithm>

#include <QPainter>

#include "arrow.h"

constexpr double clamp(double v, double lo, double hi)
{
    if (v < lo)
        return lo;
    else if (v > hi)
        return hi;
    else
        return v;
}

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

    x_ = clamp(x, 0, 100);
    y_ = clamp(y, -1, 1);
    setPos(x_ * 10, y_ * 50);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawEllipse(-5, -5, 5, 5);
}

