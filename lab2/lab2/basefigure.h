#ifndef BASEFIGURE_H
#define BASEFIGURE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class BaseFigure
{
private:
    QGraphicsItem* figureType;
    QPoint centerPoint;

    QColor penColor;
    QColor brushColor;
    QRectF boundingRect;
    int width;

public:
    BaseFigure();
    ~BaseFigure();

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

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual BaseFigure *CopyFigure();
};

#endif // BASEFIGURE_H
