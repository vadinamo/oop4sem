#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

#include "tools.h"
#include "basefigure.h"

#include "rectangle.h"
#include "ellipse.h"
#include "line.h"
#include "brokenline.h"
#include "polygon.h"

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

    void Serialize(QString fileName);
    void Deserialize(QString fileName);
};

#endif // PAINTSCENE_H
