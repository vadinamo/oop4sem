#include "basefigure.h"

BaseFigure::BaseFigure()
{
    figureType = NULL;
}

BaseFigure::~BaseFigure()
{

}

QGraphicsItem *BaseFigure::GetFigureType()
{
    return figureType;
}

void BaseFigure::SetFigureType(QGraphicsItem *setFigureType)
{
    figureType = setFigureType;
}

QPoint BaseFigure::GetCenterPoint()
{
    return centerPoint;
}

void BaseFigure::SetCenterPoint(QPoint setCenterPoint)
{
    centerPoint = setCenterPoint;
}

void BaseFigure::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene, QColor penColour, QColor brushColour, int width)
{

}

void BaseFigure::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{

}

void BaseFigure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{

}

BaseFigure *BaseFigure::CopyFigure()
{

}

const QColor &BaseFigure::GetBrushColor() const
{
    return brushColor;
}

void BaseFigure::SetBrushColor(const QColor &newBrushColor)
{
    brushColor = newBrushColor;
}

const QColor &BaseFigure::GetPenColor() const
{
    return penColor;
}

void BaseFigure::SetPenColor(const QColor &newPenColor)
{
    penColor = newPenColor;
}

const QRectF &BaseFigure::GetBoundingRect() const
{
    return boundingRect;
}

void BaseFigure::SetBoundingRect(const QRectF &newBoundingRect)
{
    boundingRect = newBoundingRect;
}

int BaseFigure::GetWidth() const
{
    return width;
}

void BaseFigure::SetWidth(int newWidth)
{
    width = newWidth;
}

void BaseFigure::fillFigure(const QColor &newColor)
{

}
