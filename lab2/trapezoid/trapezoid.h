#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "trapezoid_global.h"
#include "../lab2/basefigure.h"

extern "C" TRAPEZOID_EXPORT BaseFigure* extractFromLibrary();

class TRAPEZOID_EXPORT Trapezoid : public BaseFigure
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
    BaseFigure *CreateFigure();
    QJsonObject SerializeFigure();
    BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // TRAPEZOID_H
