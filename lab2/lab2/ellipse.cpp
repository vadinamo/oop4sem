#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    ellipse = new QGraphicsEllipseItem();
    SetFigureType(ellipse);

    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);
    ellipse -> setPen(pen);
    ellipse -> setBrush(brushColour);
    ellipse -> setRect(event -> scenePos().x(), event -> scenePos().y(), 1, 1);

    X = event -> scenePos().x();
    Y = event -> scenePos().y();
    ellipse -> update();

    scene -> addItem(ellipse);
    scene -> update();
}

void Ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;
    center.setX((event -> scenePos().x() - X) / 2 + X);
    center.setY(abs((Y + event -> scenePos().y()) / 2));
    SetCenterPoint(center);

    ellipse->setRect(X, Y, event -> scenePos().x() - X, event -> scenePos().y() - Y);
    ellipse->setTransformOriginPoint(X, Y);

    scene->update();
}

void Ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    QPoint center;

    int centerX = ellipse -> boundingRect().topLeft().x() + (ellipse -> boundingRect().bottomRight().x() - ellipse -> boundingRect().topLeft().x()) / 2;
    center.setX(centerX);


    int centerY = ellipse -> boundingRect().topLeft().y() + (ellipse -> boundingRect().bottomRight().y() - ellipse -> boundingRect().topLeft().y()) / 2;
    center.setY(centerY);

    SetCenterPoint(center);
    SetBoundingRect(ellipse -> boundingRect());
}

BaseFigure *Ellipse::CopyFigure()
{
    Ellipse *copy = new Ellipse();

    copy -> SetCenterPoint(GetCenterPoint());
    copy -> SetBoundingRect(GetBoundingRect());
    copy -> SetBrushColor(GetBrushColor());
    copy -> SetPenColor(GetPenColor());
    copy -> SetWidth(GetWidth());


    QPen pen;
    pen.setColor(GetPenColor());
    pen.setWidth(GetWidth());

    QGraphicsEllipseItem *copyEllipse = new QGraphicsEllipseItem();
    copyEllipse -> setPen(pen);
    copyEllipse -> setBrush(GetBrushColor());

    copyEllipse -> setRect(GetBoundingRect());
    copyEllipse -> setScale(GetFigureType() -> scale());
    copyEllipse -> setRotation(GetFigureType() -> rotation());
    copyEllipse -> setTransformOriginPoint(GetCenterPoint());

    copy -> SetFigureType(copyEllipse);


    return copy;
}
