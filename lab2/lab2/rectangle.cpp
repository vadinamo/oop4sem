#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    rectangle = new QGraphicsRectItem();
    SetFigureType(rectangle);

    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);
    rectangle -> setPen(pen);
    rectangle -> setBrush(brushColour);
    rectangle -> setRect(event -> scenePos().x(), event -> scenePos().y(), 1, 1);

    X = event -> scenePos().x();
    Y = event -> scenePos().y();
    rectangle -> update();

    scene -> addItem(rectangle);
    scene -> update();
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;
    center.setX((event -> scenePos().x() - X) / 2 + X);
    center.setY(abs((Y + event -> scenePos().y()) / 2));
    SetCenterPoint(center);

    rectangle -> setRect(X, Y, event -> scenePos().x() - X, event -> scenePos().y() - Y);
    rectangle -> setTransformOriginPoint(X, Y);

    scene->update();
}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;

    int centerX = rectangle -> boundingRect().topLeft().x() + (rectangle -> boundingRect().bottomRight().x() - rectangle -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = rectangle -> boundingRect().topLeft().y() + (rectangle -> boundingRect().bottomRight().y() - rectangle -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
    SetBoundingRect(rectangle -> boundingRect());
}

BaseFigure *Rectangle::CopyFigure()
{
    Rectangle *copy = new Rectangle();

    copy -> SetCenterPoint(GetCenterPoint());
    copy -> SetBoundingRect(GetBoundingRect());
    copy -> SetBrushColor(GetBrushColor());
    copy -> SetPenColor(GetPenColor());
    copy -> SetWidth(GetWidth());


    QPen pen;
    pen.setColor(GetPenColor());
    pen.setWidth(GetWidth());

    QGraphicsRectItem *copyRect = new QGraphicsRectItem();
    copyRect -> setPen(pen);
    copyRect -> setBrush(GetBrushColor());

    copyRect -> setRect(GetBoundingRect());
    copyRect -> setScale(GetFigureType() -> scale());
    copyRect -> setRotation(GetFigureType() -> rotation());
    copyRect -> setTransformOriginPoint(GetCenterPoint());

    copy -> SetFigureType(copyRect);


    return copy;
}


void Rectangle::fillFigure(const QColor &newColor)
{
    SetBrushColor(newColor);
    rectangle -> setBrush(newColor);
}
