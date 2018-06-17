#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsObject>
#include <QBrush>

class Arrow : public QGraphicsObject
{
    Q_OBJECT
public:
    Arrow();
    QRectF boundingRect() const override;

public Q_SLOTS:
    void move(double x, double y);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

#endif // ARROW_H
