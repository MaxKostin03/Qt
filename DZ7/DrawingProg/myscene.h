#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>

#include "gitem.h"

class myScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScene(QObject *parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
    gItem* It;
};

#endif // MYSCENE_H
