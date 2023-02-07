#ifndef GITEM_H
#define GITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class gItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit gItem(QObject* parent = nullptr);
    void setBrush(QBrush brush) { this->brush = brush; }
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    enum Geometry { ELLIPS = 0, RECTANGLE = 1, STAR = 2};
    Geometry geometry;
    QBrush brush;
public:
    void setGeometry(int i);
    int getGeometry();
public slots:
};

#endif // GITEM_H
