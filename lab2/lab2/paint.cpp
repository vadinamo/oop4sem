#include "paint.h"
#include "ui_paint.h"

#include "rectangle.h"
#include "ellipse.h"
#include "line.h"
#include "brokenline.h"
#include "polygon.h"

Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new PaintScene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(100);          // Запускаем таймер
    scene -> SetCurrentBrushColor(Qt::transparent);
    scene -> SetCurrentPenColor(Qt::white);
    scene -> SetCurrentWidth(1);
    ui ->width_edit -> setText("1");
}

Paint::~Paint()
{
    delete ui;
}

void Paint::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::on_rectangle_clicked()
{
    Rectangle *rectangle = new Rectangle();
    scene -> SetCurrentFigure(rectangle);
}


void Paint::on_ellipse_clicked()
{
    Ellipse *ellipse = new Ellipse();
    scene -> SetCurrentFigure(ellipse);
}


void Paint::on_line_clicked()
{
    Line *line = new Line();
    scene -> SetCurrentFigure(line);
}


void Paint::on_broken_line_clicked()
{
    BrokenLine *brokenLine = new BrokenLine();
    scene -> SetCurrentFigure(brokenLine);
}


void Paint::on_draw_clicked()
{
    scene -> SetCurrentTool(Draw);
}


void Paint::on_move_clicked()
{
    scene -> SetCurrentTool(Move);
}


void Paint::on_scale_slider_valueChanged(int value)
{
    scene -> ChangeScale(value);
}


void Paint::on_rotate_slider_valueChanged(int value)
{
    scene -> Rotate(value);
}


void Paint::on_width_edit_editingFinished()
{
    scene -> SetCurrentWidth(ui ->width_edit -> text().toInt());
}


void Paint::on_undo_clicked()
{
    scene -> Undo();
}


void Paint::on_redo_clicked()
{
    scene -> Redo();
}


void Paint::on_colour_clicked()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        scene -> SetCurrentPenColor(color);
    }
}


void Paint::on_fill_color_clicked()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        scene -> SetCurrentBrushColor(color);
    }
}

void Paint::on_polygon_clicked()
{
    Polygon *polygon = new Polygon();
    scene -> SetCurrentFigure(polygon);
}

void Paint::on_clear_clicked()
{
    scene -> clear();
}


void Paint::on_copy_clicked()
{
    scene -> SetCurrentTool(Copy);
}

void Paint::on_fill_clicked()
{
    scene -> SetCurrentTool(Fill);
}


void Paint::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save figure"),
                "figure",
                tr("JSON (*.json)" )
                );

    scene -> Serialize(fileName);
}


void Paint::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Load figure"),
                "",
                tr("JSON (*.json)" )
                );

    scene -> Deserialize(fileName);
}


void Paint::on_pushButton_clicked()
{
//    ui -> custom_figures -> clear();

//    QDir directory("/Documents/C#/oop4sem/lab2/build-trapezoid-Desktop_Qt_6_1_0_clang_64bit-Release");
//    QStringList libs = directory.entryList(QStringList() << "*.dll" << "*.DLL", QDir::Files);

//    foreach(QString libPath, libs)
//    {
//        QLibrary lib(directory.absoluteFilePath(libPath));

//        if (!lib.load())
//        {
//            qDebug() << lib.errorString();
//            continue;
//        }

//        typedef Figure* (*Prototype)();
//        Prototype  func = (Prototype) lib.resolve("getShapeType");

//        if(func)
//        {
//            Figure *tmp = func();
//            QString figName = tmp->figName();

//            tmp->options = options;
//            figStack[figName] = tmp;

//            QAction *tmpAct = new QAction(figName, this);
//            connect(tmpAct,  &QAction::triggered, this, [this, figName]{ on_Figures_2_currentTextChanged(figName); });
//            ui->Figures_2->addItem(tmp->figName());
//        }
//    }

//    QMessageLogger().debug() << "MOUSE DOWN";
//    ui->Figures_2->setCurrentIndex(-1);
//    ui->Figures->setCurrentIndex(-1);
}

