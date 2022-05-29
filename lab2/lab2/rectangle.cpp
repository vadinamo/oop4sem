#include "rectangle.h"

Rectangle::Rectangle()
{
    SetFigureName("rectangle");
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

    copy -> SetFigureName(GetFigureName());
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

QJsonObject Rectangle::SerializeFigure()
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

    return json;
}

BaseFigure *Rectangle::DeserializeFigure(QJsonObject json)
{
    Rectangle* result = new Rectangle();

    QPoint center;
    center.setX(json.value("center_x").toInt());
    center.setY(json.value("center_y").toInt());

    QRectF rect;
    rect.setTopLeft(QPointF(json.value("top_left_x").toInt(), json.value("top_left_y").toInt()));
    rect.setBottomRight(QPointF(json.value("bottom_right_x").toInt(), json.value("bottom_right_y").toInt()));

    QPen pen;
    pen.setColor(json.value("pen_color").toString());
    pen.setWidth(json.value("width").toInt());

    QGraphicsRectItem* newRect = new QGraphicsRectItem();
    newRect -> setRect(rect);
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

void Rectangle::fillFigure(const QColor &newColor)
{
    SetBrushColor(newColor);
    rectangle -> setBrush(newColor);
}
