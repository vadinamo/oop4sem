#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

#include "tools.h"
#include "basefigure.h"

using namespace std;

class PaintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

private:
    int CurrentWidth;
    int CurrentId;
    Tools CurrentTool;

    QColor CurrentPenColor;
    QColor CurrentBrushColor;

    BaseFigure* CurrentFigure;
    BaseFigure* CopyFigure;
    QVector<QPoint> ListOfCenters;
    QVector<BaseFigure*> SceneFiguresList;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    void SetCurrentTool(Tools NewCurrentTool);

    void Rotate(int RotateAngle);
    void ChangeScale(int ScaleValue);

    void SetCurrentPenColor(const QColor &NewPenColor);
    void SetCurrentBrushColor(const QColor &NewBrushColor);
    void SetCurrentFillColor(const QColor &NewBrushColor);

    void SetCurrentFigure(BaseFigure *NewFigure);
    void SetCurrentWidth(int NewWidth);

    int GetCurrentWidth();

    void Undo();
    void Redo();
};

#endif // PAINTSCENE_H
