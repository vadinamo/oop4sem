#include "brokenline.h"

BrokenLine::BrokenLine()
{
    isDrawing = true;
}

void BrokenLine::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    brokenLine = new QGraphicsLineItem();
    SetFigureType(brokenLine);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);
    brokenLine -> setPen(pen);

    if(isDrawing)
    {
        X = event -> scenePos().x();
        Y = event -> scenePos().y();
        brokenLine -> setLine(X, Y, X, Y);
    }

    else
    {
        brokenLine -> setLine(X, Y, event -> scenePos().x(), event -> scenePos().y());
    }

    brokenLine -> update();
    scene -> addItem(brokenLine);
    scene -> update();
}

void BrokenLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    brokenLine -> setLine(X, Y, event->scenePos().x(), event->scenePos().y());
    scene -> update();
}

void BrokenLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    X = event -> scenePos().x();
    Y = event -> scenePos().y();
    isDrawing = false;

    QPoint center;

    int centerX = brokenLine -> boundingRect().topLeft().x() + (brokenLine -> boundingRect().bottomRight().x() - brokenLine -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = brokenLine -> boundingRect().topLeft().y() + (brokenLine -> boundingRect().bottomRight().y() - brokenLine -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
}

BaseFigure *BrokenLine::CopyFigure()
{
}

BaseFigure *BrokenLine::DeserializeFigure(QJsonObject json)
{

}
