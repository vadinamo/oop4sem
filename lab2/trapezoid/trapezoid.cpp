#include "trapezoid.h"

extern "C" TRAPEZOID_EXPORT BaseFigure* extractFromLibrary()
{
    return new Trapezoid();
}

Trapezoid::Trapezoid()
{
    SetFigureName("trapezoid");
}

void Trapezoid::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    QPolygonF polygon = trapezoid -> polygon();
    SetFigureType(trapezoid);
    polygon << QPointF(event->scenePos()) << QPointF(event->scenePos()) << QPointF(event->scenePos());
    trapezoid -> setPolygon(polygon);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);

    trapezoid -> setPen(pen);
    trapezoid -> setBrush(brushColour);

    trapezoid -> update();
    scene -> addItem(trapezoid);
    scene -> update();

    X = event -> scenePos().x();
    Y = event -> scenePos().y();
}

void Trapezoid::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPolygonF polygon;
    polygon << QPointF(X, event -> scenePos().y()) << QPointF(event -> scenePos().x(), Y / 5) << QPointF(event -> scenePos().y(), Y / 3) << QPointF(event -> scenePos().x(), X / 6);

    trapezoid -> setPolygon(polygon);
    scene -> update();
}

void Trapezoid::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;

    int centerX = trapezoid -> boundingRect().topLeft().x() + (trapezoid -> boundingRect().bottomRight().x() - trapezoid -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = trapezoid -> boundingRect().topLeft().y() + (trapezoid -> boundingRect().bottomRight().y() - trapezoid -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
    SetBoundingRect(trapezoid -> boundingRect());
}

BaseFigure *Trapezoid::CopyFigure()
{

}

QJsonObject Trapezoid::SerializeFigure()
{

}

BaseFigure *Trapezoid::DeserializeFigure(QJsonObject json)
{

}

void Trapezoid::fillFigure(const QColor &newColor)
{

}
