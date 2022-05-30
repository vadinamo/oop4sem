#include "trapezoid.h"

extern "C" TRAPEZOID_EXPORT BaseFigure* extractFromLibrary()
{
    return new Trapezoid();
}

BaseFigure *Trapezoid::CreateFigure()
{
    return new Trapezoid();
}

Trapezoid::Trapezoid()
{
    SetFigureName("trapezoid");
}

void Trapezoid::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{
    QMessageLogger().debug() << "abc";
    trapezoid = new QGraphicsPolygonItem();
    SetFigureType(trapezoid);

    SetBrushColor(brushColour);
    SetPenColor(penColour);
    SetWidth(width);

    QPen pen;
    pen.setWidth(width);
    pen.setColor(penColour);
    trapezoid -> setPen(pen);
    trapezoid -> setBrush(brushColour);
    QPolygonF polygonf;
    polygonf << QPointF(event -> scenePos().x(), event -> scenePos().y()) << QPointF(event -> scenePos().x(), event -> scenePos().y());
    trapezoid -> setPolygon(polygonf);

    X = event -> scenePos().x();
    Y = event -> scenePos().y();
    trapezoid -> update();

    scene -> addItem(trapezoid);
    scene -> update();
}

void Trapezoid::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    int h =  event -> scenePos().y() - Y;
    QPolygonF polygon;
    polygon << QPointF(X + h / 2, Y) << QPointF(X, event -> scenePos().y()) << QPointF(event -> scenePos().x(), event -> scenePos().y()) << QPointF(event -> scenePos().x() - h / 2, Y);

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
    Trapezoid *copy = new Trapezoid();

    copy -> SetFigureName(GetFigureName());
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

    copyRect -> setPolygon(trapezoid -> polygon());
    copyRect -> setScale(GetFigureType() -> scale());
    copyRect -> setRotation(GetFigureType() -> rotation());
    copyRect -> setTransformOriginPoint(GetCenterPoint());

    copy -> SetFigureType(copyRect);

    return copy;
}

QJsonObject Trapezoid::SerializeFigure()
{
    QJsonObject json;
    json.insert("type", QJsonValue::fromVariant(GetFigureName()));

    json.insert("center_x", QJsonValue::fromVariant(GetCenterPoint().x()));
    json.insert("center_y", QJsonValue::fromVariant(GetCenterPoint().y()));

    json.insert("top_left_x", QJsonValue::fromVariant((int)GetBoundingRect().topLeft().x()));
    json.insert("top_left_y", QJsonValue::fromVariant((int)GetBoundingRect().topLeft().y()));

    json.insert("bottom_right_x", QJsonValue::fromVariant((int)GetBoundingRect().bottomRight().x()));
    json.insert("bottom_right_y", QJsonValue::fromVariant((int)GetBoundingRect().bottomRight().y()));

    json.insert("pen_color", QJsonValue::fromVariant(GetPenColor()));
    json.insert("brush_color", QJsonValue::fromVariant(GetBrushColor()));
    json.insert("width", QJsonValue::fromVariant(GetWidth()));

    int i = 0;
    foreach(QPointF point, trapezoid -> polygon())
    {
        json.insert("polygon_x" + QString::number(i), QJsonValue::fromVariant(point.x()));
        json.insert("polygon_y" + QString::number(i), QJsonValue::fromVariant(point.y()));
        i++;
    }

    return json;
}

BaseFigure *Trapezoid::DeserializeFigure(QJsonObject json)
{
    Trapezoid* result = new Trapezoid();

    QPoint center;
    center.setX(json.value("center_x").toInt());
    center.setY(json.value("center_y").toInt());

    QRectF rect;
    rect.setTopLeft(QPointF(json.value("top_left_x").toInt(), json.value("top_left_y").toInt()));
    rect.setBottomRight(QPointF(json.value("bottom_right_x").toInt(), json.value("bottom_right_y").toInt()));

    QPen pen;
    pen.setColor(json.value("pen_color").toString());
    pen.setWidth(json.value("width").toInt());

    QPolygonF newPolygon;
    for(int i = 0; i < json.length(); i++)
    {
        if(json.value("polygon_x" + QString::number(i)).toInt() == 0)
            break;
        newPolygon << QPoint(json.value("polygon_x" + QString::number(i)).toInt(), json.value("polygon_y" + QString::number(i)).toInt());
    }

    QGraphicsPolygonItem* newRect = new QGraphicsPolygonItem();
    newRect -> setPolygon(newPolygon);
    newRect -> setBrush(QColor(json.value("brush_color").toString()));
    newRect -> setPen(pen);
    newRect -> setTransformOriginPoint(center);

    result -> SetPenColor(json.value("pen_color").toString());
    result -> SetBrushColor(json.value("brush_color").toString());
    result -> SetWidth(json.value("width").toInt());
    result -> SetCenterPoint(center);
    result -> SetBoundingRect(rect);
    result -> SetFigureType(newRect);

    return result;
}

void Trapezoid::fillFigure(const QColor &newColor)
{
    trapezoid -> setBrush(newColor);
    SetBrushColor(newColor);
}
