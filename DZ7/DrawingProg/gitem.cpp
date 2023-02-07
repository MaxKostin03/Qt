#include "gitem.h"

gItem::gItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    brush.setColor(QColor(rand()% 256, rand()% 256, rand()% 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    geometry = Geometry::ELLIPS;
}

QRectF gItem::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void gItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(brush);
    if (geometry == Geometry::ELLIPS) painter->drawEllipse(-30, -30, 60, 60);
    if (geometry == Geometry::RECTANGLE) painter->drawRect(-30,-30, 60, 60);
    if (geometry == Geometry::STAR)
    {
        QPolygonF polygon;
        double step = 360./5, angle_deg = 0;
        for (size_t count = 0; count < 5; ++count)
        {
          double angle_rad = angle_deg*M_PI/180;
          QPointF outerPoint(30 * cos(angle_rad - 0.5), 30 * sin(angle_rad - 0.5));
          QPointF innerPoint(10 * cos(angle_rad),  10 * sin(angle_rad));
          polygon << outerPoint << innerPoint;
          angle_deg += step;
        }
        painter->drawPolygon(polygon);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void gItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void gItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void gItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void gItem::setGeometry(int i)
{
    if (i == 0)
    {
        geometry = Geometry::ELLIPS;
    }
    else if (i == 1)
    {
        geometry = Geometry::RECTANGLE;
    }
    else if (i == 2)
    {
        geometry = Geometry::STAR;
    }
}

int gItem::getGeometry()
{
    return gItem::geometry;
}
