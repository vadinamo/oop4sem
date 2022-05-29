#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QColorDialog>

#include <paintscene.h>

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

private:
    Ui::Paint *ui;
    QTimer *timer;      /* Определяем таймер для подготовки актуальных размеров
                         * графической сцены
                         * */
    PaintScene *scene;  // Объявляем кастомную графическую сцену
    QColor fillColor;

private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void on_rectangle_clicked();
    void on_ellipse_clicked();
    void on_line_clicked();
    void on_broken_line_clicked();
    void on_draw_clicked();
    void on_move_clicked();
    void on_scale_slider_valueChanged(int value);
    void on_rotate_slider_valueChanged(int value);
    void on_width_edit_editingFinished();
    void on_undo_clicked();
    void on_redo_clicked();
    void on_colour_clicked();
    void on_fill_color_clicked();
    void on_polygon_clicked();
    void on_clear_clicked();
    void on_copy_clicked();
    void on_fill_clicked();
};

#endif // PAINT_H
