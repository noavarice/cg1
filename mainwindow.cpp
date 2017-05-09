#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bresenham.h"

#define RADIUS 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageFirst = QImage(ui->labelFirstCurve->size(), QImage::Format_ARGB32);
    imageSecond = QImage(ui->labelFirstCurve->size(), QImage::Format_ARGB32);

    imageFirst.fill(Qt::white);
    imageSecond.fill(Qt::white);

    ui->labelFirstCurve->setPixmap(QPixmap::fromImage(imageFirst));
    ui->labelSecondCurve->setPixmap(QPixmap::fromImage(imageSecond));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonReset_clicked()
{
    QColor color{ui->spinBoxRed->value(), ui->spinBoxGreen->value(), ui->spinBoxBlue->value()};
    uint8_t width =  ui->spinBoxWidth->value();
    QPoint start{ui->spinBoxX1->value(), ui->spinBoxY1->value()};
    QPoint end{ui->spinBoxX2->value(), ui->spinBoxY2->value()};

    imageFirst.fill(Qt::white);
    imageSecond.fill(Qt::white);

    bresenhamCircleCurve(imageFirst, start, end, RADIUS, color, width, true);
    bresenhamCircleCurve(imageSecond, start, end, RADIUS, color, width, false);

    ui->labelFirstCurve->setPixmap(QPixmap::fromImage(imageFirst));
    ui->labelSecondCurve->setPixmap(QPixmap::fromImage(imageSecond));
}
