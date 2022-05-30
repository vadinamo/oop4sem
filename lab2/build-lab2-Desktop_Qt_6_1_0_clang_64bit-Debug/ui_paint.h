/********************************************************************************
** Form generated from reading UI file 'paint.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINT_H
#define UI_PAINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Paint
{
public:
    QGraphicsView *graphicsView;
    QRadioButton *rectangle;
    QRadioButton *ellipse;
    QRadioButton *line;
    QPushButton *undo;
    QPushButton *redo;
    QPushButton *draw;
    QPushButton *move;
    QSlider *rotate_slider;
    QSlider *scale_slider;
    QLabel *scale_label;
    QLabel *rotate_label;
    QLabel *width_label;
    QLineEdit *width_edit;
    QPushButton *colour;
    QPushButton *fill_color;
    QRadioButton *broken_line;
    QRadioButton *polygon;
    QPushButton *clear;
    QPushButton *copy;
    QPushButton *fill;
    QPushButton *save;
    QPushButton *load;
    QComboBox *custom_figures;
    QPushButton *pushButton;
    QRadioButton *trapezoid;

    void setupUi(QWidget *Paint)
    {
        if (Paint->objectName().isEmpty())
            Paint->setObjectName(QString::fromUtf8("Paint"));
        Paint->resize(802, 460);
        Paint->setContextMenuPolicy(Qt::DefaultContextMenu);
        graphicsView = new QGraphicsView(Paint);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 40, 681, 361));
        rectangle = new QRadioButton(Paint);
        rectangle->setObjectName(QString::fromUtf8("rectangle"));
        rectangle->setGeometry(QRect(10, 10, 81, 22));
        ellipse = new QRadioButton(Paint);
        ellipse->setObjectName(QString::fromUtf8("ellipse"));
        ellipse->setGeometry(QRect(100, 10, 61, 22));
        line = new QRadioButton(Paint);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(170, 10, 41, 22));
        undo = new QPushButton(Paint);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setGeometry(QRect(660, 430, 61, 24));
        redo = new QPushButton(Paint);
        redo->setObjectName(QString::fromUtf8("redo"));
        redo->setGeometry(QRect(729, 430, 61, 24));
        draw = new QPushButton(Paint);
        draw->setObjectName(QString::fromUtf8("draw"));
        draw->setGeometry(QRect(680, 10, 51, 24));
        move = new QPushButton(Paint);
        move->setObjectName(QString::fromUtf8("move"));
        move->setGeometry(QRect(740, 10, 51, 24));
        rotate_slider = new QSlider(Paint);
        rotate_slider->setObjectName(QString::fromUtf8("rotate_slider"));
        rotate_slider->setGeometry(QRect(289, 430, 211, 31));
        rotate_slider->setMinimum(1);
        rotate_slider->setMaximum(365);
        rotate_slider->setOrientation(Qt::Horizontal);
        scale_slider = new QSlider(Paint);
        scale_slider->setObjectName(QString::fromUtf8("scale_slider"));
        scale_slider->setGeometry(QRect(40, 430, 201, 31));
        scale_slider->setMinimum(0);
        scale_slider->setMaximum(10);
        scale_slider->setOrientation(Qt::Horizontal);
        scale_label = new QLabel(Paint);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setGeometry(QRect(130, 410, 60, 16));
        rotate_label = new QLabel(Paint);
        rotate_label->setObjectName(QString::fromUtf8("rotate_label"));
        rotate_label->setGeometry(QRect(370, 410, 41, 16));
        width_label = new QLabel(Paint);
        width_label->setObjectName(QString::fromUtf8("width_label"));
        width_label->setGeometry(QRect(560, 410, 41, 16));
        width_edit = new QLineEdit(Paint);
        width_edit->setObjectName(QString::fromUtf8("width_edit"));
        width_edit->setGeometry(QRect(520, 430, 113, 24));
        colour = new QPushButton(Paint);
        colour->setObjectName(QString::fromUtf8("colour"));
        colour->setGeometry(QRect(540, 10, 51, 24));
        fill_color = new QPushButton(Paint);
        fill_color->setObjectName(QString::fromUtf8("fill_color"));
        fill_color->setGeometry(QRect(600, 10, 61, 24));
        broken_line = new QRadioButton(Paint);
        broken_line->setObjectName(QString::fromUtf8("broken_line"));
        broken_line->setGeometry(QRect(220, 10, 91, 22));
        polygon = new QRadioButton(Paint);
        polygon->setObjectName(QString::fromUtf8("polygon"));
        polygon->setGeometry(QRect(320, 10, 71, 22));
        clear = new QPushButton(Paint);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(700, 370, 80, 24));
        copy = new QPushButton(Paint);
        copy->setObjectName(QString::fromUtf8("copy"));
        copy->setGeometry(QRect(680, 50, 51, 24));
        fill = new QPushButton(Paint);
        fill->setObjectName(QString::fromUtf8("fill"));
        fill->setGeometry(QRect(740, 50, 51, 24));
        save = new QPushButton(Paint);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(680, 90, 51, 24));
        load = new QPushButton(Paint);
        load->setObjectName(QString::fromUtf8("load"));
        load->setGeometry(QRect(740, 90, 51, 24));
        custom_figures = new QComboBox(Paint);
        custom_figures->setObjectName(QString::fromUtf8("custom_figures"));
        custom_figures->setGeometry(QRect(700, 160, 79, 24));
        pushButton = new QPushButton(Paint);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(700, 130, 80, 24));
        trapezoid = new QRadioButton(Paint);
        trapezoid->setObjectName(QString::fromUtf8("trapezoid"));
        trapezoid->setGeometry(QRect(410, 10, 81, 22));

        retranslateUi(Paint);

        QMetaObject::connectSlotsByName(Paint);
    } // setupUi

    void retranslateUi(QWidget *Paint)
    {
        Paint->setWindowTitle(QCoreApplication::translate("Paint", "lab2", nullptr));
        rectangle->setText(QCoreApplication::translate("Paint", "rectangle", nullptr));
        ellipse->setText(QCoreApplication::translate("Paint", "ellipse", nullptr));
        line->setText(QCoreApplication::translate("Paint", "line", nullptr));
        undo->setText(QCoreApplication::translate("Paint", "Undo", nullptr));
        redo->setText(QCoreApplication::translate("Paint", "Redo", nullptr));
        draw->setText(QCoreApplication::translate("Paint", "draw", nullptr));
        move->setText(QCoreApplication::translate("Paint", "move", nullptr));
        scale_label->setText(QCoreApplication::translate("Paint", "Scale", nullptr));
        rotate_label->setText(QCoreApplication::translate("Paint", "Rotate", nullptr));
        width_label->setText(QCoreApplication::translate("Paint", "Width", nullptr));
        colour->setText(QCoreApplication::translate("Paint", "colour", nullptr));
        fill_color->setText(QCoreApplication::translate("Paint", "fill color", nullptr));
        broken_line->setText(QCoreApplication::translate("Paint", "broken line", nullptr));
        polygon->setText(QCoreApplication::translate("Paint", "polygon", nullptr));
        clear->setText(QCoreApplication::translate("Paint", "clear", nullptr));
        copy->setText(QCoreApplication::translate("Paint", "copy", nullptr));
        fill->setText(QCoreApplication::translate("Paint", "fill", nullptr));
        save->setText(QCoreApplication::translate("Paint", "save", nullptr));
        load->setText(QCoreApplication::translate("Paint", "load", nullptr));
        pushButton->setText(QCoreApplication::translate("Paint", "update libs", nullptr));
        trapezoid->setText(QCoreApplication::translate("Paint", "trapezoid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Paint: public Ui_Paint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINT_H
