#include "line.h"

Line::Line()
{

}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    line = new QGraphicsLineItem();
    SetFigureType(line);

    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);
    line -> setPen(pen);
    line -> setLine(event -> scenePos().x(), event -> scenePos().y(), event -> scenePos().x(), event -> scenePos().y());

    X = event -> scenePos().x();
    Y = event -> scenePos().y();
    line -> update();

    scene -> addItem(line);
    scene -> update();
}

void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;
    center.setX((event -> scenePos().x() - X) / 2 + X);
    center.setY(abs((Y + event -> scenePos().y()) / 2));
    SetCenterPoint(center);

    line -> setLine(X, Y, event->scenePos().x(), event->scenePos().y());
    line -> setTransformOriginPoint(X, Y);

    scene->update();
}

void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;

    int centerX = line -> boundingRect().topLeft().x() + (line -> boundingRect().bottomRight().x() - line -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = line -> boundingRect().topLeft().y() + (line -> boundingRect().bottomRight().y() - line -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
    SetBoundingRect(line -> boundingRect());
}

BaseFigure *Line::CopyFigure()
{
     Line *copy = new Line();

     copy -> SetCenterPoint(GetCenterPoint());
     copy -> SetBoundingRect(GetBoundingRect());
     copy -> SetBrushColor(GetBrushColor());
     copy -> SetPenColor(GetPenColor());
     copy -> SetWidth(GetWidth());

     QPen pen;
     pen.setColor(GetPenColor());
     pen.setWidth(GetWidth());

     QGraphicsLineItem *copyRect = new QGraphicsLineItem();
     copyRect -> setPen(pen);

     copyRect -> setLine(GetBoundingRect().topLeft().x(), GetBoundingRect().topLeft().y(), GetBoundingRect().bottomRight().x(), GetBoundingRect().bottomRight().y());
     copyRect -> setScale(GetFigureType() -> scale());
     copyRect -> setRotation(GetFigureType() -> rotation());
     copyRect -> setTransformOriginPoint(GetCenterPoint());

     copy -> SetFigureType(copyRect);

     return copy;
}

void Line::fillFigure(const QColor &newColor)
{
    SetPenColor(newColor);

    QPen pen;
    pen.setColor(newColor);
    pen.setWidth(GetWidth());

    line -> setPen(pen);
}
