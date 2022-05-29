#ifndef LINE_H
#define LINE_H
#include "QGraphicsRectItem"
#include "basefigure.h"


class Line : public BaseFigure
{
private:
    int X;
    int Y;
    QGraphicsLineItem* line;

public:
    Line();

    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    void fillFigure(const QColor &newColor);
    BaseFigure *CopyFigure();
    QJsonObject SerializeFigure();
    BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // LINE_H
