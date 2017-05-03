#include "mainwindow.h"
#include "ui_mainwindow.h"

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
