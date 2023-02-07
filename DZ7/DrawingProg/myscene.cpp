#include "myscene.h"

static int geomI = 0;

myScene::myScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && !this->itemAt(event->scenePos(), {}))
    {
        It = new gItem(this);
        It->setPos(event->scenePos());
        this->addItem(It);
        if (geomI == 0)
        {
            It->setGeometry(geomI);
            geomI++;
            this->update();
        }
            else if (geomI == 1)
        {
            It->setGeometry(geomI);
            geomI++;
            this->update();
        }
        else if (geomI == 2)
        {
            It->setGeometry(geomI);
            geomI = 0;
            this->update();
        }
    }

    if (event->button() == Qt::RightButton && this->itemAt(event->scenePos(), {}))
    {
        QGraphicsItem* pIt = this->itemAt(event->scenePos(),{});
        this->removeItem(pIt);
    }
    QGraphicsScene::mousePressEvent(event);
}

