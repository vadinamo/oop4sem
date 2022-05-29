#ifndef BLOKENLINE_H
#define BLOKENLINE_H
#include "QGraphicsRectItem"
#include "basefigure.h"


class BrokenLine : public BaseFigure
{
private:
    int X;
    int Y;
    QGraphicsLineItem* brokenLine;
    bool isDrawing;

public:
    BrokenLine();

    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    BaseFigure *CopyFigure();
};

#endif // BLOKENLINE_H
