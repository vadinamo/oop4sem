#ifndef POLYGON_H
#define POLYGON_H
#include "QGraphicsRectItem"
#include "basefigure.h"


class Polygon : public BaseFigure
{
private:
    int X;
    int Y;
    int count;
    bool isDrawing;
    QGraphicsPolygonItem* polygon;

public:
    Polygon();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void fillFigure(const QColor &newColor);
    BaseFigure *CopyFigure();
};

#endif // POLYGON_H
