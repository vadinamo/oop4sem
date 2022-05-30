#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "basefigure.h"

class Trapezoid : public BaseFigure
{
private:
    int X;
    int Y;
    QGraphicsPolygonItem* trapezoid;

public:
    Trapezoid();

    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void fillFigure(const QColor &newColor);
    BaseFigure *CopyFigure();
    QJsonObject SerializeFigure();
    BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // TRAPEZOID_H
