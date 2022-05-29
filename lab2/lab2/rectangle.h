#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "QGraphicsRectItem"
#include "basefigure.h"


class Rectangle : public BaseFigure
{
private:
    int X;
    int Y;
    QGraphicsRectItem* rectangle;

public:
    Rectangle();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void fillFigure(const QColor &newColor);
    BaseFigure *CopyFigure();
    QJsonObject SerializeFigure();
    BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // RECTANGLE_H
