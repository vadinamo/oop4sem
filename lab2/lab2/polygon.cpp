#include "polygon.h"

Polygon::Polygon()
{
    count = 0;
    isDrawing = true;
    polygon = new QGraphicsPolygonItem;
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    QPolygonF polygonf = polygon -> polygon();
    SetFigureType(polygon);

    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    if(isDrawing)
    {
        polygonf << QPointF(event -> scenePos().x(), event -> scenePos().y());
        isDrawing = false;
    }

    polygonf << QPointF(event -> scenePos().x(), event -> scenePos().y());
    polygon -> setPolygon(polygonf);
    count++;

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);

    polygon -> setPen(pen);
    polygon -> setBrush(brushColour);
    polygon -> setPolygon(polygonf);

    polygon -> update();
    scene -> addItem(polygon);
    scene -> update();
}

void Polygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPolygonF polygonf = polygon -> polygon();
    polygonf[count] = QPointF(event -> scenePos().x(), event -> scenePos().y());
    polygon -> setPolygon(polygonf);
    scene->update();
}

void Polygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;

    int centerX = polygon -> boundingRect().topLeft().x() + (polygon -> boundingRect().bottomRight().x() - polygon -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = polygon -> boundingRect().topLeft().y() + (polygon -> boundingRect().bottomRight().y() - polygon -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
    SetBoundingRect(polygon -> boundingRect());
}

BaseFigure *Polygon::CopyFigure()
{
    Polygon *copy = new Polygon();

    copy -> SetCenterPoint(GetCenterPoint());
    copy -> SetBoundingRect(GetBoundingRect());
    copy -> SetBrushColor(GetBrushColor());
    copy -> SetPenColor(GetPenColor());
    copy -> SetWidth(GetWidth());

    QPen pen;
    pen.setColor(GetPenColor());
    pen.setWidth(GetWidth());

    QGraphicsPolygonItem *copyRect = new QGraphicsPolygonItem();
    copyRect -> setPen(pen);
    copyRect -> setBrush(GetBrushColor());

    copyRect -> setPolygon(polygon -> polygon());
    copyRect -> setScale(GetFigureType() -> scale());
    copyRect -> setRotation(GetFigureType() -> rotation());
    copyRect -> setTransformOriginPoint(GetCenterPoint());

    copy -> SetFigureType(copyRect);

    return copy;
}
