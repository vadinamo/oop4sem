#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "QGraphicsRectItem"
#include "basefigure.h"


class Ellipse : public BaseFigure
{
private:
    int X;
    int Y;
    QGraphicsEllipseItem* ellipse;

public:
    Ellipse();

    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void fillFigure(const QColor &newColor);
    BaseFigure *CopyFigure();
    BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // ELLIPSE_H
