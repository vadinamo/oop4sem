#include "paintscene.h"
#include "math.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    CurrentTool = None;
    CurrentFigure = NULL;
}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    QMessageLogger().debug() << "center:";
    for(int i = 0; i < items().length(); i++)
    {
        QMessageLogger().debug() << "x: " << ListOfCenters[i].x() << "y: " << ListOfCenters[i].y();
    }

    switch (CurrentTool)
    {
    case None:
        break;

    case Draw:
        CurrentFigure -> mousePressEvent(event, this, CurrentPenColor, CurrentBrushColor, CurrentWidth);
        update();
        break;

    case Move:
    {
        QList<QGraphicsItem *> FiguresList = items(event -> scenePos());

        if(!FiguresList.isEmpty()){
            int centerPoint = 0;

            for(int i = 0; i < items().length(); i++){
                centerPoint = ListOfCenters.at(i).x();

                if(items().at(i) == FiguresList.at(0) && items().at(i) -> isVisible() && centerPoint != 0){
                    CurrentFigure = SceneFiguresList.at(i);
                }
                update();
            }
            if(centerPoint == 0){
                CurrentFigure = NULL;
            }
        }
        break;
    }

    case Copy:
    {
        BaseFigure* Figure = CurrentFigure -> CopyFigure();
        SceneFiguresList.push_front(Figure);
        Figure -> GetFigureType() -> setPos(event->scenePos().x() - CurrentFigure -> GetCenterPoint().x(),
                                                          event->scenePos().y() - CurrentFigure -> GetCenterPoint().y());

        ListOfCenters.push_front(Figure -> GetCenterPoint());
        this->addItem(Figure->GetFigureType());
        this->update();

        SetCurrentTool(Move);
    }
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch(CurrentTool)
    {
    case None:
        break;

    case Draw:
        CurrentFigure -> mouseMoveEvent(event, this);
        break;

    case Move:
        CurrentFigure -> GetFigureType() -> setPos(event -> scenePos().x() - CurrentFigure -> GetCenterPoint().x(),
                                                                    event -> scenePos().y() - CurrentFigure-> GetCenterPoint().y());
        update();
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    switch (CurrentTool)
    {
    case None:
        break;

    case Draw:
        CurrentFigure -> mouseReleaseEvent(event, this);
        ListOfCenters.push_front(CurrentFigure -> GetCenterPoint());
        update();

        SceneFiguresList.push_front(CurrentFigure);
        break;

    case Move:
        break;
    }
}

void PaintScene::SetCurrentTool(Tools NewCurrentTool)
{
    CurrentTool = NewCurrentTool;
}

void PaintScene::SetCurrentWidth(int NewWidth)
{
    CurrentWidth = NewWidth;
}

int PaintScene::GetCurrentWidth()
{
    return CurrentWidth;
}

void PaintScene::Rotate(int RotateAngle)
{
    if(CurrentFigure != NULL && CurrentFigure -> GetFigureType() != NULL)
    {
        CurrentFigure -> GetFigureType() -> setTransformOriginPoint(CurrentFigure -> GetCenterPoint());
        CurrentFigure -> GetFigureType() -> setRotation(RotateAngle);

        update();
    }
}

void PaintScene::ChangeScale(int ScaleValue)
{
    if(CurrentFigure != NULL && CurrentFigure -> GetFigureType() != NULL)
    {
        CurrentFigure -> GetFigureType() -> setTransformOriginPoint(CurrentFigure -> GetCenterPoint());
        CurrentFigure -> GetFigureType() -> setScale(ScaleValue);

        update();
    }
}

void PaintScene::SetCurrentPenColor(const QColor &NewPenColor)
{
    CurrentPenColor = NewPenColor;
}

void PaintScene::SetCurrentBrushColor(const QColor &NewBrushColor)
{
    CurrentBrushColor = NewBrushColor;
}

void PaintScene::SetCurrentFigure(BaseFigure *NewFigure)
{
    CurrentFigure = NewFigure;
    CurrentTool = Draw;
}

void PaintScene::Undo()
{
    foreach(QGraphicsItem* item, items()){
        if(item -> isVisible())
        {
            item -> setVisible(false);
            if(CurrentFigure != NULL && !CurrentFigure -> GetFigureType() -> isVisible())
            {
                CurrentFigure = NULL;
            }
            break;
        }
    }
}

void PaintScene::Redo()
{
    for(int i = items().length() - 1; i >= 0; i--)
    {
        if(!items().at(i) -> isVisible())
        {
            items().at(i) -> setVisible(true);
            break;
        }
    }
}
