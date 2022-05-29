#include "ellipse.h"

Ellipse::Ellipse()
{
    SetFigureName("ellipse");
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
    copy -> SetFigureName(GetFigureName());

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

QJsonObject Ellipse::SerializeFigure()
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

BaseFigure *Ellipse::DeserializeFigure(QJsonObject json)
{
    Ellipse* result = new Ellipse();

    QPoint center;
    center.setX(json.value("center_x").toInt());
    center.setY(json.value("center_y").toInt());

    QRectF rect;
    rect.setTopLeft(QPointF(json.value("top_left_x").toInt(), json.value("top_left_y").toInt()));
    rect.setBottomRight(QPointF(json.value("bottom_right_x").toInt(), json.value("bottom_right_y").toInt()));

    QPen pen;
    pen.setColor(json.value("pen_color").toString());
    pen.setWidth(json.value("width").toInt());

    QGraphicsEllipseItem* newEllipse = new QGraphicsEllipseItem();
    newEllipse -> setRect(rect);
    newEllipse -> setBrush(QColor(json.value("brush_color").toString()));
    newEllipse -> setPen(pen);
    newEllipse -> setTransformOriginPoint(center);

    result -> SetPenColor(json.value("pen_color").toString());
    result -> SetBrushColor(json.value("brush_color").toString());
    result -> SetWidth(json.value("width").toInt());
    result -> SetCenterPoint(center);
    result -> SetBoundingRect(rect);
    result -> SetFigureType(newEllipse);

    return result;
}

void Ellipse::fillFigure(const QColor &newColor)
{
    SetBrushColor(newColor);
    ellipse -> setBrush(newColor);
}
