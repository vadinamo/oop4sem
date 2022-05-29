#ifndef BASEFIGURE_H
#define BASEFIGURE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QJsonObject>


class BaseFigure
{
private:
    QString FigureName;

    QGraphicsItem* figureType;
    QPoint centerPoint;

    QColor penColor;
    QColor brushColor;
    QRectF boundingRect;
    int width;

public:
    BaseFigure();
    ~BaseFigure();

    QString GetFigureName();
    void SetFigureName(QString newName);

    QGraphicsItem *GetFigureType();
    void SetFigureType(QGraphicsItem *setFigureType);

    QPoint GetCenterPoint();
    void SetCenterPoint(QPoint setCenterPoint);

    const QColor &GetBrushColor() const;
    void SetBrushColor(const QColor &newBrushColor);

    const QColor &GetPenColor() const;
    void SetPenColor(const QColor &newPenColor);

    const QRectF &GetBoundingRect() const;
    void SetBoundingRect(const QRectF &newBoundingRect);

    int GetWidth() const;
    void SetWidth(int newWidth);

    virtual void fillFigure(const QColor &newColor);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual BaseFigure *CopyFigure();
    virtual QJsonObject SerializeFigure();
    virtual BaseFigure *DeserializeFigure(QJsonObject json);
};

#endif // BASEFIGURE_H
